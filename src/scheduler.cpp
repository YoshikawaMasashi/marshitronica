// Copyright[2019] <marshi(masashi yoshikawa)>
#include "scheduler.h"
#include "unistd.h"


Scheduler::Scheduler() {
  return;
}

Scheduler::~Scheduler() {
  this->set_is_running(false);
  if (this->scheduling_thread.joinable()) {
    this->scheduling_thread.join();
  }
  return;
}

void Scheduler::schedule() {
  while (true) {
    this->is_running_mutex.lock();
    if (!this->is_running) {
      this->is_running_mutex.unlock();
      break;
    } else {
      this->is_running_mutex.unlock();
    }

    this->task_queue_mutex.lock();
    if (this->task_queue.size() > 0) {
      // TODO(marshi): no auto use
      auto next = this->task_queue.begin();
      double next_beats = next->first;
      std::vector<std::function<void(void)>> next_tasks = next->second;
      if (next_beats < this->now_beats()) {
        // TODO(marshi): threading
        for (std::function<void(void)> task : next_tasks) {
          task();
        }
        this->task_queue.erase(next_beats);
        this->task_queue_mutex.unlock();
        continue;
      }
    }
    this->task_queue_mutex.unlock();
    usleep(this->step_second * 1000000);
  }
}

void Scheduler::set_is_running(bool is_running) {
  this->is_running_mutex.lock();
  this->is_running = is_running;
  this->is_running_mutex.unlock();
}

void Scheduler::start() {
  this->set_is_running(true);
  this->start_time = std::chrono::system_clock::now();
  this->scheduling_thread = std::thread([this](){this->schedule();});
}

void Scheduler::stop() {
  this->set_is_running(false);
  this->scheduling_thread.join();
}

double Scheduler::seconds_to_beats(double seconds) {
  return seconds * this->bpm / 60;
}

double Scheduler::beats_to_seconds(double beats) {
  return beats * 60 / this->bpm;
}

double Scheduler::now_seconds() {
  std::chrono::duration<double> now_seconds_duration =
    std::chrono::system_clock::now() - this->start_time;
  return now_seconds_duration.count();
}

double Scheduler::now_beats() {
  return this->seconds_to_beats(this->now_seconds());
}

void Scheduler::add_task(double beats, std::function<void(void)> task) {
  if (beats < this->now_beats()) {
    return;
  }

  this->task_queue_mutex.lock();
  if (this->task_queue.find(beats) != this->task_queue.end()) {
    this->task_queue.at(beats).push_back(task);
  } else {
    this->task_queue.insert(
        std::make_pair(beats, std::vector<std::function<void(void)>>({task})));
  }
  this->task_queue_mutex.unlock();
}

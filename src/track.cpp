// Copyright[2019] <marshi(masashi yoshikawa)>
#include "./track.h"

Track::Track() {
  this->bus_id = Common::get().get_next_bus_id();
  Common::get().increment_next_bus_id();

  char buffer[1024];
  osc::OutboundPacketStream p(buffer, 1024);

  p << osc::BeginBundleImmediate
      << osc::BeginMessage("/s_new")
        << "output" << Common::get().get_next_synth_id() << 0 << 0
        << "in" << this->bus_id
      << osc::EndMessage
    << osc::EndBundle;
  Common::get().get_transmit_socket()->Send(p.Data(), p.Size());

  Common::get().increment_next_synth_id();

  this->scheduler = Common::get().main_scheduler;
}

double Track::get_length() {
  return this->phrase->get_length();
}

void Track::set_phrase(Phrase* phrase) {
  this->phrase = phrase;
}

void Track::set_scheduler(Scheduler* scheduler) {
  this->scheduler = scheduler;
}

Scheduler* Track::get_scheduler() {
  return this->scheduler;
}

int Track::now_repeats() {
  return static_cast<int>(this->scheduler->now_beats() / this->get_length());
}

double Track::now_beats() {
  return fmod(this->scheduler->now_beats(), this->get_length());
}

double Track::next_scheduler_beats() {
  auto next_beats = this->phrase->events.upper_bound(this->now_beats());
  if (next_beats == this->phrase->events.end()) {
    next_beats = this->phrase->events.begin();
    return next_beats->first + this->get_length() * (this->now_repeats() + 1);
  } else {
    return next_beats->first + this->get_length() * this->now_repeats();
  }
}

double Track::next_beats() {
  auto next_beats = this->phrase->events.upper_bound(this->now_beats());
  if (next_beats == this->phrase->events.end()) {
    next_beats = this->phrase->events.begin();
  }
  return next_beats->first;
}

double Track::next_beats_of_beats(double beats) {
  auto next_beats = this->phrase->events.upper_bound(beats);
  if (next_beats == this->phrase->events.end()) {
    next_beats = this->phrase->events.begin();
  }
  return next_beats->first;
}

double Track::next_scheduler_beats_of_beats(double beats) {
  auto next_beats = this->phrase->events.upper_bound(beats);
  if (next_beats == this->phrase->events.end()) {
    next_beats = this->phrase->events.begin();
    return next_beats->first + this->get_length() * (this->now_repeats() + 1);
  } else {
    return next_beats->first + this->get_length() * this->now_repeats();
  }
}

static void scheduling_callback(Track* track, double beats) {
  track->send_osc(beats);
  double next_beats = track->next_beats_of_beats(beats);
  double next_scheduler_beats = track->next_scheduler_beats_of_beats(beats);
  std::function<void(void)> f =
    std::bind(scheduling_callback, track, next_beats);
  track->get_scheduler()->add_task(next_scheduler_beats, f);
}

void Track::play() {
  double next_beats = fmod(this->next_beats(), this->get_length());
  std::function<void(void)> f =
    std::bind(scheduling_callback, this, next_beats);
  this->scheduler->add_task(
    next_beats + this->get_length() * this->now_repeats(), f);
}

void Track::send_osc(double beats) {
  std::vector<std::shared_ptr<Event>> events_in_beats
    = this->phrase->events[beats];

  for ( std::shared_ptr<Event> event : events_in_beats ) {
    char buffer[1024];
    osc::OutboundPacketStream p(buffer, 1024);

    p << osc::BeginBundleImmediate;
    p = event->add_osc_message(
      p, Common::get().get_next_synth_id(),
      this->bus_id, this->scheduler->get_bpm());
    p << osc::EndBundle;
    Common::get().get_transmit_socket()->Send(p.Data(), p.Size());

    Common::get().increment_next_synth_id();
  }
}

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

Phrase* Track::get_phrase() {
  return this->phrase;
}

void Track::set_scheduler(Scheduler* scheduler) {
  this->scheduler = scheduler;
}

Scheduler* Track::get_scheduler() {
  return this->scheduler;
}

static void send_osc(Track* track, std::shared_ptr<Event> event) {
  char buffer[1024];
  osc::OutboundPacketStream p(buffer, 1024);

  p << osc::BeginBundleImmediate;
  p = event->add_osc_message(
    p, Common::get().get_next_synth_id(),
    track->bus_id, track->get_scheduler()->get_bpm());
  p << osc::EndBundle;
  Common::get().get_transmit_socket()->Send(p.Data(), p.Size());

  Common::get().increment_next_synth_id();
}

static void new_scheduling_callback(Track* track, double scheduler_beats) {
  double next_scheduler_beats = scheduler_beats + 1;
  double beats = fmod(scheduler_beats, track->get_phrase()->get_length());
  double next_beats =
    fmod(next_scheduler_beats, track->get_phrase()->get_length());

  // TODO(marshi): beats > next_beats
  std::vector<std::pair<double, std::shared_ptr<Event>>> events_list
    = track->get_phrase()->get_events_in_range(beats, next_beats);

  std::function<void(void)> f;
  for ( auto event_pair : events_list ) {
    f = std::bind(send_osc, track, event_pair.second);
    track->get_scheduler()->add_task(
      event_pair.first + (scheduler_beats - beats), f);
  }
  f = std::bind(new_scheduling_callback, track, next_scheduler_beats);
  track->get_scheduler()->add_task(scheduler_beats, f);
}

void Track::play() {
  double now_scheduler_beats = this->scheduler->now_beats();
  double next_scheduler_beats = ceil(now_scheduler_beats);
  double now_beats = fmod(now_scheduler_beats, this->phrase->get_length());
  double next_beats = fmod(next_scheduler_beats, this->phrase->get_length());

  std::vector<std::pair<double, std::shared_ptr<Event>>> events_list
    = this->phrase->get_events_in_range(now_beats, next_beats);

  std::function<void(void)> f;
  for ( auto event_pair : events_list ) {
    f = std::bind(send_osc, this, event_pair.second);
    this->scheduler->add_task(
      event_pair.first + (now_scheduler_beats - now_beats), f);
  }
  new_scheduling_callback(this, next_scheduler_beats);
}

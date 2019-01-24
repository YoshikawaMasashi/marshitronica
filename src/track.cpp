// Copyright[2019] <marshi(masashi yoshikawa)>
#include "./track.h"
#include "./common.h"

Track::Track() {
  this->bus_id = next_bus_id;
  next_bus_id += 2;

  char buffer[1024];
  osc::OutboundPacketStream p(buffer, 1024);

  p << osc::BeginBundleImmediate
      << osc::BeginMessage("/s_new")
          << "output" << next_synth_id << 0 << 0 << "in" << this->bus_id
          << osc::EndMessage
      << osc::EndBundle;
  transmitSocket.Send(p.Data(), p.Size());

  next_synth_id++;
}

void Track::set_phrase(Phrase* phrase) {
  this->phrase = phrase;
}

void Track::set_scheduler(Scheduler* scheduler) {
  this->scheduler = scheduler;
}

int Track::now_repeats() {
  return static_cast<int>(this->scheduler->now_beats() / this->length);
}

double Track::now_beats() {
  return fmod(this->scheduler->now_beats(), this->length);
}

double Track::next_beats() {
  auto next_beats = this->phrase->notes.upper_bound(this->now_beats());
  if (next_beats == this->phrase->notes.end()) {
    next_beats = this->phrase->notes.begin();
  }
  return next_beats->first;
}

double Track::next_scheduler_beats() {
  auto next_beats = this->phrase->notes.upper_bound(this->now_beats());
  if (next_beats == this->phrase->notes.end()) {
    next_beats = this->phrase->notes.begin();
    return next_beats->first + this->length * (this->now_repeats() + 1);
  } else {
    return next_beats->first + this->length * this->now_repeats();
  }
}

double Track::next_beats_of_beats(double beats) {
  auto next_beats = this->phrase->notes.upper_bound(beats);
  if (next_beats == this->phrase->notes.end()) {
    next_beats = this->phrase->notes.begin();
  }
  return next_beats->first;
}

double Track::next_scheduler_beats_of_beats(double beats) {
  auto next_beats = this->phrase->notes.upper_bound(beats);
  if (next_beats == this->phrase->notes.end()) {
    next_beats = this->phrase->notes.begin();
    return next_beats->first + this->length * (this->now_repeats() + 1);
  } else {
    return next_beats->first + this->length * this->now_repeats();
  }
}

void Track::play() {
  this->recursive_schedule(this->next_scheduler_beats());
}

static void scheduling_callback(Track* track, double scheduler_beats) {
  double beats = fmod(scheduler_beats, track->length);
  track->recursive_schedule(track->next_scheduler_beats_of_beats(beats));
  track->send_osc(beats);
}

void Track::recursive_schedule(double beats) {
  std::function<void(void)> f = std::bind(scheduling_callback, this, beats);
  this->scheduler->add_task(beats, f);
}

void Track::send_osc(double beats) {
  std::vector<Note> notes_in_beats = this->phrase->notes[beats];

  for ( Note note : notes_in_beats ) {
    char buffer[1024];
    osc::OutboundPacketStream p(buffer, 1024);

    p << osc::BeginBundleImmediate
        << osc::BeginMessage("/s_new")
            << "smooth" << next_synth_id << 0 << 0 << "out" << this->bus_id
            << "amp" << note.get_amp()
            << "sustain"
            << this->scheduler->beats_to_seconds(note.get_duration())
            << "freq" << pitch_to_freq(note.get_pitch())
            << osc::EndMessage
        << osc::EndBundle;
    transmitSocket.Send(p.Data(), p.Size());

    next_synth_id++;
  }
}

// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include "note.h"


Note::Note(double pitch, double duration, double amp) {
  this->pitch = pitch;
  this->duration = duration;
  this->amp = amp;
  this->length = duration;
}

double Note::get_pitch() {
  return this->pitch;
}

double Note::get_duration() {
  return this->duration;
}

double Note::get_amp() {
  return this->amp;
}

static double beats_to_seconds(double beats, double bpm) {
  return beats * 60 / bpm;
}

static double pitch_to_freq(double pitch) {
  return 440 * pow(2, ((pitch - 69) / 12));
}

osc::OutboundPacketStream& Note::add_osc_message(
  osc::OutboundPacketStream& p, int next_synth_id, int bus_id, int bpm) {
  p << osc::BeginMessage("/s_new")
      << "smooth" << next_synth_id << 0 << 0
      << "out" << bus_id
      << "amp" << static_cast<float>(this->amp)
      << "sustain" << static_cast<float>(beats_to_seconds(this->duration, bpm))
      << "freq" << static_cast<float>(pitch_to_freq(this->pitch))
    << osc::EndMessage;
  return p;
}

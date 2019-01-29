// Copyright[2019] <marshi(masashi yoshikawa)>
#include "notes_phrase.h"


NotesPhrase::NotesPhrase() {
  this->length = 0.0;
  return;
}

void NotesPhrase::add_note(double beats, std::shared_ptr<Note> note) {
  if (this->notes.find(beats) != this->notes.end()) {
    this->notes.at(beats).push_back(note);
  } else {
    this->notes.insert(
      std::make_pair(beats, std::vector<std::shared_ptr<Note>>({note})));
  }
  this->length = std::max(this->length, beats + note->get_duration());
}

static double beats_to_seconds(double beats, double bpm) {
  return beats * 60 / bpm;
}

static double pitch_to_freq(double pitch) {
  return 440 * pow(2, ((pitch - 69) / 12));
}

static osc::OutboundPacketStream& make_osc_massage(
  NotesPhrase* notes_phrase, std::shared_ptr<Note> note,
  osc::OutboundPacketStream& p, int bus_id, int bpm, int next_synth_id) {
    p << osc::BeginMessage("/s_new")
          << "smooth" << next_synth_id << 0 << 0
          << "out" << bus_id
          << "amp" << static_cast<float>(note->get_amp())
          << "sustain" << static_cast<float>(beats_to_seconds(note->get_duration(), bpm))
          << "freq" << static_cast<float>(pitch_to_freq(note->get_pitch()))
        << osc::EndMessage;
    return p;
}

std::vector<std::pair<double, std::function<
  osc::OutboundPacketStream&(osc::OutboundPacketStream&, int, int, int)
>>>
  NotesPhrase::get_events_in_range(
  double start, double end) {
  std::vector<std::pair<double, std::function<
    osc::OutboundPacketStream&(osc::OutboundPacketStream&, int, int, int)
  >>> result = {};

  if (start > end) return result;

  auto start_iter = this->notes.lower_bound(start);
  auto end_iter = this->notes.lower_bound(end);
  for (auto notes_iter = start_iter; notes_iter != end_iter ; notes_iter++) {
    for (std::shared_ptr<Note> note : notes_iter->second) {
        std::function<
          osc::OutboundPacketStream&(osc::OutboundPacketStream&, int, int, int)
        > f = std::bind(
          make_osc_massage, this, note, std::placeholders::_1,
          std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        result.push_back(std::make_pair(notes_iter->first, f));
    }
  }
  return result;
}

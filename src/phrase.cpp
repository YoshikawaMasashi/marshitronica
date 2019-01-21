// Copyright [2019] marshi (masashi yoshikawa)
#include "phrase.h"

Phrase::Phrase() {
  return;
}

void Phrase::add_note(double beats, Note note) {
  if (this->notes.find(beats) != this->notes.end()) {
    this->notes.at(beats).push_back(note);
  } else {
    this->notes.insert(std::make_pair(beats, std::vector<Note>({note})));
  }
}

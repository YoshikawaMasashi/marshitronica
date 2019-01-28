// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include "note.h"


Note::Note(double pitch, double duration, double amp) {
  this->pitch = pitch;
  this->duration = duration;
  this->amp = amp;
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

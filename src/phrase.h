// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <map>
#include <vector>
#include "./note.h"

class Phrase {
 private:
  double length;
 public:
  Phrase();
  void add_note(double, Note);
  double get_length();
  std::map<double, std::vector<Note>> notes;
};

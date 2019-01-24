// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <map>
#include <vector>
#include "./note.h"

class Phrase {
 private:
 public:
  Phrase();
  std::map<double, std::vector<Note>> notes;
  double length;
  void add_note(double, Note);
};

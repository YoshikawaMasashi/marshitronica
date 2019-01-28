// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <map>
#include <vector>
#include "./note.h"
#include "./common.h"

class NotesPhrase {
 private:
  double length;
 public:
  NotesPhrase();
  void add_note(double, std::shared_ptr<Note>);
  double get_length();
  std::map<double, std::vector<std::shared_ptr<Note>>> notes;
  std::vector<std::pair<double, std::function<void(int, int)>>> get_events_in_range(
    double, double);
};

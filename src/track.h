// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <map>
#include <vector>
#include "./note.h"
#include "./phrase.h"
#include "./scheduler.h"

class Track {
 private:
  Phrase phrase;
  double length = 0;
  Scheduler scheduler;
  int bus_id;
 public:
  Track();
  void set_phrase(Phrase);
};

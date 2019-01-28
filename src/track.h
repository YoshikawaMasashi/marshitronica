// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <map>
#include <vector>
#include <math.h>
#include "./phrase.h"
#include "./scheduler.h"
#include "./common.h"

class Track {
 private:
  Phrase* phrase;
  Scheduler* scheduler;
 public:
  Track();
  int bus_id;
  void set_phrase(Phrase*);
  Phrase* get_phrase();
  void set_scheduler(Scheduler*);
  Scheduler* get_scheduler();
  double get_length();
  void play();
};

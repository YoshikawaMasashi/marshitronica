// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <map>
#include <vector>
#include <math.h>
#include "./event.h"
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
  int now_repeats();
  double now_beats();
  double next_scheduler_beats();
  double next_beats();
  double next_beats_of_beats(double);
  double next_scheduler_beats_of_beats(double);
  void play();
};

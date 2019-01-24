// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <map>
#include <vector>
#include <math.h>
#include "./note.h"
#include "./phrase.h"
#include "./scheduler.h"

class Track {
 private:
  Phrase* phrase;
  Scheduler* scheduler;
  int bus_id;
 public:
  double length = 0;
  Track();
  void set_phrase(Phrase*);
  void set_scheduler(Scheduler*);
  int now_repeats();
  double now_beats();
  double next_beats();
  double next_scheduler_beats();
  double next_beats_of_beats(double);
  double next_scheduler_beats_of_beats(double);
  static void callback(Track* track, double scheduler_beats);
  void play();
  void recursive_schedule(double);
  void send_osc(double);
};

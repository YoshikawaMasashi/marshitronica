// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <map>
#include <vector>
#include <math.h>
#include "./notes_phrase.h"
#include "./scheduler.h"
#include "./common.h"

class Track {
 private:
  NotesPhrase* phrase;
  Scheduler* scheduler;
 public:
  Track();
  int bus_id;
  void set_phrase(NotesPhrase*);
  NotesPhrase* get_phrase();
  void set_scheduler(Scheduler*);
  Scheduler* get_scheduler();
  double get_length();
  void play();
};

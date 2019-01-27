// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <map>
#include <vector>
#include "./event.h"

class Phrase {
 private:
  double length;
 public:
  Phrase();
  void add_event(double, std::shared_ptr<Event>);
  double get_length();
  std::map<double, std::vector<std::shared_ptr<Event>>> events;
  std::vector<std::pair<double, std::shared_ptr<Event>>> get_events_in_range(
    double, double);
};

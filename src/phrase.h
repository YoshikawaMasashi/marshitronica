// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <vector>
#include <functional>

class Phrase {
 protected:
  double length;
 public:
  Phrase();
  double get_length();
  virtual std::vector<std::pair<double, std::function<void(int, int)>>>
    get_events_in_range(double, double);
};

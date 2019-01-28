// Copyright[2019] <marshi(masashi yoshikawa)>
#include "phrase.h"


Phrase::Phrase() {
  return;
}

double Phrase::get_length() {
  return this->length;
}

std::vector<std::pair<double, std::function<void(int, int)>>>
Phrase::get_events_in_range(double, double) {
  return std::vector<std::pair<double, std::function<void(int, int)>>>{};
}

// Copyright[2019] <marshi(masashi yoshikawa)>
#include "phrase.h"


Phrase::Phrase() {
  this->length = 0.0;
  return;
}

void Phrase::add_event(double beats, std::shared_ptr<Event> event) {
  if (this->events.find(beats) != this->events.end()) {
    this->events.at(beats).push_back(event);
  } else {
    this->events.insert(
      std::make_pair(beats, std::vector<std::shared_ptr<Event>>({event})));
  }
  this->length = std::max(this->length, beats + event->get_length());
}

double Phrase::get_length() {
  return this->length;
}

std::vector<std::pair<double, std::shared_ptr<Event>>>
  Phrase::get_events_in_range(
  double start, double end) {
  std::vector<std::pair<double, std::shared_ptr<Event>>> result = {};

  if (start > end) return result;

  auto start_iter = this->events.lower_bound(start);
  auto end_iter = this->events.lower_bound(end);
  for (auto events_iter = start_iter; events_iter != end_iter ; events_iter++) {
    for (std::shared_ptr<Event> event : events_iter->second) {
      result.push_back(std::make_pair(events_iter->first, event));
    }
  }
  return result;
}

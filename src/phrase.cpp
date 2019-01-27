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

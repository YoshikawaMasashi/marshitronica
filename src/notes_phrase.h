// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <map>
#include <vector>
#include "./note.h"
#include "./phrase.h"

class NotesPhrase : public Phrase {
 public:
  NotesPhrase();
  void add_note(double, std::shared_ptr<Note>);
  std::map<double, std::vector<std::shared_ptr<Note>>> notes;
  std::vector<std::pair<double, std::function<
    osc::OutboundPacketStream&(osc::OutboundPacketStream&, int, int, int)
  >>> get_events_in_range(
    double, double) override;
};

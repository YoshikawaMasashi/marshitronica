// Copyright[2019] <marshi(masashi yoshikawa)>

// TODO(marshi): rethinking header definition
#pragma once

#include <vector>
#include <functional>
#include "osc/OscOutboundPacketStream.h"

class Phrase {
 protected:
  double length;
 public:
  Phrase();
  double get_length();
  virtual std::vector<std::pair<double, std::function<
    osc::OutboundPacketStream&(osc::OutboundPacketStream&, int, int, int)
  >>> get_events_in_range(double, double);
};

// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <math.h>

#include "event.h"

class Note : public Event{
 private:
  double pitch;
  double duration;
  double amp;
 public:
  osc::OutboundPacketStream& add_osc_message(
    osc::OutboundPacketStream& p, int, int, int);
  Note(double, double, double);
  double get_pitch();
  double get_duration();
  double get_amp();
};

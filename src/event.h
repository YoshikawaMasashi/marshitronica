// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include "osc/OscOutboundPacketStream.h"

class Event{
 protected:
   double length;
 public:
   virtual osc::OutboundPacketStream& add_osc_message(
    osc::OutboundPacketStream&, int, int, int)
    = 0;
   double get_length();
};

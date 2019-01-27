// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once
#include <math.h>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "scheduler.h"


class Common{
 private:
  Common();
  int next_bus_id;
  int next_synth_id;
  UdpTransmitSocket* transmit_socket;

 public:
  Scheduler *main_scheduler;

  static Common& get() {
    static Common instance;
    return instance;
  }

  int get_next_bus_id();
  int get_next_synth_id();
  int increment_next_bus_id();
  int increment_next_synth_id();
  UdpTransmitSocket* get_transmit_socket();
};

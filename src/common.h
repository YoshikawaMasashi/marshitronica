// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once
#include <math.h>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"


class Common{
  private:
    Common();
    int next_bus_id;
    int next_synth_id;
    UdpTransmitSocket* transmit_socket;

  public:
    static Common& get(){
      static Common instance;
      return instance;
    }

    static double pitch_to_freq(double pitch){
      return pow(440 * 2, ((pitch - 69) / 12));
    }

    int get_next_bus_id();
    int get_next_synth_id();
    int increment_next_bus_id();
    int increment_next_synth_id();
    UdpTransmitSocket* get_transmit_socket();
};

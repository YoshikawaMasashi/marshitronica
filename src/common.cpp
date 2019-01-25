// Copyright[2019] <marshi(masashi yoshikawa)>
#include "./common.h"


Common::Common() {
  this->next_bus_id = 4;
  this->next_synth_id = 10000;
  this->transmit_socket = new UdpTransmitSocket(
    IpEndpointName("127.0.0.1", 57110));
}

int Common::get_next_bus_id() {
  return this->next_bus_id;
}

int Common::get_next_synth_id() {
  return this->next_synth_id;
}

int Common::increment_next_bus_id() {
  this->next_bus_id += 2;
  return this->next_bus_id;
}

int Common::increment_next_synth_id() {
  this->next_synth_id += 1;
  return this->next_synth_id;
}

UdpTransmitSocket* Common::get_transmit_socket() {
  return this->transmit_socket;
}

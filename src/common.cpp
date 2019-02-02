// Copyright[2019] <marshi(masashi yoshikawa)>
#include "./common.h"


Common::Common() {
  this->next_bus_id = 4;
  this->next_synth_id = 10000;
  this->next_bufnum = 1000;
  this->transmit_socket = new UdpTransmitSocket(
    IpEndpointName("localhost", 57110));
  this->main_scheduler = new Scheduler();
  this->main_scheduler->start();
}

int Common::get_next_bus_id() {
  return this->next_bus_id;
}

int Common::get_next_synth_id() {
  return this->next_synth_id;
}

int Common::get_next_bufnum() {
  return this->next_bufnum;
}

int Common::increment_next_bus_id() {
  this->next_bus_id += 2;
  return this->next_bus_id;
}

int Common::increment_next_synth_id() {
  this->next_synth_id += 1;
  return this->next_synth_id;
}

int Common::increment_next_bufnum() {
  this->next_bufnum += 1;
  return this->next_bufnum;
}

UdpTransmitSocket* Common::get_transmit_socket() {
  return this->transmit_socket;
}

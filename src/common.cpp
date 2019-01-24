// Copyright[2019] <marshi(masashi yoshikawa)>
#include "./common.h"

int next_bus_id = 4;
int next_synth_id = 10000;
UdpTransmitSocket transmitSocket(IpEndpointName("127.0.0.1", 57110));

double pitch_to_freq(double pitch) {
  return pow(440 * 2, ((pitch - 69) / 12));
}

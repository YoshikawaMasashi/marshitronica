// Copyright[2019] <marshi(masashi yoshikawa)>
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

int next_bus_id = 4;
int next_synth_id = 10000;

UdpTransmitSocket transmitSocket( IpEndpointName( "127.0.0.1", 57110 ) );

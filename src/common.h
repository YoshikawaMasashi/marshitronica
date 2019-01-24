// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once
#include <math.h>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

extern int next_bus_id;
extern int next_synth_id;
extern UdpTransmitSocket transmitSocket;

double pitch_to_freq(double);

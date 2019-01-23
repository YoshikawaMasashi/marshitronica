// Copyright[2019] <marshi(masashi yoshikawa)>
#include "./track.h"
#include "./common.h"

Track::Track() {
  this->bus_id = next_bus_id;
  next_bus_id += 2;

  char buffer[1024];
  osc::OutboundPacketStream p(buffer, 1024);

  p << osc::BeginBundleImmediate
      << osc::BeginMessage("/s_new")
          << "output" << next_synth_id << 0 << 0 << "in" << this->bus_id
          << osc::EndMessage
      << osc::EndBundle;
  transmitSocket.Send(p.Data(), p.Size());

  next_synth_id++;
}

void Track::set_phrase(Phrase phrase) {
  this->phrase = phrase;
}

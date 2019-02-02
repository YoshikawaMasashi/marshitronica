// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <string>
#include <iostream>
#include <map>
#include "./common.h"
#include "./tsf.h"
#include "osc/OscOutboundPacketStream.h"


class SoundFont {
 private:
   std::map<std::pair<int, int>, int> buffer_map;
 public:
  SoundFont(std::string);
  ~SoundFont();
  void send_buffer(int, int);
  tsf* tsf_struct;
};

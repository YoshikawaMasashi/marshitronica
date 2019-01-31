// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

#include <string>
#include <iostream>
#include "./tsf.h"


class SoundFont {
 public:
  SoundFont(std::string);
  ~SoundFont();
  tsf* tsf_struct;
};

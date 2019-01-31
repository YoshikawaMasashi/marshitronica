// Copyright[2019] <marshi(masashi yoshikawa)>
#define TSF_IMPLEMENTATION
#include "./sound_font.h"


SoundFont::SoundFont(std::string filename) {
  this->tsf_struct = tsf_load_filename(filename.c_str());
  std::cout << tsf_struct->presets[0].presetName << std::endl;
}

SoundFont::~SoundFont() {
  TSF_FREE(this->tsf_struct);
}

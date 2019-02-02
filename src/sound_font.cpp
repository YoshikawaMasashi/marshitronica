// Copyright[2019] <marshi(masashi yoshikawa)>
#define TSF_IMPLEMENTATION
#include "./sound_font.h"


SoundFont::SoundFont(std::string filename) {
  this->tsf_struct = tsf_load_filename(filename.c_str());

  for (int i = 0; i < this->tsf_struct->presetNum; i++) {
    std::cout << this->tsf_struct->presets[i].presetName << std::endl;
    for (int j = 0; j < this->tsf_struct->presets[i].regionNum; j++) {
      this->send_buffer(this->tsf_struct->presets[i].regions[j].offset,
        this->tsf_struct->presets[i].regions[j].end);
    }
  }
}

SoundFont::~SoundFont() {
  TSF_FREE(this->tsf_struct);
}

void SoundFont::send_buffer(int start, int end) {
  if (this->buffer_map.find(std::make_pair(start, end))
    != this->buffer_map.end()) {
    return;
  }

  end = start + 100;

  char buffer[1024];
  osc::OutboundPacketStream p(buffer, 1024);

  p << osc::BeginBundleImmediate;
  p << osc::BeginMessage("/b_alloc")
      << Common::get().get_next_bufnum() << end - start << 1 << 0
    << osc::EndMessage;
  p << osc::BeginMessage("/b_setn") << Common::get().get_next_bufnum() << 0
    << end - start;
  for (int i = start; i < end; i++) {
    p << static_cast<float>(this->tsf_struct->fontSamples[i] * 10);
  }
  p << osc::EndMessage;
  p << osc::EndBundle;

  Common::get().get_transmit_socket()->Send(p.Data(), p.Size());

  this->buffer_map[std::make_pair(start, end)]
    = Common::get().get_next_bufnum();
  std::cout << Common::get().get_next_bufnum() << " " << end-start << std::endl;

  Common::get().increment_next_bufnum();
}

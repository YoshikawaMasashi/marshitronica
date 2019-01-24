// Copyright[2019] <marshi(masashi yoshikawa)>
#pragma once

class Note {
 private:
  double pitch;
  double duration;
  double amp;
 public:
  Note(double, double, double);
  double get_pitch();
  double get_duration();
  double get_amp();
};

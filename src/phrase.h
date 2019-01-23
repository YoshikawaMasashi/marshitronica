// TODO(marshi): rethinking header definition
#pragma once

#include <map>
#include <vector>
#include "note.h"

class Phrase
{
private:
  std::map<double, std::vector<Note>> notes;
  double length;
public:
  Phrase();
  void add_note(double, Note);
};

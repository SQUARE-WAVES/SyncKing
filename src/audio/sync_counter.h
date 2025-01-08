#pragma once

#include "table_params.h"

class sync_counter
{
  size_t count=0;
  size_t time = 1000; //this is 120 bpm
  size_t division = 0;

  bpm_param bpm;

  public:

  int get_bpm();
  int bump_bpm(int amt);

  bool tick();
  size_t get_div();
  size_t get_time();

  void reset();
};

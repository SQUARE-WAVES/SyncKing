#pragma once
#include "daisy_seed.h"

class knob_set
{
  daisy::AdcHandle adc;

  int32_t vals[4] = {0,0,0,0};

  public:
  void init();
  void poll();
  uint16_t val(size_t chan);

  float vol1();
  float vol2();
  float pan1();
  float pan2();
};

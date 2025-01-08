#include "knobs.h"

using namespace daisy;
using namespace daisy::seed;

void knob_set::init()
{
  AdcChannelConfig conf[4];

  conf[0].InitSingle(A0);
  conf[1].InitSingle(A1);
  conf[2].InitSingle(A2);
  conf[3].InitSingle(A4);

  adc.Init(conf,4);
  adc.Start();
}

void knob_set::poll()
{
  for(size_t chan = 0; chan<4;++chan)
  {
    int32_t res = adc.Get(chan);
    int32_t val = (res>>1) + (vals[chan]>>1);
    vals[chan] = val;
  }
}

uint16_t knob_set::val(size_t chan)
{
  return vals[chan];
}

float knob_set::vol1()
{
  auto v = vals[0] >> 4;
  return 1.0f - ((float)v/4096.0);
}

float knob_set::vol2()
{
  auto v = vals[2] >> 4;
  return 1.0f - ((float)v/4096.0);
}

float knob_set::pan1()
{
  auto v = vals[3] >> 4;
  return 2.0f - ((float)v/2048.0) ;
}

float knob_set::pan2()
{
  auto v = vals[1] >> 4;
  return 2.0f - ((float)v/2048.0) ;
}

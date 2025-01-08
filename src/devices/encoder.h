#pragma once
#include "daisy_seed.h"

class encoder
{
  using GPIO = daisy::GPIO;
  using pin = daisy::Pin;

  GPIO btn;
  GPIO dt;
  GPIO clk;

  uint8_t track =0xFF;
  int btn_val = 0;

  public:
  void init(pin btn_pin, pin dt_pin, pin clk_pin);
  int poll();
  int poll_btn();
};


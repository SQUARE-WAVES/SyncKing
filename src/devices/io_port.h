#pragma once

#include "daisy_seed.h"
#include "ioexp.h"

class button_events
{
  uint8_t old_st;
  uint8_t new_st;

  public:
  button_events(uint8_t o, uint8_t n);
  int get(int n);
};

class io_port
{
  ioexp mcp;

  uint8_t btns = 0x00; //the current state
  uint8_t lts = 0x00;
  uint8_t blinkers = 0x00;

  public:
  void init(uint8_t addr);
  button_events poll();

  void set_lights(uint8_t sets);
  void clear_lights(uint8_t lts);
  void blink_lights(uint8_t blinks);

  void update_lights();
};


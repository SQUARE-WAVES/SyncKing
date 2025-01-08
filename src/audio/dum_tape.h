#pragma once

#include <cmath>

class dum_tape
{
  float* mem;
  size_t len;
  size_t pos = 0;

  public:

  dum_tape(float* m, size_t l):mem(m),len(l)
  {
  }

  void record(float val)
  {
    mem[pos] = val;
  }

  float val()
  {
    return mem[pos];
  }

  bool step()
  {
    ++pos;

    if(pos == len)
    {
      pos = 0;
      return true;
    }

    return false;
  }

  void reset() { pos = 0;}
  void reset(size_t p) { pos = p % len;}
  bool at_start() { return pos == 0; }
};

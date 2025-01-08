#include "sync_counter.h"

int sync_counter::get_bpm()
{
  return bpm.get_val();
}

int sync_counter::bump_bpm(int amt)
{
  size_t new_time = bpm.bump(amt);

  time = new_time;
  count = count % time;

  return bpm.get_val();
}

bool sync_counter::tick()
{
  bool out = count == 0;

  ++count;

  if(count == time)
  {
    count = 0;
    ++division;

    if(division == 768)
    {
      division = 0;
    }
  }

  return out;
}

size_t sync_counter::get_div()
{
  return division;
}

size_t sync_counter::get_time()
{
  return time;
}

void sync_counter::reset()
{
  count = 0;
  division = 0;
}

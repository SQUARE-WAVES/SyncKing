#include "looper.h"
#include "../globals.h"

looper::looper(float* mem):
loop_set{
  loop(mem),
  loop(mem+(2*loop::TAPE_MAX)),
  loop(mem+(4*loop::TAPE_MAX)),
  loop(mem+(6*loop::TAPE_MAX))
}
{
}

bool looper::fill_buffs(const float* const* in,float** out, size_t len)
{
  if(!transport) 
  {
    return false;
  }

  //ok here is where you would adjust volume/pan
  bool has_pulse = false;
  
  for(size_t i=0;i<len;++i)
  {
    const float in_vl = in[0][i];
    const float in_vr = in[1][i];

    //now handle the sync
    bool pulse = sync.tick();
    bool main_sync = pulse && ((sync.get_div() % div_mod) == 0);

    has_pulse = has_pulse || pulse;

    for(size_t j=0;j<4;++j)
    {
      loop& lp = loop_set[j];

      if(main_sync)
      {
        lp.main_sync();
      }
      else if(pulse)
      {
        lp.sync_pulse();
      }
      
      auto lp_out = lp.tick(in_vl,in_vr);

      out[0][i] += lp_out.l;
      out[1][i] += lp_out.r;
    }
  }

  return has_pulse;
}

void looper::start()
{
  transport = true;
}

void looper::stop()
{
  transport = false;
  sync.reset();

  //reset all loops
  for(int i=0;i<4;++i)
  {
    loop_set[i].reset();
  }
}

loop_transport looper::lp_status(int loop)
{
  auto& lp = loop_set[loop % 4];
  return lp.tport;
}

const char* looper::lp_len(int loop)
{
  auto& lp = loop_set[loop % 4];
  return lp.len_param.get_str();
}

void looper::bump_lp_len(int loop, int amt)
{
  auto& lp = loop_set[loop % 4];
  size_t new_len = lp.len_param.bump(amt);

  lp.len = new_len;
  lp.count = lp.count % lp.len;
}

void looper::play_lp(int loop)
{
  auto& lp = loop_set[loop % 4];
  lp.tport.toggle_playing();
}

void looper::record_lp(int loop)
{
  auto& lp = loop_set[loop % 4];
  lp.tport.toggle_recording();
}

void looper::od_lp(int loop)
{
  auto& lp = loop_set[loop % 4];
  lp.tport.toggle_od();
}

void looper::oneshot_lp(int loop)
{
  auto& lp = loop_set[loop % 4];
  lp.tport.toggle_oneshot();
}

int looper::bpm()
{
  return sync.get_bpm();
}

int looper::bump_bpm(int amt)
{
  return sync.bump_bpm(amt);
}

const char* looper::sync_div()
{
  return div.get_str();
}

void looper::bump_div(int amt)
{
  div_mod = div.bump(amt);
}

void looper::bump_loop_len(int loop,int amt)
{
  auto& lp = loop_set[loop % 4];

  size_t new_len = lp.len_param.bump(amt);
  lp.len = new_len;
  lp.count %= lp.len; 
  lp.reposition(lp.count * sync.get_time());
}

const char* looper::get_loop_len(int loop)
{
  auto& lp = loop_set[loop % 4];
  return lp.len_param.get_str();
}

#include <algorithm>

float clamp(float val,float min, float max) {
  return std::min(max,std::max(val,min));
}

void looper::bump_loop_vol(int loop,int dir) {
  auto& lp = loop_set[loop%4];

  float amt = dir >= 0 ? 0.01 : -0.01;

  lp.v = clamp(lp.v + amt,0.0,1.0);
}

void looper::bump_loop_pan(int loop,int dir) {
  auto& lp = loop_set[loop%4];

  float amt = dir >= 0 ? 0.01 : -0.01;

  lp.p = clamp(lp.p + amt,-1.0,1.0);
}

float looper::get_loop_vol(int loop) {
  auto& lp = loop_set[loop%4];
  return lp.v;
}

float looper::get_loop_pan(int loop) {
  auto& lp = loop_set[loop%4];
  return lp.p;
}

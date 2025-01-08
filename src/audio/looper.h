#pragma once

#include "table_params.h"
#include "loop.h"
#include "sync_counter.h"

class looper
{
  loop loop_set[4];

  sync_counter sync;

  div_param div;
  size_t div_mod = 96;

  bool transport = false; //for now

  public:

  looper(float* mem);
  bool fill_buffs(const float* const* in,float** out, size_t len);

  void start();
  void stop();
  bool going() { return transport; }

  //manage loops
  loop_transport lp_status(int loop);
  const char* lp_len(int loop);
  void bump_lp_len(int loop,int amt);
  
  void play_lp(int loop);
  void record_lp(int loop);
  void od_lp(int loop);
  void oneshot_lp(int loop);

   
  //manage main sync
  int bpm();
  int bump_bpm(int amt);

  const char* sync_div();
  void bump_div(int amt);

  void bump_loop_len(int loop, int amt);
  const char* get_loop_len(int loop);

  void bump_loop_vol(int lp,int dir);
  void bump_loop_pan(int lp,int dir);

  float get_loop_vol(int lp);
  float get_loop_pan(int lp);
};

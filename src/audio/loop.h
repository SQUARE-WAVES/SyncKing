#pragma once

#include "dum_tape.h"
#include "table_params.h"

struct loop_transport
{
  static const int STOPPED = 0;
  static const int PENDING = 1;
  static const int ON = 2;
  static const int STOP_PENDING= 3;

  int playing = 0;
  int recording = 0;
  bool overdub = false;
  bool one_shot = false;

  void toggle_playing();
  void toggle_recording();
  void toggle_od();
  void toggle_oneshot();
};

struct stereo_pair 
{ 
  float l;
  float r;
};

struct loop
{
  static const size_t TAPE_MAX = 2000 * 96 * 8;

  dum_tape tpl;
  dum_tape tpr;

  loop_transport tport;
  div_param len_param;
  
  size_t len = 96; 
  size_t count = 0;

  float v = 1.0f;
  float p = 0.0f;

  loop(float* loop_buff);

  stereo_pair tick(float inl,float inr);

  void main_sync(); //this assumes there is a main sync pulse
  void sync_pulse(); //this is for any sync pulse
  void reset();
  void reposition(size_t new_pos);
};


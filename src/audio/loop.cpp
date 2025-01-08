#include "loop.h"

void loop_transport::toggle_playing()
{
  switch(playing)
  {
    case ON:
      playing = STOP_PENDING;
    break;

    case STOPPED:
      playing = PENDING;
    break;

    case PENDING:
      playing = STOPPED;
    break;

    case STOP_PENDING:
      playing = ON;
    break;
  }
}

void loop_transport::toggle_recording()
{
  switch(recording)
  {
    case ON:
      recording = STOP_PENDING;
    break;

    case STOPPED:
      recording = PENDING;
    break;

    case PENDING:
      recording = STOPPED;
    break;

    case STOP_PENDING:
      recording = ON;
    break;
  }
}

void loop_transport::toggle_od()
{
  overdub = !overdub;
}

void loop_transport::toggle_oneshot()
{
  one_shot = !one_shot;
}

loop::loop(float* loop_buff):
tpl(loop_buff,TAPE_MAX),
tpr(loop_buff+TAPE_MAX,TAPE_MAX)
{
}

stereo_pair loop::tick(float inl,float inr)
{
  if(tport.playing < 2)
  {
    return {0.0f,0.0f};
  }

  float outl = tpl.val();
  float outr = tpr.val();

  if(tport.recording > 1)
  {
    float odl = tport.overdub ? outl : 0.0f;
    float odr = tport.overdub ? outr : 0.0f;
    tpl.record(odl + inl);
    tpr.record(odr + inr);
  }

  /*
  float rpan = p >= 1.0f ? 1.0f : p;
  float lpan = 2.0-p >= 1.0f ? 1.0f : 2.0-p;
  */

  float rpan = p <= 0.0f ? 1.0 + p : 1.0;
  float lpan = p >= 0.0f ? 1.0-p : 1.0;

  tpl.step();
  tpr.step();

  return {outl*v*lpan,outr*v*rpan};
}

void loop::main_sync()
{
  switch(tport.playing)
  {
    case loop_transport::STOPPED:
      //nothing to do here!
    break;

    case loop_transport::PENDING:
      tport.playing = loop_transport::ON;
    break;

    case loop_transport::ON:
      //treat this as a regular sync
      sync_pulse();
    break;

    case loop_transport::STOP_PENDING:
      tport.playing = loop_transport::STOPPED;
      tport.recording = loop_transport::STOPPED;
      reset();
    break;

    default:
    break;
  }

  switch(tport.recording)
  {
    case loop_transport::STOPPED:
      //nothing to do here!
    break;

    case loop_transport::PENDING:
      if(tport.playing == loop_transport::ON)
      {
      }
    break;

    case loop_transport::ON:
      if(tport.one_shot)
      {
        tport.one_shot = false;
        tport.recording = loop_transport::STOP_PENDING;
      }
    break;

    case loop_transport::STOP_PENDING:
      tport.recording = loop_transport::STOPPED;
    break;

    default:
    break;
  }
}

void loop::sync_pulse()
{
  if(tport.playing < 2)
  {
    return;
  }

  ++count;
  if(count == len)
  {
    reset();
  }
}

void loop::reset()
{
  tpr.reset();
  tpl.reset();
  count = 0;
}

void loop::reposition(size_t new_pos)
{
  tpr.reset(new_pos);
  tpl.reset(new_pos);
}

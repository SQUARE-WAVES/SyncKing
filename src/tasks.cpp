#include "globals.h"
#include "tasks.h"

void status_blink(uint32_t now)
{
  static uint32_t last_time = 0;
  static bool on = false;
  
  if(now - last_time < 250)
  {
    return;
  }
  
  hw.SetLed(!on); 
  on = !on;
  last_time = now;
}

void port_blink(uint32_t now)
{
  static uint32_t last_time = 0;
  
  if(now - last_time < 125)
  {
    return;
  }
  
  prt.update_lights();
  prt2.update_lights();
  last_time = now;
}

struct poll_result {
  uint8_t sets;
  uint8_t clears;
  uint8_t blinks;

  poll_result merge(poll_result other)
  {
    return poll_result 
    { 
      sets | (other.sets<<4),
      clears | (other.clears <<4),
      blinks | (other.blinks <<4)
    };
  }
};

poll_result poll_loop(int loop) 
{
  uint8_t sets = 0x00;
  uint8_t clears = 0x00;
  uint8_t blinks = 0x00;

  auto stats = loops.lp_status(loop);

  switch(stats.playing)
  { 
    case 0: 
      clears |= 0x01; 
    break;
    case 2:
      sets |= 0x01;
    break;
    default:
      blinks |= 0x01;
    break;
  }

  switch(stats.recording)
  {
    case 0: 
      clears |= 0x02; 
    break;

    case 2:
      sets |= 0x02;
    break;
    
    default:
      blinks |= 0x02;
    break;
  }

  if(stats.overdub)
  {
    sets |= 0x04;
  }
  else
  {
    clears |= 0x04;
  }

  if(stats.one_shot)
  {
    sets |= 0x08;
  }
  else
  {
    clears |= 0x08;
  }

  return poll_result{sets,clears,blinks};
}

void poll_looper()
{
  //loops 1 and 2 are on port 2;
  auto prt2_res = poll_loop(0);
  prt2_res = prt2_res.merge(poll_loop(1));

  prt2.set_lights(prt2_res.sets);
  prt2.clear_lights(prt2_res.clears);
  prt2.blink_lights(prt2_res.blinks);

  auto prt_res = poll_loop(2);
  prt_res = prt_res.merge(poll_loop(3));

  prt.set_lights(prt_res.sets);
  prt.clear_lights(prt_res.clears);
  prt.blink_lights(prt_res.blinks);

  /*
  uint8_t sets = 0x00;
  uint8_t clears = 0x00;
  uint8_t blinks = 0x00;

  for(int i=0;i<4;++i)
  {
    int shft = 4*i;
    auto stats = loops.lp_status(i);

    switch(stats.playing)
    {
      case 0: 
        clears |= 0x01 << shft; 
      break;
      case 2:
        sets |= 0x01 << shft;
      break;
      
      default:
        blinks |= 0x01 << shft;
      break;
    }

    switch(stats.recording)
    {
      case 0: 
        clears |= 0x02 << shft; 
      break;

      case 2:
        sets |= 0x02 << shft;
      break;
      
      default:
        blinks |= 0x02 << shft;
      break;
    }

    if(stats.overdub)
    {
      sets |= 0x04 << shft;
    }
    else
    {
      clears |= 0x04 << shft;
    }

    if(stats.one_shot)
    {
      sets |= 0x08 << shft;
    }
    else
    {
      clears |= 0x08 << shft;
    }
  }

  prt.set_lights(sets);
  prt.clear_lights(clears);
  prt.blink_lights(blinks);
  */
}

void poll_port(uint32_t now)
{
  static uint32_t last_time = 0;
  
  if(now - last_time < 30)
  {
    return;
  }

  last_time = now;

  auto evs = prt2.poll();

  //loop 1:
  if(evs.get(0) == 1)
  {
    loops.play_lp(0);
  }

  if(evs.get(1) == 1)
  {
    loops.record_lp(0);
  }

  if(evs.get(2) == 1)
  {
    loops.od_lp(0);
  }

  if(evs.get(3) == 1)
  {
    loops.oneshot_lp(0);
  }

  //loop 2:
  if(evs.get(4) == 1)
  {
    loops.play_lp(1);
  }

  if(evs.get(5) == 1)
  {
    loops.record_lp(1);
  }

  if(evs.get(6) == 1)
  {
    loops.od_lp(1);
  }

  if(evs.get(7) == 1)
  {
    loops.oneshot_lp(1);
  }

  evs = prt.poll();

  //loop 3:
  if(evs.get(0) == 1)
  {
    loops.play_lp(2);
  }

  if(evs.get(1) == 1)
  {
    loops.record_lp(2);
  }

  if(evs.get(2) == 1)
  {
    loops.od_lp(2);
  }

  if(evs.get(3) == 1)
  {
    loops.oneshot_lp(2);
  }

  //loop 4:
  if(evs.get(4) == 1)
  {
    loops.play_lp(3);
  }

  if(evs.get(5) == 1)
  {
    loops.record_lp(3);
  }

  if(evs.get(6) == 1)
  {
    loops.od_lp(3);
  }

  if(evs.get(7) == 1)
  {
    loops.oneshot_lp(3);
  }
}

void poll_encoders(uint32_t now)
{
  static uint32_t last_time = 0;
  
  if(now - last_time < 1)
  {
    return;
  }
  
  last_time = now;

  int code1_turn = code1.poll();
  int code2_turn = code2.poll();
  int code3_turn = code3.poll();
  int code4_turn = code4.poll();

  if(code1_turn != 0){
    screen.knob_turn(0,code1_turn);
  }

  if(code2_turn != 0){
    screen.knob_turn(1,code2_turn);
  }

  if(code3_turn != 0){
    screen.knob_turn(2,code3_turn);
  }

  if(code4_turn != 0){
    screen.knob_turn(3,code4_turn);
  }

  screen.update();
}

void poll_encoder_btns(uint32_t now)
{
  static uint32_t last_time = 0;
  
  if(now - last_time < 30)
  {
    return;
  }
  
  last_time = now;

  int code1_btn = code1.poll_btn();
  int code2_btn = code2.poll_btn();
  int code3_btn = code3.poll_btn();
  int code4_btn = code4.poll_btn();

  if(code1_btn == 1)
  {
    screen.knob_click(0);
  }
  
  if(code2_btn == 1)
  {
    screen.knob_click(1);
  }
   
  if(code3_btn == 1)
  {
    screen.knob_click(2);
  }
 
  if(code4_btn == 1)
  {
    screen.knob_click(3);
  }

  screen.update();
}

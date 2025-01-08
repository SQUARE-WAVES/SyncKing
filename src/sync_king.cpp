#include "daisy_seed.h"
#include "globals.h"
#include "tasks.h"

using namespace daisy;
using namespace daisy::seed;

bool has_tick = false;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
  for(size_t i=0;i<size;++i)
  {
    out[0][i] = in[0][i];
    out[1][i] = in[1][i];
  }

  has_tick |= loops.fill_buffs(in,out,size);
}

int main(void)
{
  init_globals();
  hw.StartAudio(AudioCallback);
  midi.start_recv();

  main_loop:
  {
    uint32_t now = System::GetNow();
    status_blink(now);
    port_blink(now);
    poll_port(now);
    poll_looper();
    poll_encoders(now);
    poll_encoder_btns(now);

    if(has_tick)
    {
      midi.send_tick();
      has_tick = false;
    }

    //midi.poll(hw);

  }
  goto main_loop;
}

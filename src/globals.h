#pragma once

#include "daisy_seed.h"
#include "devices/io_port.h"
#include "devices/knobs.h"
#include "devices/encoder.h"
#include "devices/dma_oled.h"
#include "devices/midi.h"
#include "audio/looper.h"
#include "interface.h"

extern daisy::DaisySeed hw;

extern io_port prt;
extern io_port prt2;
//extern knob_set knobs;
extern encoder code1;
extern encoder code2;
extern encoder code3;
extern encoder code4;
extern dma_oled oled;
extern midi_guy midi;
extern looper loops;

extern screen_set screen;

void init_globals();

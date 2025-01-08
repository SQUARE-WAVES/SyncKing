#pragma once
#include "daisy_seed.h"

class midi_guy
{
  daisy::MidiUartHandler midi;

  public:
  void init()
  {
    daisy::MidiUartHandler::Config midi_cfg;
    midi_cfg.transport_config.periph = daisy::UartHandler::Config::Peripheral::USART_1;
    midi_cfg.transport_config.rx = daisy::seed::D14;
    midi_cfg.transport_config.tx = daisy::seed::D13;
    midi.Init(midi_cfg);
  }

  void send_start()
  {
    static uint8_t msg = 0xFA;
    midi.SendMessage(&msg,1);
  }

  void send_stop()
  {
    static uint8_t msg = 0xFC;
    midi.SendMessage(&msg,1);
  }

  void send_tick()
  {
    static uint8_t msg = 0xF8;
    midi.SendMessage(&msg,1);
  }

  void start_recv()
  {
    midi.StartReceive();
  }

  void poll(daisy::DaisySeed& hw) 
  {
    midi.Listen();

    while(midi.HasEvents())
    {
      auto msg = midi.PopEvent();
      switch(msg.type)
      {
        case daisy::NoteOn:
        {
          auto note_msg = msg.AsNoteOn();
          hw.Print("note on: nn:%X vel:%X\n",note_msg.note,note_msg.velocity);
          break;
        };

        default: 
        {
          break;
        }
      }
    }
  }
};

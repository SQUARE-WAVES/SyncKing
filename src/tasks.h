#pragma once

void status_blink(uint32_t now);
void port_blink(uint32_t now);
void poll_port(uint32_t now);
void poll_looper();
void poll_encoders(uint32_t now);
void poll_encoder_btns(uint32_t now);

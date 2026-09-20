// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

void oled_init_addedoled(void);
bool oled_task_addedoled(void);
void oled_interrupt(uint16_t keycode);
void oled_tempch(bool on, uint16_t keycode);
void oled_write_frame(const char *frame);                     // full 128x32 frame (RAM or PROGMEM)
void oled_write_layer_digit(uint8_t layer);                   // pre-rendered big digit, layers 0..9
void oled_write_layer_label(const char *label);               // upright portrait label, 4x glyphs stacked
void oled_write_scaled_line(const char *text, uint8_t scale); // one sideways text line, scaled and centred


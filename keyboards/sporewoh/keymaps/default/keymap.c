/*
Copyright 2022 sporewoh
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x10(
    KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,  KC_Y,  KC_U,          KC_I,         KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,     KC_G,  KC_H,  KC_J,          KC_K,         KC_L,    KC_COLON,
    KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,  KC_N,  KC_M,          KC_COMM,      KC_DOT,  KC_SLSH,
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPACE, TT(1), TT(2), OSM(MOD_LSFT), KC_BACKSPACE, KC_ESC,  KC_ENTER),
  [1] = LAYOUT_ortho_4x10(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,       KC_ASTR,       KC_LPRN, KC_RPRN,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,       KC_PLUS,       KC_LCBR, KC_RCBR,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  LSFT(KC_NUHS), LSFT(KC_NUBS), KC_PIPE, LSFT(KC_QUOT),
    KC_HOME, KC_END, KC_PAGE_UP, KC_PAGE_DOWN, TG(1), TT(3),   KC_LEFT,       KC_DOWN,       KC_UP,   KC_RIGHT),
  [2] = LAYOUT_ortho_4x10(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
    KC_TAB, LCG(KC_1), LCG(KC_2), LCG(KC_3), LCG(KC_4), LCG(KC_5), KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,
    LSFT(KC_BACKSLASH), LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), KC_NUHS, KC_NUBS, KC_BSLS, KC_QUOT,
    KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_TRNS, TT(3), TG(2), KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_BRIGHTNESS_UP),
  [3] = LAYOUT_ortho_4x10(
    QK_BOOT, AC_TOGG, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MS_WHLD,   MS_UP,   MS_WHLU,
    QK_DEBUG_TOGGLE,   AC_ON,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MS_LEFT,   MS_DOWN,   MS_RGHT,   KC_NO,
    QK_REBOOT,   AC_OFF,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MS_BTN1,   MS_BTN2,   MS_BTN3,
    TG(0),   KC_NO,   KC_NO,   KC_NO,   TG(1),   TG(2),   KC_NO,   KC_NO,   KC_NO,   KC_NO),
  [4] = LAYOUT_ortho_4x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),
  [5] = LAYOUT_ortho_4x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),
  [6] = LAYOUT_ortho_4x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),
  [7] = LAYOUT_ortho_4x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),
  [8] = LAYOUT_ortho_4x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),
  [9] = LAYOUT_ortho_4x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

// Temporary LED chain diagnostic for the KillerWhale DUO.
//
// Colours each half's 33 LEDs in blocks so the chain index can be counted by
// eye: 0-9 red, 10-19 green, 20-29 blue, 30-32 yellow. Both halves show the
// same blocks, so count within the half. The first dark LED is where the data
// chain breaks; everything after it is dark because each LED regenerates the
// signal for the next one.
//
// Build and flash:  qmk flash -kb killerwhale/duo -km ledtest   (once per half)
// Go back with:     qmk flash -kb killerwhale/duo -km miryoku

#include QMK_KEYBOARD_H
#include "lib/common_killerwhale.h"
#include "lib/add_oled.h"

#define LEDS_PER_HALF 33
#define LED_LVL 60 // dim enough to look at, bright enough to see through the caps

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Plain QWERTY so the board still types while testing.
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_NO,
        KC_DEL, KC_SPC,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT,
        KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_RSFT,
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        KC_NO,
        KC_SPC, KC_DEL,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO
    ),
};
// clang-format on

static void apply_test_pattern(void) {
    for (uint8_t half = 0; half < 2; half++) {
        uint8_t base = half * LEDS_PER_HALF;
        rgblight_setrgb_range(LED_LVL, 0, 0, base + 0, base + 10);       // red
        rgblight_setrgb_range(0, LED_LVL, 0, base + 10, base + 20);      // green
        rgblight_setrgb_range(0, 0, LED_LVL, base + 20, base + 30);      // blue
        rgblight_setrgb_range(LED_LVL, LED_LVL, 0, base + 30, base + LEDS_PER_HALF); // yellow
    }
}

// The board lib paints a solid per-layer colour over the whole strip on every
// rgblight_set(), so the layer overlays have to be held off or they would hide
// the pattern.
static void suppress_layer_lighting(void) {
    kw_config.rgb_layers = false;
    for (uint8_t i = 0; i < 10; i++) {
        rgblight_set_layer_state(i, false);
    }
}

void pointing_device_init_user(void) {
    set_auto_mouse_enable(false);
    suppress_layer_lighting(); // runs after the lib loads kw_config from EEPROM
}

// Re-apply twice a second so nothing the lib does can leave the pattern hidden.
void housekeeping_task_user(void) {
    static uint16_t last = 0;
    if (timer_elapsed(last) < 500) {
        return;
    }
    last = timer_read();
    suppress_layer_lighting();
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    apply_test_pattern();
}

// Same right-panel mirror as the miryoku keymap, so the displays are not
// confusing during the test.
static void orient_right_oled(void) {
    static uint8_t  attempts = 0;
    static uint16_t last     = 0;
    if (attempts >= 10 || !gpio_read_pin(SPLIT_HAND_PIN)) {
        return;
    }
    if (attempts > 0 && timer_elapsed(last) < 500) {
        return;
    }
    last = timer_read();
    attempts++;
    oled_set_panel_flip(true, false);
    oled_clear();
}

bool oled_task_user(void) {
    orient_right_oled();
    return true; // lib draws
}

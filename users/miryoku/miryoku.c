#include QMK_KEYBOARD_H

// Thumb layer-taps (ESC SPC TAB | ENT BSPC DEL) get quick tap so tap-then-hold
// auto-repeats space, backspace and friends. Home row mods and the Z / slash
// button-layer taps keep 0 so a letter followed by a quick hold is still the
// modifier or layer.
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_LAYER_TAP(keycode)) {
        switch (QK_LAYER_TAP_GET_TAP_KEYCODE(keycode)) {
            case KC_ESC:
            case KC_SPC:
            case KC_TAB:
            case KC_ENT:
            case KC_BSPC:
            case KC_DEL:
                return TAPPING_TERM;
        }
    }
    return 0;
}

// Miryoku layout for KillerWhale DUO
// Based on https://github.com/manna-harbour/miryoku
// Aligned with the keyball39 Miryoku keymap, adapted for KillerWhale
// trackball / dpad / encoder / OLED author lib.

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"
#include "lib/common_killerwhale.h"
#include "lib/add_oled.h"

enum custom_keycodes {
    SCRL_BTN = SAFE_RANGE, // tap = middle click, hold = scroll mode
    GAME_TOG,              // latching switch: pressed = game layer, released = base
};

// Layer definitions
enum layers { U_BASE, U_EXTRA, U_TAP, U_BUTTON, U_NAV, U_MOUSE, U_MEDIA, U_NUM, U_SYM, U_FUN, U_KW, U_GAME };

// Home row mod shortcuts
#define HRM_A LGUI_T(KC_A)
#define HRM_S LALT_T(KC_S)
#define HRM_D LCTL_T(KC_D)
#define HRM_F LSFT_T(KC_F)
#define HRM_J RSFT_T(KC_J)
#define HRM_K RCTL_T(KC_K)
#define HRM_L LALT_T(KC_L)
#define HRM_QUOT RGUI_T(KC_QUOT)

// Thumb keys
#define TH_ESC LT(U_MEDIA, KC_ESC)
#define TH_SPC LT(U_NAV, KC_SPC)
#define TH_TAB LT(U_MOUSE, KC_TAB)
#define TH_ENT LT(U_SYM, KC_ENT)
#define TH_BSPC LT(U_NUM, KC_BSPC)
#define TH_DEL LT(U_FUN, KC_DEL)

// Encoder map helpers (8 encoders: 4 per half)
#define ENC_SCROLL ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD)

#define ENC_VOLUME ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)

#define ENC_PAGETURN ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer (QWERTY with home row mods)
     * Left:  ESC 1 2 3 4 5 | TAB Q W E R T | LCTL A S D F G | Z X C V B | _
     *        MEDIA NAV | UP DN LT RT _ | MOUSE BTN1 GAME
     * Right: 6 7 8 9 0 BSPC | Y U I O P ENT | H J K L ; RCTL | N M , . / | _
     *        FUN NUM | _ _ _ _ _ | SYM BTN1 EXTRA
     */
    [U_BASE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        OSM(MOD_LCTL), HRM_A, HRM_S, HRM_D, HRM_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        SCRL_BTN,
        TH_ESC, TH_SPC,
        KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT, L_CHMOD,
        TH_TAB, MS_BTN1, MO(U_EXTRA),

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT,
        KC_H, HRM_J, HRM_K, HRM_L, HRM_QUOT, OSM(MOD_RCTL),
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        SCRL_BTN,
        TH_BSPC, TH_DEL,
        _______, _______, _______, _______, R_CHMOD,
        MS_BTN1, TH_ENT, GAME_TOG
    ),

    /*
     * Extra Layer (clean QWERTY, no home row mods)
     */
    [U_EXTRA] = LAYOUT(
        TO(U_BASE), KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        _______,
        KC_DEL, KC_SPC,
        _______, _______, _______, _______, _______,
        _______, _______, _______,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT,
        KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_RSFT,
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        _______,
        KC_SPC, KC_DEL,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Tap Layer (no home row mods; mods on the side keys)
     */
    [U_TAP] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        _______,
        KC_LGUI, KC_LALT,
        _______, _______, _______, _______, _______,
        KC_LCTL, KC_LGUI, _______,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT,
        KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_RSFT,
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        _______,
        KC_RCTL, KC_RGUI,
        _______, _______, _______, _______, _______,
        KC_RALT, KC_RCTL, _______
    ),

    /*
     * Button Layer (clipboard + mouse buttons)
     */
    [U_BUTTON] = LAYOUT(
        UNDO, CUT, COPY, PASTE, REDO, _______,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, _______,
        UNDO, CUT, COPY, PASTE, REDO, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        MS_BTN3, MS_BTN1, MS_BTN2,

        REDO, PASTE, COPY, CUT, UNDO, _______,
        _______, _______, _______, KC_RSFT, KC_RCTL, KC_RGUI,
        REDO, PASTE, COPY, CUT, UNDO, _______,
        _______, _______, _______, _______, _______,
        _______,
        MS_BTN2, MS_BTN3,
        _______, _______, _______, _______, _______,
        MS_BTN1, MS_BTN2, MS_BTN3
    ),

    /*
     * Navigation Layer
     */
    [U_NAV] = LAYOUT(
        QK_BOOT, _______, TO(U_EXTRA), TO(U_BASE), _______, _______,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, CW_TOGG,
        _______, KC_RALT, MO(U_NUM), MO(U_NAV), _______, KC_INS,
        _______, _______, _______, _______, _______,
        _______,
        _______, _______,
        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
        _______, _______, _______,

        _______, _______, _______, _______, _______, QK_BOOT,
        KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Mouse Layer (trackball handles most; buttons here)
     */
    [U_MOUSE] = LAYOUT(
        QK_BOOT, _______, TO(U_EXTRA), TO(U_BASE), _______, _______,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, _______,
        _______, KC_RALT, MO(U_SYM), _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        MS_BTN2, MS_BTN1, MS_BTN3,

        _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_RSFT, KC_RCTL, KC_RGUI,
        _______, _______, _______, _______, _______,
        _______,
        MS_BTN2, MS_BTN3,
        _______, _______, _______, _______, _______,
        MS_BTN1, MS_BTN2, MS_BTN3
    ),

    /*
     * Media Layer
     */
    [U_MEDIA] = LAYOUT(
        QK_BOOT, _______, TO(U_EXTRA), TO(U_BASE), _______, _______,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, _______,
        _______, KC_RALT, MO(U_FUN), MO(U_MEDIA), _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______,

        UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, QK_BOOT,
        _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        KC_MSTP, KC_MPLY,
        _______, _______, _______, _______, _______,
        KC_MUTE, _______, _______
    ),

    /*
     * Number Layer
     */
    [U_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC, _______,
        KC_SCLN, KC_4, KC_5, KC_6, KC_EQL, _______,
        KC_GRV, KC_1, KC_2, KC_3, KC_BSLS,
        _______,
        KC_DOT, KC_0,
        _______, _______, _______, _______, _______,
        KC_MINS, _______, _______,

        _______, TO(U_BASE), TO(U_EXTRA), _______, _______, QK_BOOT,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, MO(U_NUM), MO(U_NAV), KC_RALT, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Symbol Layer
     */
    [U_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, _______,
        KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, _______,
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,
        _______,
        KC_LPRN, KC_RPRN,
        _______, _______, _______, _______, _______,
        KC_UNDS, _______, _______,

        _______, TO(U_BASE), TO(U_EXTRA), _______, _______, QK_BOOT,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, MO(U_SYM), MO(U_MOUSE), KC_RALT, _______, _______,
        KC_UNDS, _______, _______, _______, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Function Layer
     */
    [U_FUN] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, _______,
        KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL, _______,
        KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,
        _______,
        KC_APP, KC_SPC,
        _______, _______, _______, _______, _______,
        KC_TAB, _______, _______,

        _______, TO(U_BASE), TO(U_EXTRA), _______, _______, QK_BOOT,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, MO(U_FUN), MO(U_MEDIA), KC_RALT, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        KC_TAB, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * KillerWhale Layer (trackball / dpad / encoder settings)
     * Q or ESC returns to BASE
     */
    [U_KW] = LAYOUT(
        TO(U_BASE), _______, _______, QK_USER_14, _______, L_CHMOD,
        _______, _______, _______, _______, L_SPD_I, _______,
        AUTO_MOUSE, _______, _______, L_ANG_D, L_INV, L_ANG_I,
        _______, _______, _______, L_SPD_D, _______,
        INV_SCRL,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, INV_SCRL, _______,

        R_CHMOD, _______, QK_USER_14, _______, _______, _______,
        _______, R_SPD_I, _______, _______, _______, _______,
        R_ANG_D, R_INV, R_ANG_I, _______, _______, AUTO_MOUSE,
        _______, R_SPD_D, _______, _______, _______,
        INV_SCRL,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Game Layer (left-hand WASD; right hand on a separate mouse)
     * Activated by the left toggle switch.
     * Row1: 1-5 weapons | Row2: W move | Row3: A S D move
     * Dpad = arrows | thumb-side keys = Ctrl / Shift
     */
    [U_GAME] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        _______,
        KC_LCTL, KC_SPC,
        KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT, _______,
        MS_BTN2, MS_BTN1, _______,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT,
        KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_RSFT,
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        _______,
        KC_BSPC, KC_DEL,
        _______, _______, _______, _______, _______,
        MS_BTN1, MS_BTN2, GAME_TOG
    ),
};
// clang-format on

// Encoder map: scroll by default; volume on MEDIA; page-turn on NAV.
// All 8 encoders mapped so the two installed ADD-unit wheels work
// regardless of which rotary index they sit on.
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [U_BASE] = {ENC_SCROLL}, [U_EXTRA] = {ENC_SCROLL}, [U_TAP] = {ENC_SCROLL}, [U_BUTTON] = {ENC_SCROLL}, [U_NAV] = {ENC_PAGETURN}, [U_MOUSE] = {ENC_SCROLL}, [U_MEDIA] = {ENC_VOLUME}, [U_NUM] = {ENC_SCROLL}, [U_SYM] = {ENC_SCROLL}, [U_FUN] = {ENC_SCROLL}, [U_KW] = {ENC_SCROLL}, [U_GAME] = {ENC_SCROLL},
};

// Combos for missing thumb keys and layer escape
const uint16_t PROGMEM fun_combo[]  = {TH_ENT, TH_BSPC, COMBO_END};
const uint16_t PROGMEM kw_combo[]   = {TH_ESC, TH_SPC, COMBO_END};
const uint16_t PROGMEM tap_combo[]  = {TH_TAB, TH_ENT, COMBO_END};
const uint16_t PROGMEM base_combo[] = {KC_LGUI, KC_RGUI, COMBO_END};
combo_t                key_combos[] = {
    COMBO(fun_combo, MO(U_FUN)),   // ENT + BSPC = Fun layer
    COMBO(kw_combo, TO(U_KW)),     // ESC + SPC = toggle to KillerWhale layer
    COMBO(tap_combo, TO(U_TAP)),   // TAB + ENT = toggle to Tap layer
    COMBO(base_combo, TO(U_BASE)), // outer bottom keys = escape to BASE
};

// Key overrides: Shift+Backspace = Delete
const key_override_t  shift_backspace_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t *key_overrides[]        = {&shift_backspace_delete, NULL};

// Board-level joystick detection global. The GP27/GP28 pins can false-positive
// when no joystick is installed, which makes the slave OLED show “Please attach
// USB cable this side.” Force it off for this trackball-only keymap.
extern uint8_t joystick_attached;

// Keep the trackball from yanking the keymap into the mouse layer while typing,
// and split the OLEDs: master = stats, slave = layer number.
void pointing_device_init_user(void) {
    set_auto_mouse_enable(false);
    kw_config.oled_mode = false;
    joystick_attached = NO_JOYSTICK;
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    return keycode == SCRL_BTN;
}

static bool scrl_btn_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t scrl_btn_timer;
    if (keycode == GAME_TOG) {
        // The physical TOG is latching: it only generates a key press in one
        // direction and a key release in the other. Track the switch state
        // directly instead of using TO(), which fires on press only.
        if (record->event.pressed) {
            layer_on(U_GAME);
        } else {
            layer_off(U_GAME);
        }
        return false;
    }
    if (keycode == SCRL_BTN) {
        if (record->event.pressed) {
            scrl_btn_timer = timer_read();
            scrl_btn_held = true;
            is_scroll_mode(true);
            oled_tempch(true, MOD_SCRL);
        } else {
            scrl_btn_held = false;
            is_scroll_mode(get_highest_layer(layer_state) == U_MOUSE);
            if (timer_elapsed(scrl_btn_timer) < TAPPING_TERM) {
                tap_code(MS_BTN3);
            }
            oled_tempch(false, MOD_SCRL);
        }
        return false;
    }
    return true;
}

static const char *const layer_names[] = {"BASE", "EXTRA", "TAP", "BTN", "NAV", "MOUSE", "MEDIA", "NUM", "SYM", "FUN", "KW", "GAME"};

static void oled_write_line(uint8_t line, const char *text, bool center) {
    char buf[17];
    if (center) {
        uint8_t len = strlen(text);
        uint8_t pad = (len < 16) ? (16 - len) / 2 : 0;
        uint8_t i   = 0;
        while (pad--) {
            buf[i++] = ' ';
        }
        for (uint8_t j = 0; text[j] && i < 16; ++j) {
            buf[i++] = text[j];
        }
        while (i < 16) {
            buf[i++] = ' ';
        }
    } else {
        snprintf(buf, sizeof(buf), "%-16.16s", text);
    }
    buf[16] = 0;
    oled_set_cursor(0, line);
    oled_write(buf, true);
}

static const char *pointing_mode_name(uint8_t mode) {
    if (mode == SCROLL_MODE) {
        return "SCROL";
    }
    if (mode == CURSOR_MODE) {
        return "CURSR";
    }
    if (mode == GAME_MODE) {
        return "GAME";
    }
    return "KEY";
}

// Master OLED: layer name + stats. Slave OLED: layer name. Overwrite all four
// text lines instead of calling oled_clear() every frame; with the default
// OLED_UPDATE_PROCESS_LIMIT the full clear never reaches the lower blocks.
bool oled_task_user(void) {
    uint8_t cur_layer = get_highest_layer(layer_state);
    char    buf[16];

    if (!is_keyboard_master()) {
        oled_write_line(0, "LAYER", false);
        if (cur_layer < sizeof(layer_names) / sizeof(layer_names[0])) {
            oled_write_line(1, layer_names[cur_layer], true);
        } else {
            snprintf(buf, sizeof(buf), "%u", (unsigned)cur_layer);
            oled_write_line(1, buf, true);
        }
        oled_write_line(2, "", false);
        oled_write_line(3, "", false);
        return true;
    }

    if (cur_layer < sizeof(layer_names) / sizeof(layer_names[0])) {
        snprintf(buf, sizeof(buf), "LAYER: %s", layer_names[cur_layer]);
    } else {
        snprintf(buf, sizeof(buf), "LAYER: %u", (unsigned)cur_layer);
    }
    oled_write_line(0, buf, false);

    snprintf(buf, sizeof(buf), "SPD %u/%u", 400 + (unsigned)kw_config.spd_l * 200, 400 + (unsigned)kw_config.spd_r * 200);
    oled_write_line(1, buf, false);

    snprintf(buf, sizeof(buf), "ANG %u/%u", (unsigned)kw_config.angle_l * 12, (unsigned)kw_config.angle_r * 12);
    oled_write_line(2, buf, false);

    uint8_t mod_state = get_mods();
    if (mod_state) {
        snprintf(buf, sizeof(buf), "MOD %c%c%c%c",
                 (mod_state & MOD_MASK_SHIFT) ? 'S' : ' ',
                 (mod_state & MOD_MASK_CTRL) ? 'C' : ' ',
                 (mod_state & MOD_MASK_ALT) ? 'A' : ' ',
                 (mod_state & MOD_MASK_GUI) ? 'G' : ' ');
    } else {
        snprintf(buf, sizeof(buf), "L:%s R:%s", pointing_mode_name(kw_config.pd_mode_l), pointing_mode_name(kw_config.pd_mode_r));
    }
    oled_write_line(3, buf, false);

    return true;
}

// Flush RGB immediately when the layer state changes so layer colors do not
// wait for the next animation tick.
void housekeeping_task_user(void) {
    static layer_state_t last_layer_state = 0;
    if (layer_state != last_layer_state) {
        last_layer_state = layer_state;
        // Keyball-style: holding the mouse layer switches the trackball to scroll mode.
        is_scroll_mode(scrl_btn_held || get_highest_layer(layer_state) == U_MOUSE);
        uint8_t mode     = rgblight_get_mode();
        if (mode == 0) {
            return;
        }
        if (kw_config.rgb_layers && (layer_state & 0x03FE)) {
            rgblight_set();
        } else if (mode == RGBLIGHT_MODE_STATIC_LIGHT) {
            rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
        } else {
#ifdef RGBLIGHT_USE_TIMER
            animation_status.last_timer = sync_timer_read();
#endif
        }
    }
}

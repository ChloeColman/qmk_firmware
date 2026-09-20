// Miryoku layout for KillerWhale DUO
// Based on https://github.com/manna-harbour/miryoku
// The 3x5 alpha block on each half is identical to the keyball39 Miryoku
// keymap. The extra KillerWhale keys (number row, outer column, dpad, scroll
// button, side/ADD/TOG switches) carry board-specific extras.

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"
#include "lib/common_killerwhale.h"
#include "lib/add_oled.h"
#include "bongo_frames.h"

enum custom_keycodes {
    SCRL_BTN = SAFE_RANGE, // tap = middle click, hold = scroll mode
    OLED_VIEW,             // cycle the USB half's display view (KW layer, O key)
};

// Layer definitions. Thumb hold layers first, in thumb order left to right
// (ESC SPC TAB | right-click BSPC ENT = 1..6), so the layer digit on the
// non-USB half's OLED reads sensibly. Then the toggled alpha variants (7..9), then the board layers.
enum layers { U_BASE, U_MEDIA, U_NAV, U_MOUSE, U_FUN, U_NUM, U_SYM, U_EXTRA, U_TAP, U_BUTTON, U_KW, U_GAME };

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
#define TH_BTN2 LT(U_FUN, MS_BTN2) // tap = right click, hold = Fun layer

// Button layer keys
#define BTN_Z LT(U_BUTTON, KC_Z)
#define BTN_SLSH LT(U_BUTTON, KC_SLSH)

// Encoder map helpers (8 encoders: 4 per half)
#define ENC_SCROLL ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLU, MS_WHLD)

#define ENC_VOLUME ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)

#define ENC_PAGETURN ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)

// clang-format off
/*
 * LAYOUT() argument order per half:
 *   row 1: outer + 5 (ESC 1 2 3 4 5   |  6 7 8 9 0 BSPC)
 *   row 2: outer + 5 (TAB Q W E R T   |  Y U I O P ENT)
 *   row 3: outer + 5 (CMD A S D F G   |  H J K L ' SHIFT)
 *   row 4:         5 (    Z X C V B   |  N M , . /     )
 *   SCROLL
 *   SIDE1 SIDE2                (left: ESC SPC  | right: BSPC ENT; SIDE1 is the lower key on the right)
 *   DPAD up down left right, JOYSW
 *   ADD1 ADD2 TOG              (left: TAB btn1 | right: btn1 btn2/FUN)
 *
 * Miryoku thumbs: left SIDE1/SIDE2/ADD1 = ESC SPC TAB, right SIDE2/SIDE1 = ENT BSPC,
 * Fun layer on hold of the right-click key, plain DEL on the right outer-bottom
 * pinky key (the keyball's far-right thumb).
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer (QWERTY with home row mods)
     */
    [U_BASE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        OSM(MOD_LCTL), HRM_A, HRM_S, HRM_D, HRM_F, KC_G,
        BTN_Z, RALT_T(KC_X), KC_C, KC_V, KC_B,
        SCRL_BTN,
        TH_ESC, TH_SPC,
        KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT, L_CHMOD,
        TH_TAB, MS_BTN1, MO(U_EXTRA),

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT,
        KC_H, HRM_J, HRM_K, HRM_L, HRM_QUOT, KC_DEL,
        KC_N, KC_M, KC_COMM, RALT_T(KC_DOT), BTN_SLSH,
        SCRL_BTN,
        TH_BSPC, TH_ENT,
        _______, _______, _______, _______, R_CHMOD,
        MS_BTN1, TH_BTN2, MO(U_GAME)
    ),

    /*
     * Media Layer
     */
    [U_MEDIA] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, QK_BOOT, _______, TO(U_EXTRA), TO(U_BASE), _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
        _______, KC_RALT, TO(U_FUN), TO(U_MEDIA), _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______,

        _______, _______, _______, _______, _______, _______,
        UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, _______,
        _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE,
        _______, _______, _______, _______, _______,
        _______,
        KC_MPLY, KC_MSTP,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Navigation Layer
     */
    [U_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, QK_BOOT, _______, TO(U_EXTRA), TO(U_BASE), _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
        _______, KC_RALT, TO(U_NUM), TO(U_NAV), _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______,

        _______, _______, _______, _______, _______, _______,
        REDO, PASTE, COPY, CUT, UNDO, _______,
        CW_TOGG, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DEL,
        KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
        _______,
        KC_BSPC, KC_ENT,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Mouse Layer (trackball scrolls while held; buttons on J K L and the right thumbs)
     */
    [U_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, QK_BOOT, _______, TO(U_EXTRA), TO(U_BASE), _______,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
        _______, KC_RALT, TO(U_SYM), TO(U_MOUSE), _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______,

        _______, _______, _______, _______, _______, _______,
        REDO, PASTE, COPY, CUT, UNDO, _______,
        _______, MS_BTN1, MS_BTN2, MS_BTN3, _______, MS_BTN3,
        _______, _______, _______, _______, _______,
        _______,
        MS_BTN1, MS_BTN2,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Function Layer
     */
    [U_FUN] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,
        _______, KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL,
        KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,
        _______,
        KC_APP, KC_SPC,
        _______, _______, _______, _______, _______,
        KC_TAB, _______, _______,

        _______, _______, _______, _______, _______, _______,
        _______, TO(U_BASE), TO(U_EXTRA), _______, QK_BOOT, _______,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, TO(U_FUN), TO(U_MEDIA), KC_RALT, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Number Layer
     */
    [U_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,
        _______, KC_SCLN, KC_4, KC_5, KC_6, KC_EQL,
        KC_GRV, KC_1, KC_2, KC_3, KC_BSLS,
        _______,
        KC_DOT, KC_0,
        _______, _______, _______, _______, _______,
        KC_MINS, _______, _______,

        _______, _______, _______, _______, _______, _______,
        _______, TO(U_BASE), TO(U_EXTRA), _______, QK_BOOT, _______,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, TO(U_NUM), TO(U_NAV), KC_RALT, _______,
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
        _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,
        _______, KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,
        _______,
        KC_LPRN, KC_RPRN,
        _______, _______, _______, _______, _______,
        KC_UNDS, _______, _______,

        _______, _______, _______, _______, _______, _______,
        _______, TO(U_BASE), TO(U_EXTRA), _______, QK_BOOT, _______,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______, TO(U_SYM), TO(U_MOUSE), KC_RALT, _______,
        _______,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Extra Layer (clean QWERTY, no home row mods; left toggle switch)
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
     * Tap Layer (no home row mods; plain thumbs, mods on the outer column)
     * Enter with TAB+ENT combo, exit with LGUI+RGUI (the two top outer keys).
     */
    [U_TAP] = LAYOUT(
        KC_LGUI, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_LALT, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_Z, KC_X, KC_C, KC_V, KC_B,
        _______,
        KC_ESC, KC_SPC,
        _______, _______, _______, _______, _______,
        KC_TAB, _______, _______,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_RGUI,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_RSFT,
        KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_DEL,
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        _______,
        KC_BSPC, KC_ENT,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Button Layer (clipboard + mouse buttons)
     */
    [U_BUTTON] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, UNDO, CUT, COPY, PASTE, REDO,
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
        UNDO, CUT, COPY, PASTE, REDO,
        _______,
        MS_BTN3, MS_BTN1,
        _______, _______, _______, _______, _______,
        MS_BTN2, _______, _______,

        _______, _______, _______, _______, _______, _______,
        REDO, PASTE, COPY, CUT, UNDO, _______,
        _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, MS_BTN3,
        REDO, PASTE, COPY, CUT, UNDO,
        _______,
        MS_BTN1, MS_BTN2,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * KillerWhale Layer (trackball / dpad / encoder settings)
     * ESC returns to BASE. 5 / 6 cycle the left / right ball mode, O cycles
     * the USB half's display view.
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
        _______, R_SPD_I, _______, OLED_VIEW, _______, _______,
        R_ANG_D, R_INV, R_ANG_I, _______, _______, AUTO_MOUSE,
        _______, R_SPD_D, _______, _______, _______,
        INV_SCRL,
        _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /*
     * Game Layer (left-hand WASD; right hand on a separate mouse)
     * Held on by the right toggle switch (MO on the BASE layer).
     * Row1: 1-5 weapons | Row2: W move | Row3: A S D move
     * Dpad = arrows | thumb-side keys = Ctrl / Space
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
        MS_BTN1, MS_BTN2, _______
    ),
};
// clang-format on

// Encoder map: scroll by default; volume on MEDIA; page-turn on NAV.
// All 8 encoders mapped so the two installed ADD-unit wheels work
// regardless of which rotary index they sit on.
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [U_BASE] = {ENC_SCROLL}, [U_EXTRA] = {ENC_SCROLL}, [U_TAP] = {ENC_SCROLL}, [U_BUTTON] = {ENC_SCROLL}, [U_NAV] = {ENC_PAGETURN}, [U_MOUSE] = {ENC_SCROLL}, [U_MEDIA] = {ENC_VOLUME}, [U_NUM] = {ENC_SCROLL}, [U_SYM] = {ENC_SCROLL}, [U_FUN] = {ENC_SCROLL}, [U_KW] = {ENC_SCROLL}, [U_GAME] = {ENC_SCROLL},
};

// Combos for layer toggles and layer escape
const uint16_t PROGMEM kw_combo[]   = {TH_ESC, TH_SPC, COMBO_END};
const uint16_t PROGMEM tap_combo[]  = {TH_TAB, TH_ENT, COMBO_END};
const uint16_t PROGMEM base_combo[] = {KC_LGUI, KC_RGUI, COMBO_END};
combo_t                key_combos[] = {
    COMBO(kw_combo, TO(U_KW)),     // ESC + SPC = toggle to KillerWhale layer
    COMBO(tap_combo, TO(U_TAP)),   // TAB + ENT = toggle to Tap layer
    COMBO(base_combo, TO(U_BASE)), // LGUI + RGUI = escape to BASE
};

// Key overrides: Shift+Backspace = Delete
const key_override_t  shift_backspace_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t *key_overrides[]        = {&shift_backspace_delete, NULL};

// Board-level joystick detection global. The GP27/GP28 pins can false-positive
// when no joystick is installed, which makes the non-USB half's OLED show "Please attach
// USB cable this side." Force it off for this trackball-only keymap.
extern uint8_t joystick_attached;

// USB half display view, cycled with OLED_VIEW on the KW layer, kept in user EEPROM.
enum oled_view { VIEW_STATS, VIEW_WPM, VIEW_MIRROR, VIEW_NAME, VIEW_COUNT };

typedef union {
    uint32_t raw;
    struct {
        uint8_t oled_view : 2;
    };
} user_config_t;
static user_config_t user_config;

// Keep the trackball from yanking the keymap into the mouse layer while typing,
// and let the board lib drive the OLEDs: USB half = stats, other half = layer digit.
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
    if (keycode == OLED_VIEW) {
        if (record->event.pressed) {
            user_config.oled_view = (user_config.oled_view + 1) % VIEW_COUNT;
            eeconfig_update_user(user_config.raw);
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

// ---------------------------------------------------------------------------
// OLED. The board lib draws the big layer digit on the non-USB half and the
// trackball stats on the USB half. The keymap takes over a frame (returns
// false from oled_task_user) for layers without a digit and for the extra USB
// half views, cycled with OLED_VIEW and kept in user EEPROM. Frames are drawn
// in the left half's orientation; the lib mirrors the right half's panel.
// ---------------------------------------------------------------------------
static const char *const layer_names[] = {
    [U_BASE] = "Base", [U_MEDIA] = "Media", [U_NAV] = "Navigation", [U_MOUSE] = "Mouse", [U_FUN] = "Function", [U_NUM] = "Number", [U_SYM] = "Symbol", [U_EXTRA] = "Extra", [U_TAP] = "Tap", [U_BUTTON] = "Button", [U_KW] = "Settings", [U_GAME] = "Game",
};

void eeconfig_init_user(void) {
    user_config.raw = 0;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

// Key presses from both halves (seen through SPLIT_TRANSPORT_MIRROR) drive
// the bongo cat.
static uint8_t bongo_taps;

static void count_taps(void) {
    static matrix_row_t prev[MATRIX_ROWS];
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row_t row = matrix_get_row(r);
        if (row & ~prev[r]) {
            bongo_taps++;
        }
        prev[r] = row;
    }
}

static void render_bongo(void) {
    static uint8_t  seen      = 0;
    static uint16_t tap_timer = 0;
    static bool     paw_down  = false;
    static bool     left_paw  = false;
    if (bongo_taps != seen) {
        seen      = bongo_taps;
        paw_down  = true;
        left_paw  = !left_paw;
        tap_timer = timer_read();
    }
    if (paw_down && timer_elapsed(tap_timer) > 150) {
        paw_down = false;
    }
    oled_write_frame(paw_down ? (left_paw ? bongo_left : bongo_right) : bongo_idle);
}

// The layer view: bongo cat on GAME, upright label on KW, otherwise the lib's
// big digit. Returns true when the digit should be drawn by the caller.
static bool render_layer_view(uint8_t layer) {
    if (layer == U_GAME) {
        render_bongo();
    } else if (layer == U_KW) {
        oled_write_layer_label("KW");
    } else {
        return true;
    }
    return false;
}

// WPM history, one sample per 250 ms, newest last.
#define WPM_SAMPLES 64
#define WPM_MAX 120
static uint8_t wpm_hist[WPM_SAMPLES];

static void sample_wpm(void) {
    static uint16_t wpm_timer = 0;
    if (timer_elapsed(wpm_timer) < 250) {
        return;
    }
    wpm_timer   = timer_read();
    uint8_t wpm = get_current_wpm();
    memmove(wpm_hist, wpm_hist + 1, WPM_SAMPLES - 1);
    wpm_hist[WPM_SAMPLES - 1] = wpm > WPM_MAX ? WPM_MAX : wpm;
}

// Text line 0: layer name and current WPM. Pages 1..3: bar graph, 2px per
// sample, newest at the end (bottom of the panel), bars growing from the
// panel's outer edge toward the text.
static void render_wpm_view(uint8_t layer) {
    char buf[22];
    snprintf(buf, sizeof(buf), "%-10s WPM %3u", layer_names[layer], (unsigned)get_current_wpm());
    oled_set_cursor(0, 0);
    oled_write(buf, false);
    oled_advance_page(true);

    char graph[3 * OLED_DISPLAY_WIDTH] = {0};
    for (uint8_t i = 0; i < WPM_SAMPLES; i++) {
        uint8_t h = wpm_hist[i] * 24 / WPM_MAX;
        for (uint8_t y = 24 - h; y < 24; y++) {
            graph[(y / 8) * OLED_DISPLAY_WIDTH + i * 2] |= 1 << (y % 8);
            graph[(y / 8) * OLED_DISPLAY_WIDTH + i * 2 + 1] |= 1 << (y % 8);
        }
    }
    oled_set_cursor(0, 1);
    oled_write_raw(graph, sizeof(graph));
}

bool oled_task_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    if (!is_keyboard_master()) {
        return render_layer_view(layer);
    }
    switch (user_config.oled_view) {
        case VIEW_WPM:
            render_wpm_view(layer);
            return false;
        case VIEW_MIRROR:
            if (render_layer_view(layer)) {
                oled_write_layer_digit(layer);
            }
            return false;
        case VIEW_NAME:
            oled_write_scaled_line(layer_names[layer], 2);
            return false;
        default:
            return true; // lib draws the trackball stats
    }
}

// Flush RGB immediately when the layer state changes so layer colors do not
// wait for the next animation tick.
void housekeeping_task_user(void) {
    count_taps();
    if (is_keyboard_master()) {
        sample_wpm();
    }
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

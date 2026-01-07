/*
 * Miryoku config for Keyball39
 */

#pragma once

// Tapping term for home row mods
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Prevent accidental mod activation
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Enable caps word
#define CAPS_WORD_IDLE_TIMEOUT 5000

// Combo settings (ENT + BSPC = Fun layer)
#define COMBO_TERM 50

// Auto mouse layer settings (optional - trackball moves activate mouse layer)
// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// #define AUTO_MOUSE_DEFAULT_LAYER U_MOUSE
// #define AUTO_MOUSE_TIME 400

// Trackball settings
#define KEYBALL_CPI_DEFAULT 500
#define KEYBALL_SCROLL_DIV_DEFAULT 3

// Disable scroll snap entirely (bypass the feature)
#define KEYBALL_SCROLLSNAP_ENABLE 0

// Custom split transaction for bongo cat (added to QMK's internal enum)
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_BONGO

// RGB Light effects
#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE
#endif

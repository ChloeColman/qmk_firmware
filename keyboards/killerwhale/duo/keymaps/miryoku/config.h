#pragma once

// Home row mods: same feel as the keyball39 miryoku keymap.
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Auto mouse is disabled at init but can be toggled from the KW layer. Point it
// at U_MOUSE instead of the board default (layer 7, which is U_EXTRA here).
#undef AUTO_MOUSE_DEFAULT_LAYER
#define AUTO_MOUSE_DEFAULT_LAYER 3

// Each panel's view is chosen independently and keys are only processed on the
// USB half, so the pair of values is pushed to the other half.
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_OLED_VIEWS
// Makes the WPM graph work on the half without USB too.
#define SPLIT_WPM_ENABLE

// The board's steps are tiny against their caps: brightness moved 8 of 200 per
// press and hue 4 of 255, so a press looked like nothing happening. These give
// eight usable brightness steps and sixteen hue steps around the circle.
#undef RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 25
#undef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 16
#undef RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 16

// Trackball acceleration. The board scales movement by 1 + magnitude/10, capped
// at 3x, so a flick came out three times faster than the same distance moved
// slowly. That spread is what made it feel uncontrollable rather than the base
// speed, so the curve is flattened here instead of scaling everything down.
#undef KW_ACCEL_DIVISOR
#define KW_ACCEL_DIVISOR 30.0
#undef KW_ACCEL_MAX
#define KW_ACCEL_MAX 1.5

// With acceleration capped the top end came up short, so widen what the speed
// keys reach: 400 to 2800 instead of 400 to 1600, same number of steps.
#undef KW_CPI_STEP
#define KW_CPI_STEP 400

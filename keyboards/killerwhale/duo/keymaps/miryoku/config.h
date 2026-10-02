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

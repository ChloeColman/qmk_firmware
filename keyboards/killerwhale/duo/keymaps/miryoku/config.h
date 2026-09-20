#pragma once

// Home row mods: same feel as the keyball39 miryoku keymap.
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Auto mouse is disabled at init but can be toggled from the KW layer. Point it
// at U_MOUSE instead of the board default (layer 7, which is U_EXTRA here).
#undef AUTO_MOUSE_DEFAULT_LAYER
#define AUTO_MOUSE_DEFAULT_LAYER 3

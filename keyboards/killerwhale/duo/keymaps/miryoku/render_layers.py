#!/usr/bin/env python3
"""Render every layer of the KillerWhale DUO miryoku keymap to layers.svg / layers.png.

Reads the key geometry from ../../keyboard.json and the keycodes from keymap.c
in this directory, so it stays in sync with the firmware. Run from anywhere:

    python3 keyboards/killerwhale/duo/keymaps/miryoku/render_layers.py

PNG conversion uses rsvg-convert if present, otherwise only the SVG is written.
"""
import json
import re
import shutil
import subprocess
from pathlib import Path

HERE = Path(__file__).resolve().parent
KEYBOARD_JSON = HERE.parent.parent / "keyboard.json"
KEYMAP_C = HERE / "keymap.c"
OUT_SVG = HERE / "layers.svg"
OUT_PNG = HERE / "layers.png"

UNIT = 46          # px per key unit
PAD = 3            # gap inside a key unit
COLS = 2           # layers per row in the sheet
TITLE_H = 34
LAYER_GAP = 30

LAYER_SHORT = {
    "U_BASE": "Base", "U_MEDIA": "Media", "U_NAV": "Nav", "U_MOUSE": "Mouse", "U_FUN": "Fun",
    "U_NUM": "Num", "U_SYM": "Sym", "U_EXTRA": "Extra", "U_TAP": "Tap", "U_BUTTON": "Button",
    "U_KW": "Settings", "U_GAME": "Game",
}
LAYER_TITLE = {
    "U_BASE": "0 Base", "U_MEDIA": "1 Media  (hold Esc)", "U_NAV": "2 Navigation  (hold Space)",
    "U_MOUSE": "3 Mouse  (hold Tab)", "U_FUN": "4 Function  (hold right click)",
    "U_NUM": "5 Number  (hold Backspace)", "U_SYM": "6 Symbol  (hold Enter)",
    "U_EXTRA": "7 Extra  (left toggle switch)", "U_TAP": "8 Tap  (Tab+Enter chord)",
    "U_BUTTON": "9 Button  (hold Z or /)", "U_KW": "10 Settings  (Esc+Space chord)",
    "U_GAME": "11 Game  (right toggle switch)",
}

SIMPLE = {
    "KC_ESC": "Esc", "KC_TAB": "Tab", "KC_SPC": "Space", "KC_ENT": "Enter", "KC_BSPC": "Bksp", "KC_DEL": "Del",
    "KC_QUOT": "'", "KC_COMM": ",", "KC_DOT": ".", "KC_SLSH": "/", "KC_SCLN": ";", "KC_LBRC": "[", "KC_RBRC": "]",
    "KC_EQL": "=", "KC_GRV": "`", "KC_BSLS": "\\", "KC_MINS": "-", "KC_LCBR": "{", "KC_RCBR": "}", "KC_AMPR": "&",
    "KC_ASTR": "*", "KC_LPRN": "(", "KC_RPRN": ")", "KC_COLN": ":", "KC_DLR": "$", "KC_PERC": "%", "KC_CIRC": "^",
    "KC_PLUS": "+", "KC_TILD": "~", "KC_EXLM": "!", "KC_AT": "@", "KC_HASH": "#", "KC_PIPE": "|", "KC_UNDS": "_",
    "KC_PSCR": "PrtSc", "KC_SCRL": "ScrLk", "KC_PAUS": "Pause", "KC_APP": "Menu", "KC_INS": "Ins",
    "KC_HOME": "Home", "KC_END": "End", "KC_PGUP": "PgUp", "KC_PGDN": "PgDn",
    "KC_LEFT": "←", "KC_RIGHT": "→", "KC_RGHT": "→", "KC_UP": "↑", "KC_DOWN": "↓",
    "KC_LGUI": "Gui", "KC_RGUI": "Gui", "KC_LALT": "Alt", "KC_RALT": "AltGr", "KC_LCTL": "Ctrl", "KC_RCTL": "Ctrl",
    "KC_LSFT": "Shift", "KC_RSFT": "Shift",
    "KC_MPRV": "Prev", "KC_MNXT": "Next", "KC_VOLD": "Vol-", "KC_VOLU": "Vol+", "KC_MPLY": "Play", "KC_MSTP": "Stop",
    "KC_MUTE": "Mute", "UG_TOGG": "RGB", "UG_NEXT": "RGB fx", "UG_HUEU": "Hue+", "UG_SATU": "Sat+", "UG_VALU": "Val+",
    "CW_TOGG": "Caps Word", "QK_BOOT": "Boot",
    "MS_BTN1": "L click", "MS_BTN2": "R click", "MS_BTN3": "M click",
    "UNDO": "Undo", "CUT": "Cut", "COPY": "Copy", "PASTE": "Paste", "REDO": "Redo",
    "L_CHMOD": "Mode L", "R_CHMOD": "Mode R", "L_SPD_I": "Spd+ L", "L_SPD_D": "Spd- L", "R_SPD_I": "Spd+ R",
    "R_SPD_D": "Spd- R", "L_ANG_I": "Ang+ L", "L_ANG_D": "Ang- L", "R_ANG_I": "Ang+ R", "R_ANG_D": "Ang- R",
    "L_INV": "Inv X L", "R_INV": "Inv X R", "INV_SCRL": "Inv scrl", "AUTO_MOUSE": "Auto mouse",
    "QK_USER_14": "Dpad excl", "OLED_VIEW": "Display",
}
SUB_ONLY = {"SCRL_BTN": ("M click", "hold: scroll")}
MOD_TAP = {"LGUI_T": "Gui", "LALT_T": "Alt", "LCTL_T": "Ctrl", "LSFT_T": "Shift", "RSFT_T": "Shift", "RCTL_T": "Ctrl", "RGUI_T": "Gui", "RALT_T": "AltGr"}
OSM_NAMES = {"MOD_LCTL": "Ctrl", "MOD_RCTL": "Ctrl", "MOD_LSFT": "Shift", "MOD_LALT": "Alt", "MOD_LGUI": "Gui"}


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        if ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_keymap(text):
    defines = dict(re.findall(r"^#define (\w+) (.+?)(?://.*)?$", text, re.M))
    enum = re.search(r"enum layers \{(.*?)\};", text, re.S).group(1)
    layers_order = [x.strip() for x in enum.split(",") if x.strip()]
    body = text[text.index("keymaps[][MATRIX_ROWS][MATRIX_COLS] = {"):text.index("// clang-format on")]
    layers = {}
    for name, args in re.findall(r"\[(U_\w+)\] = LAYOUT\((.*?)\n    \),", body, re.S):
        args = re.sub(r"/\*.*?\*/", "", args, flags=re.S)
        args = re.sub(r"//.*", "", args)
        keys = split_args(args)
        assert len(keys) == 68, (name, len(keys))
        layers[name] = [defines.get(k, k).strip() for k in keys]
    return layers_order, layers


def legend(kc):
    """Return (main, sub) legend for a keycode string."""
    if kc in ("_______", "XXXXXXX"):
        return "", ""
    if kc in SUB_ONLY:
        return SUB_ONLY[kc]
    if kc in SIMPLE:
        return SIMPLE[kc], ""
    m = re.fullmatch(r"KC_([A-Z0-9])", kc)
    if m:
        return m.group(1), ""
    m = re.fullmatch(r"KC_F(\d+)", kc)
    if m:
        return "F" + m.group(1), ""
    m = re.fullmatch(r"(\w+_T)\((\w+)\)", kc)
    if m and m.group(1) in MOD_TAP:
        return legend(m.group(2))[0], MOD_TAP[m.group(1)]
    m = re.fullmatch(r"LT\((U_\w+), (\w+)\)", kc)
    if m:
        return legend(m.group(2))[0], LAYER_SHORT[m.group(1)]
    m = re.fullmatch(r"MO\((U_\w+)\)", kc)
    if m:
        return LAYER_SHORT[m.group(1)], "hold"
    m = re.fullmatch(r"TO\((U_\w+)\)", kc)
    if m:
        return "→ " + LAYER_SHORT[m.group(1)], ""
    m = re.fullmatch(r"OSM\((\w+)\)", kc)
    if m:
        return OSM_NAMES.get(m.group(1), m.group(1)), "one-shot"
    return kc.replace("KC_", ""), ""


def esc(s):
    return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")


def main():
    kb = json.loads(KEYBOARD_JSON.read_text())
    geometry = kb["layouts"]["LAYOUT"]["layout"]
    min_y = min(k["y"] for k in geometry)
    board_w = max(k["x"] + k.get("w", 1) for k in geometry)
    board_h = max(k["y"] + k.get("h", 1) for k in geometry) - min_y

    layers_order, layers = parse_keymap(KEYMAP_C.read_text())

    # Keys on BASE that activate each layer (highlighted on that layer's picture).
    activators = {}
    for idx, kc in enumerate(layers["U_BASE"]):
        m = re.fullmatch(r"(?:LT|MO)\((U_\w+)(?:, \w+)?\)", kc)
        if m:
            activators.setdefault(m.group(1), set()).add(idx)

    layer_w = board_w * UNIT
    layer_h = board_h * UNIT + TITLE_H
    rows = (len(layers_order) + COLS - 1) // COLS
    sheet_w = COLS * layer_w + (COLS + 1) * LAYER_GAP
    sheet_h = rows * layer_h + (rows + 1) * LAYER_GAP

    out = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{sheet_w}" height="{sheet_h}" viewBox="0 0 {sheet_w} {sheet_h}" '
        f'font-family="DejaVu Sans, Helvetica, Arial, sans-serif">',
        f'<rect width="{sheet_w}" height="{sheet_h}" fill="#ffffff"/>',
    ]
    for li, lname in enumerate(layers_order):
        ox = LAYER_GAP + (li % COLS) * (layer_w + LAYER_GAP)
        oy = LAYER_GAP + (li // COLS) * (layer_h + LAYER_GAP)
        out.append(f'<text x="{ox}" y="{oy + 22}" font-size="22" font-weight="bold" fill="#222">{esc(LAYER_TITLE.get(lname, lname))}</text>')
        for idx, key in enumerate(geometry):
            kx = ox + key["x"] * UNIT + PAD
            ky = oy + TITLE_H + (key["y"] - min_y) * UNIT + PAD
            kw = key.get("w", 1) * UNIT - 2 * PAD
            kh = key.get("h", 1) * UNIT - 2 * PAD
            main_l, sub_l = legend(layers[lname][idx])
            is_act = idx in activators.get(lname, set())
            if is_act:
                fill, stroke, dash = "#ffe9a8", "#b8860b", ""
            elif main_l:
                fill, stroke, dash = "#ffffff", "#444", ""
            else:
                fill, stroke, dash = "#f4f4f4", "#bbb", ' stroke-dasharray="3,3"'
            out.append(f'<rect x="{kx:.1f}" y="{ky:.1f}" width="{kw:.1f}" height="{kh:.1f}" rx="5" fill="{fill}" stroke="{stroke}"{dash}/>')
            if main_l:
                size = 13 if len(main_l) <= 4 else 10 if len(main_l) <= 7 else 8
                cy = ky + kh / 2 + (0 if not sub_l else -4)
                out.append(f'<text x="{kx + kw / 2:.1f}" y="{cy:.1f}" font-size="{size}" text-anchor="middle" dominant-baseline="middle" fill="#111">{esc(main_l)}</text>')
            if sub_l:
                out.append(f'<text x="{kx + kw / 2:.1f}" y="{ky + kh - 6:.1f}" font-size="8" text-anchor="middle" fill="#8a4b00">{esc(sub_l)}</text>')
    out.append("</svg>")
    OUT_SVG.write_text("\n".join(out))
    print(f"wrote {OUT_SVG}")
    if shutil.which("rsvg-convert"):
        subprocess.run(["rsvg-convert", "-w", "2400", "-o", str(OUT_PNG), str(OUT_SVG)], check=True)
        print(f"wrote {OUT_PNG}")
    else:
        print("rsvg-convert not found; PNG not written")


if __name__ == "__main__":
    main()

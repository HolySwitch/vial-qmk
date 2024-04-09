// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY,
  _LOWER,
  _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * QWERTY
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */

    [_QWERTY] = LAYOUT(
           KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,       KC_5,                      KC_6,     KC_7,         KC_8,      KC_9,     KC_0,      KC_GRV,
           KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,       KC_T,                      KC_Y,     KC_U,         KC_I,      KC_O,     KC_P,      KC_BSPC,
    KC_1,  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,       KC_G,                       KC_H,     KC_J,         KC_K,      KC_L,     KC_SCLN,   KC_QUOT,  KC_1,
           KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,       KC_B, KC_MUTE,    XXXXXXX,   KC_N,     KC_M,         KC_COMM,   KC_DOT,   KC_SLSH,   KC_RSFT,
                             KC_LALT, KC_LCTL, MO(_LOWER), KC_ENT,                    KC_SPC,   MO(_RAISE),   KC_RCTL,   KC_RALT
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    //                  Encoder 1                                     Encoder 2
};
#endif

#ifdef OLED_ENABLE

static void render_at(uint8_t start_col, uint8_t start_line, uint8_t rows, uint8_t width, const char data[rows][width]) {
    for (int i = 0; i < rows; i++)
    {
        oled_set_cursor(start_col, start_line + i);
        oled_write_raw_P(data[i], sizeof(data[i]));
    }
}

#ifdef LOGO_ENABLE
static void render_logo(void) {
    static const char PROGMEM logo[6][32] =
    {{0,0,0,0,192,224,240,240,112,112,120,120,120,120,120,120,120,120,120,120,120,120,112,112,240,240,224,192,0,0,0,0},{0,0,0,0,3,7,7,15,15,15,142,142,222,222,222,222,222,222,222,222,142,142,15,15,15,7,7,3,0,0,0,0},{0,128,192,240,248,252,254,126,63,31,15,15,15,7,7,7,7,7,7,15,15,15,31,63,126,254,252,248,240,192,0,0},{252,255,255,255,255,3,0,0,0,0,240,240,240,240,254,255,255,254,240,240,240,240,0,0,0,0,3,255,255,255,255,252},{3,31,127,255,255,252,240,224,192,128,0,0,0,0,15,31,31,15,0,0,0,0,128,192,224,240,252,255,255,127,31,3},{0,0,0,0,1,3,7,15,15,31,31,31,62,62,62,62,62,62,62,62,31,31,31,15,15,7,3,1,0,0,0,0}};
    render_at(0, 5, 6, 32, logo);
}
#endif

static void render_layer_state(void) {
    static const char PROGMEM off[2][20] = {{224,24,196,244,242,250,250,250,242,242,194,2,2,2,2,2,4,4,24,224},{3,12,17,23,39,47,47,47,39,39,33,32,32,32,32,32,16,16,12,3}};
    static const char PROGMEM on[2][20] ={{224,248,252,252,254,254,254,254,254,62,14,14,6,6,6,14,12,60,248,224},{3,15,31,31,63,63,63,63,63,62,56,56,48,48,48,56,24,30,15,3}};

    #define LAYER_STATE_BITS 4
    const int current_layer = get_highest_layer(layer_state) > get_highest_layer(default_layer_state)
        ? get_highest_layer(layer_state)
        : get_highest_layer(default_layer_state);
    for (int i = 0; i < LAYER_STATE_BITS; i++)
    {
        int line = 12 - 1 - 2*(i + 1);
        if (current_layer > i)
        {
            render_at(1, line, 2, 20, on);
        } else {
            render_at(1, line, 2, 20, off);
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    #ifdef LOGO_ENABLE
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        render_logo();
    }
    #else
    render_layer_state();
    #endif

    return false;
}

#endif

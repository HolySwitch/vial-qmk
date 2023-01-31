 /* Copyright 2022 Andrei Gaevskii
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

//Sets up what the OLED screens display.

#include QMK_KEYBOARD_H

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

/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 * Modification for Vial support by Drew Petersen
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

// clang-format off

#pragma once

// Vial Support
#define VIAL_KEYBOARD_UID { 0x05, 0xCD, 0x9F, 0x8A, 0xF4, 0xDF, 0xDE, 0xB2 }

// #define MASTER_RIGHT

#undef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 4

#undef TAPPING_TERM
#define TAPPING_TERM 150

#define SPLIT_LAYER_STATE_ENABLE

#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN D3

    #undef RGBLED_NUM
    #ifdef RGBLIGHT_MODE_UNDERGLOW
    #   define RGBLED_NUM 7*2
    #endif
    #ifdef RGBLIGHT_MODE_BACKLIGHT
    #   define RGBLED_NUM 29*2
    #endif
    #ifdef RGBLIGHT_MODE_FULL
    #   define RGBLED_NUM 36*2
    #endif

    #define RGBLED_SPLIT { RGBLED_NUM/2, RGBLED_NUM/2 }

    #undef RGBLIGHT_ANIMATIONS
    #undef RGBLIGHT_EFFECT_BREATHING
    #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
    #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #undef RGBLIGHT_EFFECT_SNAKE
    #undef RGBLIGHT_EFFECT_KNIGHT
    #undef RGBLIGHT_EFFECT_CHRISTMAS
    #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
    #undef RGBLIGHT_EFFECT_ALTERNATING
    #undef RGBLIGHT_EFFECT_TWINKLE

    #define RGBLIGHT_LIMIT_VAL 128
    #define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+0
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE


/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_ergol.h"

enum layer_names {
    _BASE,
    _NAV,
    _NUM
};

//Layer-taps
#define MY_SPC LT(_NAV, KC_SPC)
#define MY_ENT LT(_NUM, KC_ENT)

// Left-hand home row mods
#define MY_A LGUI_T(KC_A)
#define MY_S LALT_T(KC_S)
#define MY_D LSFT_T(KC_D)
#define MY_F LCTL_T(KC_F)

// Right-hand home row mods
#define MY_J RCTL_T(KC_J)
#define MY_K RSFT_T(KC_K)
#define MY_L LALT_T(KC_L)
#define MY_SCLN RGUI_T(KC_SCLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LCTL,    KC_RCTL,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LALT,    MY_A,    MY_S,    MY_D,    MY_F,    KC_G, KC_LALT,    KC_RALT,    KC_H,    MY_J,    MY_K,    MY_L, MY_SCLN, KC_RGUI,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                           KC_ESC, OS_LSFT,  MY_SPC,     MY_ENT, OS_RALT, KC_BSPC
                                      //`--------------------------'  `--------------------------'

  ),

  [_NAV] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL,    KC_RCTL, KC_AGIN, KC_PSTE, KC_COPY,  KC_CUT, KC_UNDO, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, KC_LALT,    KC_RALT, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_DEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    QK_LLCK, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB, XXXXXXX,    EG_7,    EG_8,    EG_9, XXXXXXX, QK_BOOT,    KC_RCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX,    EG_4,    EG_5,    EG_6, XXXXXXX, KC_LALT,    KC_RALT, XXXXXXX, KC_RCTL, KC_RSFT, KC_LALT, KC_RGUI,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX,    EG_1,    EG_2,    EG_3, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                           EG_DOT,    EG_0, QK_LLCK,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )

};

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

bool is_caps_word_active = false;

void caps_word_set_user(bool active) {
    if (active) {
        is_caps_word_active = true;
    } else {
        is_caps_word_active = false;
    }
}

#define MY_RGB_INDICATOR_COLOR 0, 100, 100

bool rgb_matrix_indicators_user(void) {
    if (is_caps_word_active) {
        rgb_matrix_set_color(g_led_config.matrix_co[3][4], MY_RGB_INDICATOR_COLOR);
    }
    if (layer_state_is(_NAV)) {
        rgb_matrix_set_color(g_led_config.matrix_co[3][5], MY_RGB_INDICATOR_COLOR);
        // workaround for weird aliasing causing both sides to turn on
        rgb_matrix_set_color(g_led_config.matrix_co[7][5], 0, 0, 0);
    }
    if (layer_state_is(_NUM)) {
        rgb_matrix_set_color(g_led_config.matrix_co[7][5], MY_RGB_INDICATOR_COLOR);
    }
    return false;
}

bool caps_word_press_user(uint16_t keycode) {
    bool on_sym_layer = (get_mods() | get_oneshot_mods()) & MOD_BIT_RALT;
    if (on_sym_layer) {
        // Keep symbols as they are.
        return true;
    } else {
        switch (keycode) {
            // Avoid EG_DOT = KC_N and EG_1DK = KC_O
            case KC_A ... KC_M:
            case KC_P ... KC_Z:
            // Add EG_U, EG_G, EG_K
            case EG_U:
            case EG_G:
            case EG_K:
                add_weak_mods(MOD_BIT_LSHIFT);
                return true;
            case EG_1 ... EG_0:
            case KC_BSPC:
            case KC_DEL:
            case KC_TAB:
            case EG_UNDS:
            case EG_1DK:
                return true;
            default:
                return false;
        }
    }
}

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t tab_key_override = ko_make_basic(MOD_BIT(KC_RALT), MY_SPC, KC_TAB);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &tab_key_override
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

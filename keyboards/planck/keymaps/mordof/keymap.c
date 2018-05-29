/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  TMUX_SCROLL,
  SCR_SCROLL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layout: http://www.keyboard-layout-editor.com/#/gists/10f2e9e3c8dc255039d4bd76eacc28ad
  [_QWERTY] = {
    { KC_TAB     , KC_Q     , KC_W   , KC_E    , KC_R   , KC_T   , KC_Y   , KC_U     , KC_I   , KC_O   , KC_P   , KC_SLSH },
    { KC_ESC     , KC_A     , KC_S   , KC_D    , KC_F   , KC_G   , KC_H   , KC_J     , KC_K   , KC_L   , KC_SCLN, KC_QUOT },
    { KC_LSFT    , KC_Z     , KC_X   , KC_C    , KC_V   , KC_B   , KC_N   , KC_M     , KC_COMM, KC_DOT , KC_UP  , KC_DEL  },
    { TMUX_SCROLL, KC_LALT  , KC_LGUI, KC_LCTRL, LOWER  , KC_ENT , KC_SPC , RAISE    , XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT }
  },
  [_LOWER] = {
    { KC_GRV     , KC_1     , KC_2   , KC_3    , KC_4   , KC_5   , KC_6   , KC_7     , KC_8   , KC_9   , KC_0   , XXXXXXX },
    { XXXXXXX    , XXXXXXX  , KC_BSPC, KC_MINS , KC_EQL , XXXXXXX, XXXXXXX, KC_4     , KC_5   , KC_6   , XXXXXXX, XXXXXXX },
    { KC_LPRN    , XXXXXXX  , XXXXXXX, XXXXXXX , KC_BSLS, XXXXXXX, KC_0   , KC_1     , KC_2   , KC_3   , KC_UP  , KC_RPRN },
    { XXXXXXX    , XXXXXXX  , XXXXXXX, XXXXXXX , LOWER  , KC_ENT , KC_SPC , RAISE    , KC_DOT , KC_LEFT, KC_DOWN, KC_RGHT }
  },
  [_RAISE] = {
    { KC_TILD    , KC_EXLM  , KC_AT  , KC_HASH , KC_DLR , KC_PERC, KC_CIRC, KC_AMPR  , KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX },
    { XXXXXXX    , XXXXXXX  , KC_BSPC, KC_UNDS , KC_PLUS, XXXXXXX, XXXXXXX, KC_QUES  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
    { KC_LBRC    , XXXXXXX  , XXXXXXX, XXXXXXX , KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, KC_RBRC },
    { SCR_SCROLL , XXXXXXX  , XXXXXXX, XXXXXXX , LOWER  , KC_ENT , KC_SPC , RAISE    , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX }
  },
  [_ADJUST] = {
    { KC_F1      , KC_F2    , KC_F3  , KC_F4   , KC_F5  , KC_F6  , KC_F7  , KC_F8    , KC_F9  , KC_F10 , KC_F11 , KC_F12  },
    { XXXXXXX    , XXXXXXX  , XXXXXXX, KC_HOME , KC_PGDN, XXXXXXX, XXXXXXX, KC_PGUP  , KC_END , XXXXXXX, XXXXXXX, XXXXXXX },
    { KC_LCBR    , XXXXXXX  , XXXXXXX, KC_MPRV , KC_VOLD, XXXXXXX, KC_MUTE, KC_VOLU  , KC_MNXT, XXXXXXX, XXXXXXX, KC_RCBR },
    { XXXXXXX    , XXXXXXX  , XXXXXXX, XXXXXXX , LOWER  , KC_MPLY, KC_MPLY, RAISE    , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX }
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
	    return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      break;
    case TMUX_SCROLL:
      if (record->event.pressed) {
        // ctrl + b -> [
        register_code(KC_LCTRL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTRL);
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
      }
      break;
    case SCR_SCROLL:
      if (record->event.pressed) {
        // ctrl + a -> esc
        register_code(KC_LCTRL);
        register_code(KC_A);
        unregister_code(KC_A);
        unregister_code(KC_LCTRL);
        register_code(KC_ESC);
        unregister_code(KC_ESC);
      }
      break;
  }
  return true;
}

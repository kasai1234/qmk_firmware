/* Copyright 2018 Carlos Filoteo
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
#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)
#define LT2_ENT LT(2, KC_ENT)
#define LT3_TAB LT(3, KC_TAB)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer
   * ,-------------------------------------------------------------------------.
   * | Esc |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * |Tab/L3|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |   '  |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |Sh/En|
   * |-------------------------------------------------------------------------+
   * | Ctrl| Alt | Gui | App |  L2  |   Space   |  L1  | Left| Down|  Up |Right|
   * `-------------------------------------------------------------------------'
   */

LAYOUT(
  LT3_TAB,  KC_Q,    KC_W,      KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL, KC_A,     KC_S,      KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_MINS, KC_ENT,
  KC_LSFT, KC_Z,     KC_X,      KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_INT1,
  KC_LEFT, KC_RGHT, KC_LGUI, KC_MHEN,LT2_ENT,       KC_BSPC,    LT1_SPC, ALT_T(KC_HENK), KC_APP, KC_DOWN,     KC_UP
),

  /* FN Layer 1
   * ,-------------------------------------------------------------------------.
   * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |  -  |  =  |  [  |  ]  |  \   |
   * |-------------------------------------------------------------------------+
   * |       | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |Capsl|      |          |       | Home| PgDn| PgUp| End |
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Right */
  KC_ESC,          KC_1,  KC_2,  KC_3,  KC_4,  KC_5,     KC_6 , XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP, KC_DELETE,
  LCTL_T(KC_F11), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,  XXXXXXX,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
  SFT_T(KC_F12),  KC_F6, KC_F7, KC_F8, KC_F9,KC_F10,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, MO(3),     KC_DELETE,     _______, _______, _______, _______, _______
),

  /* FN Layer 2
   * ,-------------------------------------------------------------------------.
   * |   ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |  _  |  +  |  { |  }  |   |   |
   * |-------------------------------------------------------------------------+
   * |       | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |Capsl|      |          |       | Home| PgDn| PgUp| End |
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Left */
  KC_ESC,     KC_EXLM,    KC_QUES,     KC_RBRC,    KC_NUHS, LSFT(KC_EQL),    KC_6,    KC_7,    KC_8,    KC_9, LSFT(KC_QUOT), KC_SLSH,
  LSFT(KC_7), KC_HASH, LSFT(KC_2),  LSFT(KC_8), LSFT(KC_9),      KC_LBRC, XXXXXXX,    KC_4,    KC_5,    KC_6,       KC_MINS,  LSFT(KC_MINS),
  KC_EQL,     KC_PERC, LSFT(KC_6),     KC_SCLN,    KC_QUOT,LSFT(KC_INT3),    KC_0,    KC_1,    KC_2,    KC_3, LSFT(KC_SCLN),  KC_ENT,  
  _______,    _______,    _______,     KC_ZKHK,    _______,        KC_DELETE,        MO(3),    KC_0,  KC_DOT,       _______, _______
),

  /* FN Layer 2
   * ,-------------------------------------------------------------------------.
   * | Esc | Calc|Webhm| Mail| Comp|     |     |     |     |     |PrtSc|       |
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |     |     |     |     |      |
   * |-------------------------------------------------------------------------+
   * |       |    |     |     |     |     |     |     |     |     |     |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       |MousL|MousD|MousU|MousR|
   * `-------------------------------------------------------------------------'
   */

LAYOUT( /* Tab */
  KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  LCTL_T(KC_F11), KC_F1, KC_F2, KC_F3,  KC_F4,   KC_F5, RGB_TOG, RGB_MOD, XXXXXXX, LCA(KC_DEL), LALT(KC_PSCR),  KC_PSCR,
  SFT_T(KC_F12),  KC_F6, KC_F7, KC_F8,  KC_F9,  KC_F10, RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD,  RGB_SAI,
  _______, _______, _______, _______, _______,       RESET,      _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
),
};

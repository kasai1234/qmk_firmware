/* Copyright 2018 Salicylic_Acid
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FLOCK 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MOUSE,
  BROWSER,
  FLOCK,
  LOWER,
  RAISE,
  ADJUST,
  SEND_SUM,
  SEND_AVERAGE,
  SEND_COUNTIF,
  SEND_MAX,
  SEND_MIN
};

enum tapdances{
  TD_ESFL = 0,
  TD_ESQW,
};

// Fillers to make layering more clear
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJUST ADJUST

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP

#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)

#define KC_SNUBS S(KC_NUBS)
#define KC_SNUHS S(KC_NUHS)

#define KC_SSUM  SEND_SUM
#define KC_SAVE  SEND_AVERAGE
#define KC_SCOU  SEND_COUNTIF
#define KC_SMAX  SEND_MAX
#define KC_SMIN  SEND_MIN

#define KC_RPDO LT(_RAISE, KC_PDOT)
#define KC_LP0 LT(_LOWER, KC_P0)
#define KC_NAD LT(_ADJUST, KC_NLCK)

#define KC_ESFL TD(TD_ESFL)
#define KC_ESQW TD(TD_ESQW)

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESFL] = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _FLOCK),
  [TD_ESQW] = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _QWERTY),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_With_Setta21_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
       PGUP,  ESFL,     1,     2,     3,     4,     5,                   6,     7,     8,     9,     0,  MINS,  BSPC,          LP0,    P1,    P4,    P7,   NAD,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
       PGDN,   TAB,     Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P,  LCBR,  RCBR,                  P2,    P5,    P8,  PSLS,    F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
             LCTRL,     A,     S,     D,     F,     G,                   H,     J,     K,     L,  SCLN,  QUOT,   ENT,         RPDO,    P3,    P6,    P9,  PAST,  PEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
              LSFT,     Z,     X,     C,     V,     B,                   N,     M,  COMM,   DOT,  SLSH,    UP,  RSFT,                PENT,         PPLS,  PMNS,   DEL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
            ADJUST,         LALT,          SPC, LOWER,               RAISE,          SPC,  LGUI,  LEFT,  DOWN, RIGHT  \
          //`-------------------------------------------------------------------------------------------------------'
  ),

  [_FLOCK] = LAYOUT_With_Setta21_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      _____,   ESC,    F1,    F2,    F3,    F4,    F5,                  F6,    F7,    F8,    F9,   F10,   F11,   F12,          LP0,    P1,    P4,    P7,   NAD,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____,   TAB,     Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P,  LCBR,  RCBR,                  P2,    P5,    P8,  PSLS,    F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
             LCTRL,     A,     S,     D,     F,     G,                   H,     J,     K,     L,  SCLN,  QUOT,   ENT,         RPDO,    P3,    P6,    P9,  PAST,  PEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
              LSFT,     Z,     X,     C,     V,     B,                   N,     M,  COMM,   DOT,  SLSH,    UP,  RSFT,                PENT,         PPLS,  PMNS,   DEL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
            ADJUST,         LALT,        _____, LOWER,               RAISE,        _____,  LGUI,  LEFT,  DOWN, RIGHT  \
          //`-------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_With_Setta21_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      _____,   ESC,    F1,    F2,    F3,    F4,    F5,                  F6,    F7,    F8,    F9,   F10,   F11,   F12,        LOWER, XXXXX,  LEFT, XXXXX, XXXXX,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____,  TILD,  EXLM,    AT,  HASH,   DLR,  PERC,                CIRC,  AMPR,  ASTR,  LPRN,  RPRN,   DEL, _____,                DOWN,  DOWN,    UP,  PSLS,   F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
             _____,    F1,    F2,    F3,    F4,    F5,                  F6,  UNDS,  PLUS,  LCBR,  RCBR,  PIPE, _____,        RAISE, XXXXX, RIGHT, XXXXX,  PAST,  PEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
             _____,    F7,    F8,  F9,     F10,   F11,                 F12, SNUHS, SNUBS, _____, _____,  VOLU, _____,                PENT,         PPLS,  PMNS,   DEL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
             _____,        _____,        _____, _____,               _____,        _____,  PDOT,  MNXT,  VOLD,  MPLY  \
          //`-------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_With_Setta21_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      _____,   ESC,    F1,    F2,    F3,    F4,    F5,                  F6,    F7,    F8,    F9,   F10,   F11,   F12,        LOWER,   F11,    F4,    F7,  SMIN,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____,   TAB,     1,     2,     3,     4,     5,                   6,     7,     8,     9,     0,  MINS,  BSPC,                 F12,    F5,    F8,  SMAX,    F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
             _____,    F1,    F2,    F3,    F4,    F5,                  F6,  MINS,   EQL,  LBRC,  RCBR,  BSLS, _____,        RAISE,    F3,    F6,    F9,  SCOU,  PEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
             _____,    F7,    F8,  F9,     F10,   F11,                 F12,  NUHS,  NUBS, _____, _____,  VOLU, _____,                RPRN,         SSUM,  SAVE,   DEL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
             _____,        _____,        _____, _____,               _____,        _____,  LGUI,  MNXT,  VOLD,  MPLY  \
          //`-------------------------------------------------------------------------------------------------------'
  ),


  [_ADJUST] = LAYOUT_With_Setta21_kc( /* Base */
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      _____,   RST,    F1,    F2,    F3,    F4,    F5,                  F6,    F7,    F8,    F9,   F10,   F11,   F12,        LOWER,  LVAD,  LHUD,  LSAD,ADJUST,  LTOG, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      _____, _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,               XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LVAI,  LHUI,  LSAI, XXXXX, _____, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
             _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LTOG,  LMOD, XXXXX,   CAD, APSCR,  PSCR, XXXXX,        RAISE, XXXXX, XXXXX, XXXXX, XXXXX, _____, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
             _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LVAD,  LVAI,  LHUD,  LHUI,  LSAD,  LSAI, XXXXX,                LMOD,        _____, _____, _____, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
             _____,        _____,        _____, _____,               _____,        _____, _____,  MNXT,  VOLD,  MPLY  \
          //`-------------------------------------------------------------------------------------------------------'
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//A description for expressing the layer position in LED mode.
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _FLOCK:
      setrgb(100, 100, 0, (LED_TYPE *)&led[0]);
      setrgb(100, 100, 0, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    case _LOWER:
      setrgb(0, 0, 150, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 150, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    case _RAISE:
      setrgb(150, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(150, 0, 0, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    case _ADJUST:
      setrgb(100, 0, 100, (LED_TYPE *)&led[0]);
      setrgb(100, 0, 100, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    default: //  for any other layers, or the default layer
      setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
      rgblight_set();
      break;
    }
#endif
return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("_SUM*");
      }
      return false;
      break;
    case SEND_AVERAGE:
      if (record->event.pressed) {
        SEND_STRING("_AVERAGE*");
      }
      return false;
      break;
    case SEND_COUNTIF:
      if (record->event.pressed) {
        SEND_STRING("_COUNTIF*");
      }
      return false;
      break;
    case SEND_MAX:
      if (record->event.pressed) {
        SEND_STRING("_MAX*");
      }
      return false;
      break;
    case SEND_MIN:
      if (record->event.pressed) {
        SEND_STRING("_MIN*");
      }
      return false;
      break;
  }
  return true;
}

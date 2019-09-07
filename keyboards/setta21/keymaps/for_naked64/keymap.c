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
#ifdef SSD1306OLED
  #include "ssd1306.h"
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
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SEND_SUM,
  SEND_AVERAGE,
  SEND_COUNTIF,
  SEND_MAX,
  SEND_MIN
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

#define KC_JCLON KC_QUOT  // : and +
#define KC_JAT   KC_LBRC  // @ and `
#define KC_JHAT  KC_EQL   // ^ and ~
#define KC_JENUN KC_RO    // \ and _ (EN mark and UNder score)
#define KC_JENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define KC_JLBRC KC_RBRC  // [ and {
#define KC_JRBRC KC_BSLS  // ] and }
#define KC_JAMPR KC_CIRC  // &
#define KC_JQUES LSFT(KC_SLSH)  // ?
#define KC_JTILD LSFT(KC_EQL)  // ~
#define KC_JQUOT LSFT(KC_7)  // '
#define KC_JLPRN KC_ASTR  // (
#define KC_JRPRN KC_LPRN  // )
#define KC_JLCBR KC_RCBR  // {
#define KC_JRCBR KC_PIPE  // }
#define KC_JPIPE LSFT(KC_JYEN)  // |
#define KC_JASTR LSFT(KC_QUOT)  // *
#define KC_JEQL LSFT(KC_MINS)  // =
#define KC_JPLUS LSFT(KC_SCLN)  // +
#define KC_JDQUO LSFT(KC_2)  // "
#define KC_CF11 LCTL_T(KC_F11)

#define KC_SF12 SFT_T(KC_F12)
#define KC_LEN LT(_LOWER, KC_ENT)
#define KC_RSP LT(_RAISE, KC_SPC)
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)

#define KC_RTAB LCTL(KC_TAB)
#define KC_LTAB LCTL(LSFT(KC_TAB))
#define KC_CTAB LCTL(KC_W)
#define KC_RETAB LCTL(LSFT(KC_T))

#define KC_CSAVE LCTL(KC_S)
#define KC_ALHE ALT_T(KC_HENK)
#define KC_GUMH LGUI_T(KC_MHEN)

#define KC_TGMO TG(_MOUSE)
#define KC_TGBR TG(_BROWSER)

#define KC_SSUM  SEND_SUM
#define KC_SAVE  SEND_AVERAGE
#define KC_SCOU  SEND_COUNTIF
#define KC_SMAX  SEND_MAX
#define KC_SMIN  SEND_MIN

#define KC_RPDO LT(_RAISE, KC_PDOT)
#define KC_LP0 LT(_LOWER, KC_P0)
#define KC_NAD LT(_ADJUST, KC_NLCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_for_Naked64_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
        LP0,  RPDO,     1,     2,    P4,     4,    P8,                   6,  PMNS,   ESC,     9,     0,  MINS,  BSPC,          LP0,    P1,    P4,    P7,   NAD,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
        LP0,  PENT,    P1,     W,    P5,     R,    P9,                   Y,     U,    F2,     O,     P, JLBRC, JRBRC,                  P2,    P5,    P8,  PSLS,    F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
              PENT,    P2,     S,    P6,     F,     G,                 NAD,     J,  JEQL,     L,  MINS, JENUN,   ENT,         RPDO,    P3,    P6,    P9,  PAST,  JEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
              LSFT,    P3,     X,  PPLS,    P7,     B,                PSLS,     M,  BSPC,   DOT,  SLSH,    UP,  RSFT,                PENT,         PPLS,  PMNS,  BSPC, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
              ZKHK,         GUMH,          LEN,  BSPC,                PAST,          RSP,  ALHE,  LEFT,  DOWN, RIGHT  \
          //`-------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_for_Naked64_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      LOWER, RAISE,    F1,    F2,  LEFT,    F4,    UP,                  F6,  PMNS,   ESC,    F9,   F10,   F11,   F12,        LOWER, XXXXX,  LEFT, XXXXX, XXXXX,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      LOWER,  PENT, XXXXX, JQUES,  DOWN, JRBRC, XXXXX,                  P6, XXXXX,    F2,    P9, JASTR,  SLSH, XXXXX,                DOWN,  DOWN,    UP,  PSLS,    F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
              PENT,  DOWN, JDQUO, RIGHT, JRPRN,   JAT,               XXXXX,    P4,  JEQL,    P6, _____,  JEQL,   ENT,        RAISE, XXXXX, RIGHT, XXXXX,  PAST,  JEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
              JHAT, XXXXX, JAMPR,  SCLN, XXXXX, JPIPE,                PPLS,    P1,  BSPC,    P3, JPLUS,    UP,  RSFT,                PENT,         PPLS,  PMNS,  BSPC, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
              ZKHK,        _____,          LEN, _____,                PAST,          RSP,  PDOT,  LEFT,  DOWN, RIGHT  \
          //`-------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_for_Naked64_kc( \
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      LOWER, RAISE,    F1,    F2,    F4,    F4,    F8,                  F6,  SAVE,   ESC,    F9,   F10,   F11,   F12,        LOWER,   F11,    F4,    F7,  SMIN,   ESC, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      LOWER, JRPRN,   F11,     2,    F5,     4,    F9,               XXXXX, XXXXX,    F2, XXXXX,  PGUP, XXXXX, XXXXX,                 F12,    F5,    F8,  SMAX,    F2, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
             JRPRN,   F12,    F2,    F6,    F4,    F5,                SMIN,  LEFT,  JEQL, RIGHT, XXXXX, XXXXX,   ENT,        RAISE,    F3,    F6,    F9,  SCOU,  JEQL, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
              SF12,    F3,    F7,  SSUM,    F7,   F10,                SMAX, XXXXX,  BSPC, XXXXX,  PGDN,    UP,  RSFT,               JRPRN,         SSUM,  SAVE,  BSPC, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
             _____,        _____,        LOWER, _____,                SCOU,        RAISE,  ALHE,  LEFT,  DOWN, RIGHT  \
          //`-------------------------------------------------------------------------------------------------------'
  ),


  [_ADJUST] = LAYOUT_for_Naked64_kc( /* Base */
  //,------------------------------------------------|             |------------------------------------------------.      |-----------------------------------------|
      LOWER, RAISE,    F1,    F2,  LHUD,    F4,  LSAI,                  F6, _____,  LTOG,    F9,   F10,   F11,   F12,        LOWER,  LVAD,  LHUD,  LSAD,ADJUST,  LTOG, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
      LOWER,  LMOD,  LVAD,     2,  LHUI,     4, XXXXX,               XXXXX, XXXXX, _____, XXXXX, XXXXX, XXXXX, XXXXX,                LVAI,  LHUI,  LSAI, XXXXX, _____, \
  //|------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |------+------+------+------+------+------|
              LMOD,  LVAI,    F2, XXXXX,    F4,    F5,                LTOG,  LMOD, _____,   CAD, APSCR,  PSCR, XXXXX,        RAISE, XXXXX, XXXXX, XXXXX, XXXXX, _____, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-------------+-------------+------+------|
              SF12, XXXXX,    F7, _____,  LSAD,   F10,                LVAD,  LVAI, _____,  LHUI,  LSAD,  LSAI, XXXXX,                LMOD,        _____, _____, _____, \
  //       |------+------+------+------+------+------|             |------+------+------+------+------+------+------|      |-----------------------------------------|
               RST,        _____,        LOWER, _____,               _____,        RAISE,  ALHE, XXXXX, XXXXX, XXXXX  \
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
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {

  // If you want to change the display of OLED, you need to change here
  //matrix_write_ln(matrix, read_layer_state());
  //matrix_write_ln(matrix, read_keylog());
  //matrix_write_ln(matrix, read_keylogs());
  //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
  //matrix_write_ln(matrix, read_host_led_state());
  //matrix_write_ln(matrix, read_timelog());

  // If you want to display logo instead of keylogger, comment out above and uncomment this here
  matrix_write(matrix, read_logo());
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
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

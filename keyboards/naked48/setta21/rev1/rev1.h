#ifndef SETTA21_H
#define SETTA21_CONFIG_H

//#pragma once

#include "../setta21.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);
/*
 * ,-----------------------------------.
 * | L00 | L01 | L02 | L03 | L04 | L05 |
 * |-----------------------------------+
 * |     | L11 | L12 | L13 | L14 | L15 |
 * |-----------------------------------+
 * | L20 | L21 | L22 | L23 | L24 | L25 |
 * |-----------------------------------+
 * | L30 |     | L33 |     | L34 | L35 |
 * |-----------------------------------'
 */

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, \
         L11, L12, L13, L14, L15, \
    L20, L21, L22, L23, L24, L25, \
    L30,      L32,      L34, L35  \
  ) \
  { \
    {  L00,  L01,  L02,  L03,  L04,  L05,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,  L11,  L12,  L13,  L14,  L15,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  L20,  L21,  L22,  L23,  L24,  L25,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  L30,KC_NO,  L32,KC_NO,  L34,  L35,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  }   \
  }

#define LAYOUT_kc( \
    L00, L01, L02, L03, L04, L05, \
         L11, L12, L13, L14, L15, \
    L20, L21, L22, L23, L24, L25, \
    L30,      L32,      L34, L35  \
  ) \
  LAYOUT( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, \
              KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, \
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, \
    KC_##L30,           KC_##L32,           KC_##L34, KC_##L35  \
  )



#define LAYOUT_for_Naked48( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B,    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B,         R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B,    R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B,    R30,      R32,      R34, R35  \
  ) \
  { \
    {  L00,  L01,  L02,  L03,  L04,  L05,  L06,  L07,  L08,  L09,  L0A,  L0B  },  \
    {  L10,  L11,  L12,  L13,  L14,  L15,  L16,  L17,  L18,  L19,  L1A,  L1B  },  \
    {  L20,  L21,  L22,  L23,  L24,  L25,  L26,  L27,  L28,  L29,  L2A,  L2B  },  \
    {  L30,  L31,  L32,  L33,  L34,  L35,  L36,  L37,  L38,  L39,  L3A,  L3B  },  \
    {  R00,  R01,  R02,  R03,  R04,  R05,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {KC_NO,  R11,  R12,  R13,  R14,  R15,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  R20,  R21,  R22,  R23,  R24,  R25,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  },  \
    {  R30,KC_NO,  R32,KC_NO,  R34,  R35,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO  }   \
  }

#define LAYOUT_for_Naked48_kc( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B,   R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B,        R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B,   R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B,   R30,      R32,      R34, R35  \
  ) \
  LAYOUT_for_Naked48( \
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,                     KC_##L06, KC_##L07, KC_##L08, KC_##L09, KC_##L0A, KC_##L0B,        KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, \
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,                     KC_##L16, KC_##L17, KC_##L18, KC_##L19, KC_##L1A, KC_##L1B,                  KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, \
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25,                     KC_##L26, KC_##L27, KC_##L28, KC_##L29, KC_##L2A, KC_##L2B,        KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, \
              KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##L36, KC_##L37, KC_##L38, KC_##L36, KC_##L3A, KC_##L3B,                  KC_##R30,           KC_##R32,           KC_##R34, KC_##R35  \
  )

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
#ifndef NAKED48_H
#define NAKED48_H

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
/*
 * ,------------------------------------           ------------------------------------------.
 * | L00 | L01 | L02 | L03 | L04 | L05 |           | L06 | L07 | L08 | L09 | L0A | L0B | L0C |
 * |------------------------------------           ------------------------------------------+
 * | L10 | L11 | L12 | L13 | L14 | L15 |           | L16 | L17 | L18 | L19 | L1A | L1B | L1C |
 * |------------------------------------           ------------------------------------------+
 * | L20 | L21 | L22 | L23 | L24 | L25 |           | L26 | L17 | L28 | L29 | L2A | L2B | L2C |
 * |-----------------------------------------------------------------------------------------+
 *       | L30 | L32 | L33 | L34 | L35 | L36 | L37 | L38 | L39 | L3A | L3B | L3D | L3C |
 *       |-----------------------------------------------------------------------------'
 */

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B, L0C, \
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B, L1C, \
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B, L2C, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B, L3C  \
    ) { \
  {  L00,  L01,  L02,  L03,  L04,  L05,  L06,  L07,  L08,  L09,  L0A,  L0B,  L0C  },  \
  {  L10,  L11,  L12,  L13,  L14,  L15,  L16,  L17,  L18,  L19,  L1A,  L1B,  L1C  },  \
  {  L20,  L21,  L22,  L23,  L24,  L25,  L26,  L27,  L28,  L29,  L2A,  L2B,  L2C  },  \
  {  L30,  L31,  L32,  L33,  L34,  L35,  L36,  L37,  L38,  L39,  L3A,  L3B,  L3C  }   \
}

#endif

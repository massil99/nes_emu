#ifndef ROL_H_
#define ROL_H_

#include "custom_types.h"

u8 ROL(u8 m);
size_t ROL_Accumulator();
size_t ROL_ZeroPage(u8 addr);
size_t ROL_ZeroPageX(u8 addr);
size_t ROL_Absolute(u16 addr);
size_t ROL_AbsoluteX(u16 addr);

#endif //ROL_H_

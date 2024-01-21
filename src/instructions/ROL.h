#ifndef ROL_H_
#define ROL_H_

#include "custom_types.h"

u8 ROL(u8 m);
void ROL_Accumulator();
void ROL_ZeroPage(u8 addr);
void ROL_ZeroPageX(u8 addr);
void ROL_Absolute(u16 addr);
void ROL_AbsoluteX(u16 addr);

#endif //ROL_H_

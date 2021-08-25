#ifndef LSR_H_
#define LSR_H_

#include "custom_types.h"

u8 LSR(u8 m);
void LSR_Accumulator();
void LSR_ZeroPage(u8 addr);
void LSR_ZeroPageX(u8 addr);
void LSR_Absolute(u16 addr);
void LSR_AbsoluteX(u16 addr);

#endif //LSR_H_

#ifndef ROR_H_
#define ROR_H_

#include "custom_types.h"

u8 ROR(u8 m);
void ROR_Accumulator();
void ROR_ZeroPage(u8 addr);
void ROR_ZeroPageX(u8 addr);
void ROR_Absolute(u16 addr);
void ROR_AbsoluteX(u16 addr);

#endif //ROR_H_

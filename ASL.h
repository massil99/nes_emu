#ifndef ASL_H_
#define ASL_H_

#include "custom_types.h"

void ASL_Accumulator();
u8 ASL(u8 mem);
void ASL_ZeroPage(u8 addr);
void ASL_ZeroPageX(u8 addr);
void ASL_Absolute(u16 addr);
void ASL_AbsoluteX(u16 addr);

#endif //ASL_H_

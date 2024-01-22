#ifndef ROR_H_
#define ROR_H_

#include "custom_types.h"

u8 ROR(u8 m);
size_t ROR_Accumulator();
size_t ROR_ZeroPage(u8 addr);
size_t ROR_ZeroPageX(u8 addr);
size_t ROR_Absolute(u16 addr);
size_t ROR_AbsoluteX(u16 addr);

#endif //ROR_H_

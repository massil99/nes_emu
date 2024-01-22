#ifndef LSR_H_
#define LSR_H_

#include "custom_types.h"

u8 LSR(u8 m);
size_t LSR_Accumulator();
size_t LSR_ZeroPage(u8 addr);
size_t LSR_ZeroPageX(u8 addr);
size_t LSR_Absolute(u16 addr);
size_t LSR_AbsoluteX(u16 addr);

#endif //LSR_H_

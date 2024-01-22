#ifndef ASL_H_
#define ASL_H_

#include "custom_types.h"

size_t ASL_Accumulator();
u8 ASL(u8 mem);
size_t ASL_ZeroPage(u8 addr);
size_t ASL_ZeroPageX(u8 addr);
size_t ASL_Absolute(u16 addr);
size_t ASL_AbsoluteX(u16 addr);

#endif //ASL_H_

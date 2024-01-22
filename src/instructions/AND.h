#ifndef AND_H_
#define AND_H_

#include "custom_types.h"

size_t AND(u8 m);
#define AND_Immediate(mem) AND(mem)

size_t AND_ZeroPage(u8 addr);
size_t AND_ZeroPageX(u8 addr);
size_t AND_Absolute(u16 addr);
size_t AND_AbsoluteX(u16 addr);
size_t AND_AbsoluteY(u16 addr);
size_t AND_IndirectX(u8 addr);
size_t AND_IndirectY(u8 addr);

#endif //AND_H_

#ifndef AND_H_
#define AND_H_

#include "custom_types.h"

void AND(u8 m);
#define AND_Immediate(mem) AND(mem)

void AND_ZeroPage(u8 addr);
void AND_ZeroPageX(u8 addr);
void AND_Absolute(u16 addr);
void AND_AbsoluteX(u16 addr);
void AND_AbsoluteY(u16 addr);
void AND_IndirectX(u8 addr);
void AND_IndirectY(u8 addr);

#endif //AND_H_

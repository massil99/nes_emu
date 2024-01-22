#ifndef EOR_H_
#define EOR_H_

#include "custom_types.h"

size_t EOR(u8 m);
#define EOR_Immediate(mem) EOR(mem)
size_t EOR_ZeroPage(u8 addr);
size_t EOR_ZeroPageX(u8 addr);
size_t EOR_Absolute(u16 addr);
size_t EOR_AbsoluteX(u16 addr);
size_t EOR_AbsoluteY(u16 addr);
size_t EOR_IndirectX(u8 addr);
size_t EOR_IndirectY(u8 addr);

#endif //EOR_H_

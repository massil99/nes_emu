#ifndef SBC_H_
#define SBC_H_

#include "custom_types.h"

size_t SBC(u8 m);
#define SBC_Immediate(mem) SBC(mem) 

size_t SBC_ZeroPage(u8 addr);
size_t SBC_ZeroPageX(u8 addr);
size_t SBC_Absolute(u16 addr);
size_t SBC_AbsoluteX(u16 addr);
size_t SBC_AbsoluteY(u16 addr);
size_t SBC_IndirectX(u8 addr);
size_t SBC_IndirectY(u8 addr);

#endif //SBC_H_

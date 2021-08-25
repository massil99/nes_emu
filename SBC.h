#ifndef SBC_H_
#define SBC_H_

#include "custom_types.h"

void SBC(u8 m);
#define SBC_Immediate(mem) SBC(mem) 

void SBC_ZeroPage(u8 addr);
void SBC_ZeroPageX(u8 addr);
void SBC_Absolute(u16 addr);
void SBC_AbsoluteX(u16 addr);
void SBC_AbsoluteY(u16 addr);
void SBC_IndirectX(u8 addr);
void SBC_IndirectY(u8 addr);

#endif //SBC_H_

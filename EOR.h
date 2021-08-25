#ifndef EOR_H_
#define EOR_H_

#include "custom_types.h"

void EOR(u8 m);
#define EOR_Immediate(mem) EOR(mem)
void EOR_ZeroPage(u8 addr);
void EOR_ZeroPageX(u8 addr);
void EOR_Absolute(u16 addr);
void EOR_AbsoluteX(u16 addr);
void EOR_AbsoluteY(u16 addr);
void EOR_IndirectX(u8 addr);
void EOR_IndirectY(u8 addr);

#endif //EOR_H_

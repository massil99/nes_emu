#ifndef INCDEC_H_J
#define INCDEC_H_J

#include "custom_types.h"

u8 DEC(u8 mem);
void DEC_ZeroPage(u8 addr);
void DEC_ZeroPageX(u8 addr);
void DEC_Absolute(u16 addr);
void DEC_AbsoluteX(u16 addr);
void DEX();
void DEY();
u8 INC(u8 mem);
void INC_ZeroPage(u8 addr);
void INC_ZeroPageX(u8 addr);
void INC_Absolute(u16 addr);
void INC_AbsoluteX(u16 addr);
void INX();
void INY();

#endif //INCDEC_H_J

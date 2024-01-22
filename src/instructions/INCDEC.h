#ifndef INCDEC_H_J
#define INCDEC_H_J

#include "custom_types.h"

u8 DEC(u8 mem);
size_t DEC_ZeroPage(u8 addr);
size_t DEC_ZeroPageX(u8 addr);
size_t DEC_Absolute(u16 addr);
size_t DEC_AbsoluteX(u16 addr);
size_t DEX();
size_t DEY();
u8 INC(u8 mem);
size_t INC_ZeroPage(u8 addr);
size_t INC_ZeroPageX(u8 addr);
size_t INC_Absolute(u16 addr);
size_t INC_AbsoluteX(u16 addr);
size_t INX();
size_t INY();

#endif //INCDEC_H_J

#ifndef ORA_H_
#define ORA_H_

#include "custom_types.h"

size_t ORA(u8 m);
#define ORA_Immediate(mem) ORA(mem)
size_t ORA_ZeroPage(u8 addr);
size_t ORA_ZeroPageX(u8 addr);
size_t ORA_Absolute(u16 addr);
size_t ORA_AbsoluteX(u16 addr);
size_t ORA_AbsoluteY(u16 addr);
size_t ORA_IndirectX(u8 addr);
size_t ORA_IndirectY(u8 addr);
		  
#endif //ORA_H_

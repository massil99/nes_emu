#ifndef ORA_H_
#define ORA_H_

#include "custom_types.h"

void ORA(u8 m);
#define ORA_Immediate(mem) ORA(mem)
void ORA_ZeroPage(u8 addr);
void ORA_ZeroPageX(u8 addr);
void ORA_Absolute(u16 addr);
void ORA_AbsoluteX(u16 addr);
void ORA_AbsoluteY(u16 addr);
void ORA_IndirectX(u8 addr);
void ORA_IndirectY(u8 addr);
		  
#endif //ORA_H_

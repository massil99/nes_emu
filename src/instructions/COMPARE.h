#ifndef COMPARE_H_
#define COMPARE_H_

size_t CMP(u8 m);
#define CMP_Immediate(mem) CMP(mem)
size_t CMP_ZeroPage(u8 addr);
size_t CMP_ZeroPageX(u8 addr);
size_t CMP_Absolute(u16 addr);
size_t CMP_AbsoluteX(u16 addr);
size_t CMP_AbsoluteY(u16 addr);
size_t CMP_IndirectX(u8 addr);
size_t CMP_IndirectY(u8 addr);
size_t CPX(u8 m);
#define CPX_Immediate(mem) CPX(mem)
size_t CPX_ZeroPage(u8 addr);
size_t CPX_Absolute(u16 addr);
size_t CPY(u8 m);
#define CPY_Immediate(mem) CPY(mem)
size_t CPY_ZeroPage(u8 addr);
size_t CPY_Absolute(u16 addr);

#endif //COMPARE_H_

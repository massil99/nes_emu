#ifndef COMPARE_H_
#define COMPARE_H_

void CMP(u8 m);
#define CMP_Immediate(mem) CMP(mem)
void CMP_ZeroPage(u8 addr);
void CMP_ZeroPageX(u8 addr);
void CMP_Absolute(u16 addr);
void CMP_AbsoluteX(u16 addr);
void CMP_AbsoluteY(u16 addr);
void CMP_IndirectX(u8 addr);
void CMP_IndirectY(u8 addr);
void CPX(u8 m);
#define CPX_Immediate(mem) CPX(mem)
void CPX_ZeroPage(u8 addr);
void CPX_Absolute(u16 addr);
void CPY(u8 m);
#define CPY_Immediate(mem) CPY(mem)
void CPY_ZeroPage(u8 addr);
void CPY_Absolute(u16 addr);

#endif //COMPARE_H_

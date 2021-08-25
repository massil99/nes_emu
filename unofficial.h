#ifndef UNOFFICIAL_H_
#define UNOFFICIAL_H_
	
#include "add_mode.h"

void ALR(u8 m);
void ANC(u8 m);
void ARR(u8 m);
void AXS(u8 m);

void LAX_Absolute(u16 addr);
void LAX_AbsoluteY(u16 addr);
void LAX_ZeroPage(u8 addr);
void LAX_ZeroPageY(u8 addr);
void LAX_IndirectX(u8 addr);
void LAX_IndirectY(u8 addr);

void SAX_Absolute(u16 addr);
void SAX_ZeroPage(u8 addr);
void SAX_ZeroPageY(u8 addr);
void SAX_IndirectX(u8 addr);

void DCP_ZeroPage(u8 addr);
void DCP_ZeroPageX(u8 addr);
void DCP_Absolute(u16 addr);
void DCP_AbsoluteX(u16 addr);
void DCP_AbsoluteY(u16 addr);
void DCP_IndirectX(u8 addr);
void DCP_IndirectY(u8 addr);

void ISC_Absolute(u16 addr);
void ISC_AbsoluteX(u16 addr);
void ISC_AbsoluteY(u16 addr);
void ISC_ZeroPage(u8 addr);
void ISC_ZeroPageX(u8 addr);
void ISC_IndirectX(u8 addr);
void ISC_IndirectY(u8 addr);

void RLA_Absolute(u16 addr);
void RLA_AbsoluteX(u16 addr);
void RLA_AbsoluteY(u16 addr);
void RLA_ZeroPage(u8 addr);
void RLA_ZeroPageX(u8 addr);
void RLA_IndirectX(u8 addr);
void RLA_IndirectY(u8 addr);

void RRA_Absolute(u16 addr);
void RRA_AbsoluteX(u16 addr);
void RRA_AbsoluteY(u16 addr);
void RRA_ZeroPage(u8 addr);
void RRA_ZeroPageX(u8 addr);
void RRA_IndirectX(u8 addr);
void RRA_IndirectY(u8 addr);

void SLO_Absolute(u16 addr);
void SLO_AbsoluteX(u16 addr);
void SLO_AbsoluteY(u16 addr);
void SLO_ZeroPage(u8 addr);
void SLO_ZeroPageX(u8 addr);
void SLO_IndirectX(u8 addr);
void SLO_IndirectY(u8 addr);

void SRE_Absolute(u16 addr);
void SRE_AbsoluteX(u16 addr);
void SRE_AbsoluteY(u16 addr);
void SRE_ZeroPage(u8 addr);
void SRE_ZeroPageX(u8 addr);
void SRE_IndirectX(u8 addr);
void SRE_IndirectY(u8 addr);
#endif //UNOFFICIAL_H_

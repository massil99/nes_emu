#include <stdlib.h>
#include "AND.h"
#include "ADC.h"
#include "ORA.h"
#include "EOR.h"
#include "ASL.h"
#include "LSR.h"
#include "ROR.h"
#include "ROL.h"
#include "cpu.h"
#include "PSW.h"
#include "SBC.h"
#include "COMPARE.h"
#include "INCDEC.h"
#include "bit_manipulation.h"
#include "add_mode.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void ALR(u8 m){
	AND(m);
	LSR_Accumulator();
}

void ANC(u8 m){
	AND(m);
	SET_STATUS_CARRY(cpu, U8_BIT7(cpu.A));
}

void ARR(u8 m){
	AND(m);
	ROR_Accumulator();
//SET_STATUS_CARRY(cpu, U8_BIT6(cpu.A));
//SET_STATUS_OVERFLOW(cpu, U8_BIT6(cpu.A) ^ U8_BIT5(cpu.A));
}

void AXS(u8 m){
	u8 temp = cpu.A;
	AND(cpu.X);
	SEC();	
	SBC(m);
	TAX();	
	cpu.A = temp;
}

void LAX_Absolute(u16 addr){
	LDA_Absolute(addr);
	LDX_Absolute(addr);
}
void LAX_AbsoluteY(u16 addr){
	LDA_AbsoluteY(addr);
	LDX_AbsoluteY(addr);
}
void LAX_ZeroPage(u8 addr){
	LDA_ZeroPage(addr);
	LDX_ZeroPage(addr);
}
void LAX_ZeroPageY(u8 addr){
	u8 val = get_zero_page_y(addr);
	cpu.A = val;
	LDX_ZeroPageY(addr);
}
void LAX_IndirectX(u8 addr){
	LDA_IndirectX(addr);
	u8 val = get_indirect_x(addr);
	cpu.X = val;	
}
void LAX_IndirectY(u8 addr){
	LDA_IndirectY(addr);
	u8 val = get_indirect_y(addr);
	cpu.X = val;
}

void SAX_Absolute(u16 addr){
	memory[addr] = cpu.A & cpu.X;	
}

void SAX_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.A & cpu.X);	
}

void SAX_ZeroPageY(u8 addr){
	set_zero_page_y(addr, cpu.A & cpu.X);	
}

void SAX_IndirectX(u8 addr){
	set_indirect_x(addr, cpu.A & cpu.X);	
}

/*************** DCP  ****************/
void DCP_ZeroPage(u8 addr){
	DEC_ZeroPage(addr);
	CMP_ZeroPage(addr);
}
void DCP_ZeroPageX(u8 addr){
	DEC_ZeroPageX(addr);
	CMP_ZeroPageX(addr);
}
void DCP_Absolute(u16 addr){
	DEC_Absolute(addr);
	CMP_Absolute(addr);
}
void DCP_AbsoluteX(u16 addr){
	DEC_AbsoluteX(addr);
	CMP_AbsoluteX(addr);
}
void DCP_AbsoluteY(u16 addr){
	u8 val = get_absolute_y(addr);
	val = DEC(val);
	set_absolute_y(addr, val);
	CMP_AbsoluteY(addr);
}
void DCP_IndirectX(u8 addr){
	u8 val = get_indirect_x(addr);
	val = DEC(val);
	set_indirect_x(addr, val);
	CMP_IndirectX(addr);
}
void DCP_IndirectY(u8 addr){
	u8 val = get_indirect_y(addr);
	val = DEC(val);
	set_indirect_y(addr, val);
	CMP_IndirectY(addr);
}

/*************** ISC ******************/
void ISC_Absolute(u16 addr){
	INC_Absolute(addr);
	SBC_Absolute(addr);
}
void ISC_AbsoluteX(u16 addr){
	INC_AbsoluteX(addr);
	SBC_AbsoluteX(addr);
}
void ISC_AbsoluteY(u16 addr){
	u8 val = get_absolute_y(addr);	
	val = INC(val);
	set_absolute_y(addr,  val);
	SBC_AbsoluteY(addr);
}
void ISC_ZeroPage(u8 addr){
	INC_ZeroPage(addr);
	SBC_ZeroPage(addr);
}
void ISC_ZeroPageX(u8 addr){
	INC_ZeroPageX(addr);
	SBC_ZeroPageX(addr);
}
void ISC_IndirectX(u8 addr){
	u8 val = get_indirect_x(addr);
	val = INC(val);
	set_indirect_x(addr, val);	
	SBC_IndirectX(addr);
}
void ISC_IndirectY(u8 addr){
	u8 val = get_indirect_y(addr);
	val = INC(val);
	set_indirect_y(addr, val);	
	SBC_IndirectY(addr);
}

void RLA_Absolute(u16 addr){
	ROL_Absolute(addr);
	AND_Absolute(addr);
}
void RLA_AbsoluteX(u16 addr){
	ROL_AbsoluteX(addr);
	AND_AbsoluteX(addr);
}
void RLA_AbsoluteY(u16 addr){
	u8 val = get_absolute_y(addr);
	val = ROL(val);
	set_absolute_y(addr, val);	
	AND_AbsoluteY(addr);
}
void RLA_ZeroPage(u8 addr){
	ROL_ZeroPage(addr);
	AND_ZeroPage(addr);
}
void RLA_ZeroPageX(u8 addr){
	ROL_ZeroPageX(addr);
	AND_ZeroPageX(addr);
}
void RLA_IndirectX(u8 addr){
	u8 val = get_indirect_x(addr);
	val = ROL(val);
	set_indirect_x(addr, val);
	AND_IndirectX(addr);
}
void RLA_IndirectY(u8 addr){
	u8 val = get_indirect_y(addr);
	val = ROL(val);
	set_indirect_y(addr, val);
	AND_IndirectY(addr);
}


void RRA_Absolute(u16 addr){
	ROR_Absolute(addr);
	ADC_Absolute(addr);
}
void RRA_AbsoluteX(u16 addr){
	ROR_AbsoluteX(addr);
	ADC_AbsoluteX(addr);
}
void RRA_AbsoluteY(u16 addr){
	u8 val = get_absolute_y(addr);
	val = ROR(val);
	set_absolute_y(addr, val);	
	ADC_AbsoluteY(addr);
}
void RRA_ZeroPage(u8 addr){
	ROR_ZeroPage(addr);
	ADC_ZeroPage(addr);
}
void RRA_ZeroPageX(u8 addr){
	ROR_ZeroPageX(addr);
	ADC_ZeroPageX(addr);
}
void RRA_IndirectX(u8 addr){
	u8 val = get_indirect_x(addr);
	val = ROR(val);
	set_indirect_x(addr, val);
	ADC_IndirectX(addr);
}
void RRA_IndirectY(u8 addr){
	u8 val = get_indirect_y(addr);
	val = ROR(val);
	set_indirect_y(addr, val);
	ADC_IndirectY(addr);
}

/*************** SLO *******************/
void SLO_Absolute(u16 addr){
	ASL_Absolute(addr);
	ORA_Absolute(addr);
}
void SLO_AbsoluteX(u16 addr){
	ASL_AbsoluteX(addr);
	ORA_AbsoluteX(addr);
}
void SLO_AbsoluteY(u16 addr){
	u8 val = get_absolute_y(addr);
	val = ASL(val);
	set_absolute_y(addr, val);	
	ORA_AbsoluteY(addr);
}
void SLO_ZeroPage(u8 addr){
	ASL_ZeroPage(addr);
	ORA_ZeroPage(addr);
}
void SLO_ZeroPageX(u8 addr){
	ASL_ZeroPageX(addr);
	ORA_ZeroPageX(addr);
}
void SLO_IndirectX(u8 addr){
	u8 val = get_indirect_x(addr);
	val = ASL(val);
	set_indirect_x(addr, val);	
	ORA_IndirectX(addr);
}
void SLO_IndirectY(u8 addr){
	u8 val = get_indirect_y(addr);
	val = ASL(val);
	set_indirect_y(addr, val);
	ORA_IndirectY(addr);
}

/***************** SRE ******************/

void SRE_Absolute(u16 addr){
	LSR_Absolute(addr);
	EOR_Absolute(addr);
}
void SRE_AbsoluteX(u16 addr){
	LSR_AbsoluteX(addr);
	EOR_AbsoluteX(addr);
}
void SRE_AbsoluteY(u16 addr){
	u8 val = get_absolute_y(addr);
	val = LSR(val);
	set_absolute_y(addr, val);
	EOR_AbsoluteY(addr);	
}
void SRE_ZeroPage(u8 addr){
	LSR_ZeroPage(addr);
	EOR_ZeroPage(addr);
}
void SRE_ZeroPageX(u8 addr){
	LSR_ZeroPageX(addr);
	EOR_ZeroPageX(addr);
}
void SRE_IndirectX(u8 addr){
	u8 val = get_indirect_x(addr);
	val = LSR(val);
	set_indirect_x(addr, val);
	EOR_IndirectX(addr);
}
void SRE_IndirectY(u8 addr){
	u8 val = get_indirect_y(addr);
	val = LSR(val);
	set_indirect_y(addr, val);
	EOR_IndirectY(addr);
}

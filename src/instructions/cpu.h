#ifndef _CPU_H
#define _CPU_H

#include <assert.h>
#include <stdint.h>
#include "bit_manipulation.h"

#define GET_STATUS_NEGATIVE(cpu) \
	 U8_BIT7(cpu.P)
#define SET_STATUS_NEGATIVE(cpu, value) \
	assert(value == 1 || value == 0);   \
	cpu.P = value? cpu.P | 0x80: cpu.P & 0x7f
	
#define GET_STATUS_OVERFLOW(cpu) \
	U8_BIT6(cpu.P)
#define SET_STATUS_OVERFLOW(cpu, value) \
	assert(value == 1 || value == 0); 	   \
	cpu.P = value? cpu.P | 0x40: cpu.P & 0xbf

#define GET_STATUS_DECIMAL(cpu) \
	U8_BIT3(cpu.P)
#define SET_STATUS_DECIMAL(cpu, value) \
	assert(value == 1 || value == 0); 	   \
	cpu.P = value? cpu.P | 0x08: cpu.P & 0xf7

#define GET_STATUS_INTERUPT(cpu) \
	U8_BIT2(cpu.P)
#define SET_STATUS_INTERUPT(cpu, value) \
	assert(value == 1 || value == 0); 	   \
	cpu.P = value? cpu.P | 0x04: cpu.P & 0xfb

#define GET_STATUS_BREAK(cpu) \
	U8_BIT4(cpu.P)
#define SET_STATUS_BREAK(cpu, value) \
	assert(value == 1 || value == 0); 	   \
	cpu.P = value? cpu.P | 0x10: cpu.P & 0xef

#define GET_STATUS_ZERO(cpu) \
	U8_BIT1(cpu.P)
#define SET_STATUS_ZERO(cpu, value) \
	assert(value == 1 || value == 0); 	   \
	cpu.P = value? cpu.P | 0x02: cpu.P & 0xfd

#define GET_STATUS_CARRY(cpu) \
	U8_BIT0(cpu.P) 
#define SET_STATUS_CARRY(cpu, value) \
	assert(value == 1 || value == 0); 	   \
	cpu.P = value? cpu.P | 0x01: cpu.P & 0xfe

#include "custom_types.h"

typedef struct {
	u8 A;
	u8 X;
	u8 Y;

	u8 P; 
	u8 SP;
	u16 PC;
}CPU_registers;

void STX_ZeroPage(u8 addr);
void STX_ZeroPageY(u8 addr);
void STX_Absolute(u16 addr);
void STY_ZeroPage(u8 addr);
void STY_ZeroPageX(u8 addr);
void STY_Absolute(u16 addr);
void STA_ZeroPage(u8 addr);
void STA_ZeroPageX(u8 addr);
void STA_Absolute(u16 addr);
void STA_AbsoluteX(u16 addr);
void STA_AbsoluteY(u16 addr);
void STA_IndirectX(u8 addr);
void STA_IndirectY(u8 addr);
void TAX();
void TAY();
void TSX();
void TXA();
void TYA();
void TXS();
void LDA(u8 m);
#define LDA_Immediate(mem) LDA(mem)
void LDA_ZeroPage(u8 addr);
void LDA_ZeroPageX(u8 addr);
void LDA_Absolute(u16 addr);
void LDA_AbsoluteX(u16 addr);
void LDA_AbsoluteY(u16 addr);
void LDA_IndirectX(u8 addr);
void LDA_IndirectY(u8 addr);
void LDX(u8 m);
#define LDX_Immediate(mem) LDX(mem)
void LDX_ZeroPage(u8 addr);
void LDX_ZeroPageY(u8 addr);
void LDX_Absolute(u16 addr);
void LDX_AbsoluteY(u16 addr);
void LDY(u8 m);
#define LDY_Immediate(mem) LDY(mem)
void LDY_ZeroPage(u8 addr);
void LDY_ZeroPageX(u8 addr);
void LDY_Absolute(u16 addr);
void LDY_AbsoluteX(u16 addr);

#endif //_CPU_H

#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include "add_mode.h"
#include "stdio.h"

extern u8 memory[MEMORY_SIZE];
CPU_registers cpu = {
	.A=0x00,
	.X=0x00,
	.Y=0x00,

	.P=0x24,
	.SP=0xFD,
	.PC=0x0000
};

void STX_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.X);
}

void STX_ZeroPageY(u8 addr){
	set_zero_page_y(addr, cpu.X);
}

void STX_Absolute(u16 addr){
	memory[addr] = cpu.X;
}

/***********************************************************************/
/*************************        STY          *************************/ 

void STY_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.Y);
}

void STY_ZeroPageX(u8 addr){
	set_zero_page_x(addr, cpu.Y);
}

void STY_Absolute(u16 addr){
	memory[addr] = cpu.Y;
}
/***********************************************************************/
/*************************        STA          *************************/ 

void STA_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.A);
}

void STA_ZeroPageX(u8 addr){
	set_zero_page_x(addr, cpu.A);
}

void STA_Absolute(u16 addr){
	memory[addr] = cpu.A;
}

void STA_AbsoluteX(u16 addr){
	set_absolute_x(addr, cpu.A);
}

void STA_AbsoluteY(u16 addr){
	set_absolute_y(addr, cpu.A);
}

void STA_IndirectX(u8 addr){
	set_indirect_x(addr, cpu.A);
}

void STA_IndirectY(u8 addr){
	set_indirect_y(addr, cpu.A);
}

// tax
void TAX(){
	cpu.X = cpu.A;
	SET_STATUS_ZERO(cpu, cpu.X == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));
}
// tay
void TAY(){
	cpu.Y = cpu.A;
	SET_STATUS_ZERO(cpu, cpu.Y == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.Y));
}

// tsx
void TSX(){
	cpu.X = cpu.SP;
	SET_STATUS_ZERO(cpu, cpu.X == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));
}

// TXA
void TXA(){
	cpu.A = cpu.X;
	SET_STATUS_ZERO(cpu, cpu.A == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));
}

// TYA
void TYA(){
	cpu.A = cpu.Y;
	SET_STATUS_ZERO(cpu, cpu.A == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));
}

// txs
void TXS(){
	cpu.SP = cpu.X;
}
/***********************************************************************/
/*************************         LDA         *************************/
void LDA(u8 m){
	cpu.A = m;
	SET_STATUS_ZERO(cpu, cpu.A == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));
}

#define LDA_Immediate(mem) LDA(mem)

void LDA_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	LDA(mem);
}

void LDA_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	LDA(mem);
}

void LDA_Absolute(u16 addr){
	u8 mem = memory[addr];
	LDA(mem);
}

void LDA_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	LDA(mem);
}

void LDA_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr); 
	LDA(mem);
}

void LDA_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	LDA(mem);
}

void LDA_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	LDA(mem);
}

/***********************************************************************/
/*************************         LDX         *************************/
void LDX(u8 m){
	cpu.X = m;
	SET_STATUS_ZERO(cpu, cpu.X == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));
}

#define LDX_Immediate(mem) LDX(mem)

void LDX_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	LDX(mem);
}

void LDX_ZeroPageY(u8 addr){
	u8 mem = get_zero_page_y(addr);
	LDX(mem);
}

void LDX_Absolute(u16 addr){
	u8 mem = memory[addr];
	LDX(mem);
}

void LDX_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr); 
	LDX(mem);
}
/***********************************************************************/
/*************************         LDY         *************************/ 
void LDY(u8 m){
	cpu.Y = m;
	SET_STATUS_ZERO(cpu, cpu.Y == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.Y));
}

#define LDY_Immediate(mem) LDY(mem)

void LDY_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	LDY(mem);
}

void LDY_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	LDY(mem);
}

void LDY_Absolute(u16 addr){
	u8 mem = memory[addr];
	LDY(mem);
}

void LDY_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr); 
	LDY(mem);
}

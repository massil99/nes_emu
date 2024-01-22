#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include "add_mode.h"
#include "stdio.h"

#include "../utils/utils.h"

extern u8 memory[MEMORY_SIZE];
CPU_registers cpu = {
	.A=0x00,
	.X=0x00,
	.Y=0x00,

	.P=0x24,
	.SP=0xFD,
	.PC=0x0000
};

size_t STX_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.X);

	return 3;
}

size_t STX_ZeroPageY(u8 addr){
	set_zero_page_y(addr, cpu.X);
	
	return 4;
}

size_t STX_Absolute(u16 addr){
	memory[addr] = cpu.X;

	return 4;
}

/***********************************************************************/
/*************************        STY          *************************/ 

size_t STY_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.Y);

	return 3;
}

size_t STY_ZeroPageX(u8 addr){
	set_zero_page_x(addr, cpu.Y);

	return 4;
}

size_t STY_Absolute(u16 addr){
	memory[addr] = cpu.Y;

	return 4;
}
/***********************************************************************/
/*************************        STA          *************************/ 

size_t STA_ZeroPage(u8 addr){
	set_zero_page(addr, cpu.A);

	return 3;
}

size_t STA_ZeroPageX(u8 addr){
	set_zero_page_x(addr, cpu.A);

	return 4;
}

size_t STA_Absolute(u16 addr){
	memory[addr] = cpu.A;

	return 4;
}

size_t STA_AbsoluteX(u16 addr){
	set_absolute_x(addr, cpu.A);

	return 5;
}

size_t STA_AbsoluteY(u16 addr){
	set_absolute_y(addr, cpu.A);

	return 5;
}

size_t STA_IndirectX(u8 addr){
	set_indirect_x(addr, cpu.A);

	return 6;
}

size_t STA_IndirectY(u8 addr){
	set_indirect_y(addr, cpu.A);

	return 6;
}

// tax
size_t TAX(){
	cpu.X = cpu.A;
	SET_STATUS_ZERO(cpu, cpu.X == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));

	return 2;
}
// tay
size_t TAY(){
	cpu.Y = cpu.A;
	SET_STATUS_ZERO(cpu, cpu.Y == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.Y));

	return 2;
}

// tsx
size_t TSX(){
	cpu.X = cpu.SP;
	SET_STATUS_ZERO(cpu, cpu.X == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));

	return 2;
}

// TXA
size_t TXA(){
	cpu.A = cpu.X;
	SET_STATUS_ZERO(cpu, cpu.A == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	return 2;
}

// TYA
size_t TYA(){
	cpu.A = cpu.Y;
	SET_STATUS_ZERO(cpu, cpu.A == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	return 2;
}

// txs
size_t TXS(){
	cpu.SP = cpu.X;

	return 2;
}
/***********************************************************************/
/*************************         LDA         *************************/
size_t LDA(u8 m){
	cpu.A = m;
	SET_STATUS_ZERO(cpu, cpu.A == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	return 2;
}

#define LDA_Immediate(mem) LDA(mem)

size_t LDA_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	LDA(mem);

	return 3;
}

size_t LDA_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	LDA(mem);

	return 4;
}

size_t LDA_Absolute(u16 addr){
	u8 mem = memory[addr];
	LDA(mem);

	return 4;
}

size_t LDA_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	LDA(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

size_t LDA_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr); 
	LDA(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

size_t LDA_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	LDA(mem);

	return 6;
}

size_t LDA_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	LDA(mem);

	if(page_crossed(addr, mem))
		return 6;
	else
		return 5;
}

/***********************************************************************/
/*************************         LDX         *************************/
size_t LDX(u8 m){
	cpu.X = m;
	SET_STATUS_ZERO(cpu, cpu.X == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));

	return 2;
}

#define LDX_Immediate(mem) LDX(mem)

size_t LDX_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	LDX(mem);

	return 3;
}

size_t LDX_ZeroPageY(u8 addr){
	u8 mem = get_zero_page_y(addr);
	LDX(mem);

	return 4;
}

size_t LDX_Absolute(u16 addr){
	u8 mem = memory[addr];
	LDX(mem);

	return 4;
}

size_t LDX_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr); 
	LDX(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}
/***********************************************************************/
/*************************         LDY         *************************/ 
size_t LDY(u8 m){
	cpu.Y = m;
	SET_STATUS_ZERO(cpu, cpu.Y == 0x00);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.Y));

	return 2;
}

#define LDY_Immediate(mem) LDY(mem)

size_t LDY_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	LDY(mem);

	return 3;
}

size_t LDY_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	LDY(mem);

	return 4;
}

size_t LDY_Absolute(u16 addr){
	u8 mem = memory[addr];
	LDY(mem);
	
	return 4;
}

size_t LDY_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr); 
	LDY(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

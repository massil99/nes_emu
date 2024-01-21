#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include "add_mode.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void SBC(u8 m){
	u8 carry = GET_STATUS_CARRY(cpu);
	u8 mb7 = U8_BIT7(m);
	u8 ab7 = U8_BIT7(cpu.A); 

	if(cpu.A < m){
		SET_STATUS_CARRY(cpu, 0); 
	}else{
		SET_STATUS_CARRY(cpu, 1); 
	}
	cpu.A = cpu.A - m - (0x01 - carry);

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	if((!mb7 == ab7) && (mb7 == U8_BIT7(cpu.A))){
		SET_STATUS_OVERFLOW(cpu, 1);
	}else{
		SET_STATUS_OVERFLOW(cpu, 0);
	}

	if(cpu.A == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}
}

#define SBC_Immediate(mem) SBC(mem) 

void SBC_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	SBC(mem);
}

void SBC_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	SBC(mem);
}

void SBC_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	SBC(mem);
}

void SBC_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr); 
	SBC(mem);
}

void SBC_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	SBC(mem);
}

void SBC_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	SBC(mem);
}

void SBC_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	SBC(mem);
}

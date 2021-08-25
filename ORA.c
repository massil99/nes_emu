
#include "add_mode.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern u8 memory[MEMORY_SIZE];
extern CPU_registers cpu;

void ORA(u8 m){
	u8 temp = 0x00;	
	temp |= (cpu.A & 0x80) | (m & 0x80);
	temp |= (cpu.A & 0x40) | (m & 0x40);
	temp |= (cpu.A & 0x20) | (m & 0x20);
	temp |= (cpu.A & 0x10) | (m & 0x10);
	temp |= (cpu.A & 0x08) | (m & 0x08);
	temp |= (cpu.A & 0x04) | (m & 0x04);
	temp |= (cpu.A & 0x02) | (m & 0x02);
	temp |= (cpu.A & 0x01) | (m & 0x01);
	cpu.A = temp;

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	if(cpu.A == 0x00){
		SET_STATUS_ZERO(cpu, 1);	
	}else{
		SET_STATUS_ZERO(cpu, 0);	
	}
}

#define ORA_Immediate(mem) OR(mem)

void ORA_ZeroPage(u8 addr){
	u8 m = get_zero_page(addr);
	ORA(m);
}

void ORA_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	ORA(mem);
}

void ORA_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	ORA(mem);
}

void ORA_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	ORA(mem);
}

void ORA_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	ORA(mem);
}

void ORA_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	ORA(mem);
}

void ORA_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	ORA(mem);
}

#include "custom_types.h"
#include "add_mode.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"
#include "../utils/utils.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t AND(u8 m){
	u8 temp = 0x00;	
	temp |= (cpu.A & 0x80) & (m & 0x80);
	temp |= (cpu.A & 0x40) & (m & 0x40);
	temp |= (cpu.A & 0x20) & (m & 0x20);
	temp |= (cpu.A & 0x10) & (m & 0x10);
	temp |= (cpu.A & 0x08) & (m & 0x08);
	temp |= (cpu.A & 0x04) & (m & 0x04);
	temp |= (cpu.A & 0x02) & (m & 0x02);
	temp |= (cpu.A & 0x01) & (m & 0x01);
	cpu.A = temp;

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	if(cpu.A == 0x00){
		SET_STATUS_ZERO(cpu, 1);	
	}else {
		SET_STATUS_ZERO(cpu, 0);	
	}

	return 2;
}

#define AND_Immediate(mem) AND(mem)

size_t AND_ZeroPage(u8 addr){
	u8 m = get_zero_page(addr);
	AND(m);

	return 3;
}

size_t AND_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	AND(mem);

	return 4;
}

size_t AND_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	AND(mem);

	return 4;
}

size_t AND_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	AND(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

size_t AND_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	AND(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

size_t AND_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	AND(mem);

	return 6;
}

size_t AND_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	AND(mem);

	if(page_crossed(addr, mem))
		return 6;
	else
		return 5;
}


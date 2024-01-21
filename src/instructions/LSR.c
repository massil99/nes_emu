
#include "add_mode.h"
#include "custom_types.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

u8 LSR(u8 m){
	SET_STATUS_CARRY(cpu, U8_BIT0(m));
	u8 res = m >> 1;
	
	if(res == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(res));
	return res;
}

void LSR_Accumulator(){
	cpu.A = LSR(cpu.A);
}

void LSR_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	u8 res = LSR(mem);
	set_zero_page(addr, res);
}

void LSR_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	u8 res = LSR(mem);
	set_zero_page_x(addr, res);
}

void LSR_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	u8 res = LSR(mem);
	memory[addr] = res;
}

void LSR_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	u8 res = LSR(mem);
	set_absolute_x(addr, res);
}

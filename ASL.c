
#include "custom_types.h"
#include "add_mode.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void ASL_Accumulator(){
	SET_STATUS_CARRY(cpu, U8_BIT7(cpu.A));
	
	cpu.A <<= 1;

	if(cpu.A == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));
}

u8 ASL(u8 mem){
	SET_STATUS_CARRY(cpu, U8_BIT7(mem));
	
	u8 res = mem << 1;

	if(res == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	} 

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(res));
	return res;
}

void ASL_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	u8 res = ASL(mem);
	set_zero_page(addr, res);
}

void ASL_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	u8 res = ASL(mem);
	set_zero_page_x(addr, res);
}

void ASL_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	u8 res = ASL(mem);
	memory[addr] = res;	
}

void ASL_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	u8 res = ASL(mem);
	set_absolute_x(addr, res);
}

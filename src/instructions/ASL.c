
#include "custom_types.h"
#include "add_mode.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

#include "../utils/utils.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t ASL_Accumulator(){
	SET_STATUS_CARRY(cpu, U8_BIT7(cpu.A));
	
	cpu.A <<= 1;

	if(cpu.A == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));

	return 2;
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

size_t ASL_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	u8 res = ASL(mem);
	set_zero_page(addr, res);

	return 5;
}

size_t ASL_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	u8 res = ASL(mem);
	set_zero_page_x(addr, res);

	return 6;
}

size_t ASL_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	u8 res = ASL(mem);
	memory[addr] = res;	

	return 6;
}

size_t ASL_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	u8 res = ASL(mem);
	set_absolute_x(addr, res);

	return 7;
}

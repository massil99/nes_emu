
#include "add_mode.h"
#include "custom_types.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

u8 ROR(u8 m){
	u8 bit0 = U8_BIT0(m);
	u8 res = (m>>1);	

	if(GET_STATUS_CARRY(cpu))
		res = res | 0x80;
	else
		res = res & 0x7f;
	
	if(res == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_CARRY(cpu, bit0);
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(res));
	return res;
}

size_t ROR_Accumulator(){
	cpu.A = ROR(cpu.A);

	return 2;
}

size_t ROR_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	u8 res = ROR(mem);
	set_zero_page(addr, res);

	return 5;
}

size_t ROR_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	u8 res = ROR(mem);
	set_zero_page_x(addr, res);
	
	return 6;
}

size_t ROR_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	u8 res = ROR(mem);
	memory[addr] = res;
	
	return 6;
}

size_t ROR_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	u8 res = ROR(mem);
	set_absolute_x(addr, res);

	return 7;
}

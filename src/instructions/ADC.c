#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include "add_mode.h"

#include "../utils/utils.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t ADC(u8 m){
	u8 carry = GET_STATUS_CARRY(cpu);
	u8 mb7 = U8_BIT7(m);
	u8 ab7 = U8_BIT7(cpu.A); 

	cpu.A += m + carry;

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.A));
	
	if((mb7 || ab7) && !U8_BIT7(cpu.A)){
		SET_STATUS_CARRY(cpu, 1);
	} else{
		SET_STATUS_CARRY(cpu, 0);
	}

	if((mb7 == ab7) && (mb7 != U8_BIT7(cpu.A))){
		SET_STATUS_OVERFLOW(cpu, 1);
	}else{
		SET_STATUS_OVERFLOW(cpu, 0);
	}

	if(cpu.A == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}

	return 2; // cycles
}

// $69
#define ADC_Immediate(mem) ADC(mem) 

// $65
size_t ADC_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	ADC(mem);

	return 3;
}


// $75
size_t ADC_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	ADC(mem);

	return 4;
}

// $6D
size_t ADC_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	ADC(mem);

	return 4;
}

// $7D
size_t ADC_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr); 
	ADC(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

// $79
size_t ADC_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	ADC(mem);

	if(page_crossed(addr, mem))
		return 5;
	else
		return 4;
}

// $61
size_t ADC_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	ADC(mem);

	return 6;
}

// $71
size_t ADC_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	ADC(mem);

	if(page_crossed(addr, mem))
		return 6;
	else
		return 5;
}

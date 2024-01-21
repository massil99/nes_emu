#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include "add_mode.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void ADC(u8 m){
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
}

// $69
#define ADC_Immediate(mem) ADC(mem) 

// $65
void ADC_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	ADC(mem);
}


// $75
void ADC_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	ADC(mem);
}

// $6D
void ADC_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	ADC(mem);
}

// $7D
void ADC_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr); 
	ADC(mem);
}

// $79
void ADC_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	ADC(mem);
}

// $61
void ADC_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);
	ADC(mem);
}

// $71
void ADC_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	ADC(mem);
}

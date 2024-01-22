#include "cpu.h"
#include "add_mode.h"
#include "custom_types.h"
#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include <stdbool.h>

#include "../utils/utils.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t BCC(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_CARRY(cpu) == 0x00){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BCS(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_CARRY(cpu) == 0x01){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BEQ(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_ZERO(cpu) == 0x01){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BNE(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_ZERO(cpu) == 0x00){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BMI(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_NEGATIVE(cpu) == 0x01){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BPL(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_NEGATIVE(cpu) == 0x00){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BVC(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;

	if(GET_STATUS_OVERFLOW(cpu) == 0x00){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t BVS(s8 offset){
	size_t cycles = 2;
	u16 oldPC = cpu.PC;
	if(GET_STATUS_OVERFLOW(cpu) == 0x01){
		cpu.PC += offset;
		cycles += 1;
	}

	if(page_crossed(oldPC, cpu.PC)){
		cycles += 2;
	}

	return cycles;
}

size_t JMP(u16 m){
	cpu.PC = m;

	return 3;
}

#define JMP_Absolute(addr) JMP(addr)

size_t JMP_Indirect(u16 addr){
	if(addr & 0xff == 0xff)
		cpu.PC = memory[addr] + (memory[addr & 0xff00]<<8); 
	else
		cpu.PC = memory[addr] + (memory[addr +1]<<8); 

	return 5;
}

size_t JSR(u16 addr){
	u16 ret = cpu.PC + 2;
	push_word(ret);
	JMP(addr);

	return 6;
}

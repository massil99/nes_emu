#include "cpu.h"
#include "add_mode.h"
#include "custom_types.h"
#include "cpu.h"
#include "stack.h"
#include "memory.h"
#include <stdbool.h>

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

bool BCC(s8 offset){
	if(GET_STATUS_CARRY(cpu) == 0x00){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

bool BCS(s8 offset){
	if(GET_STATUS_CARRY(cpu) == 0x01){
		cpu.PC += offset;
		return true;
	}else	
		return false;
}

bool BEQ(s8 offset){
	if(GET_STATUS_ZERO(cpu) == 0x01){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

bool BNE(s8 offset){
	if(GET_STATUS_ZERO(cpu) == 0x00){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

bool BMI(s8 offset){
	if(GET_STATUS_NEGATIVE(cpu) == 0x01){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

bool BPL(s8 offset){
	if(GET_STATUS_NEGATIVE(cpu) == 0x00){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

bool BVC(s8 offset){
	if(GET_STATUS_OVERFLOW(cpu) == 0x00){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

bool BVS(s8 offset){
	if(GET_STATUS_OVERFLOW(cpu) == 0x01){
		cpu.PC += offset;
		return true;
	}else
		return false;
}

void JMP(u16 m){
	cpu.PC = m;
}

#define JMP_Absolute(addr) JMP(addr)

void JMP_Indirect(u16 addr){
	if(addr & 0xff == 0xff)
		cpu.PC = memory[addr] + (memory[addr & 0xff00]<<8); 
	else
		cpu.PC = memory[addr] + (memory[addr +1]<<8); 
}

void JSR(u16 addr){
	u16 ret = cpu.PC + 2;
	push_word(ret);
	JMP(addr);
}

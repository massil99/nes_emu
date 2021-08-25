#include "custom_types.h"
#include "add_mode.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"
#include "PSW.h"
#include "bit_manipulation.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void BRK(){
	push_word(cpu.PC);
	PHP();
	cpu.PC = 0x0000;
	cpu.PC = memory[0xfffe];
	cpu.PC |= memory[0xffff] << 8;
	
	SET_STATUS_BREAK(cpu, 1);
}

void RTS(){
	u8 lo = pull();
	u8 hi = pull();
	
	cpu.PC = (hi<<8) + lo;
	cpu.PC += 3;
}

void RTI(){
	cpu.P = pull();
	u8 lo = pull();
	u8 hi = pull();
	
	cpu.PC = (hi<<8) + lo;
}

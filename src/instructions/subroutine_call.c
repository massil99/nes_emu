#include "custom_types.h"
#include "add_mode.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"
#include "PSW.h"
#include "bit_manipulation.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t BRK(){
	push_word(cpu.PC);
	PHP();
	cpu.PC = 0x0000;
	cpu.PC = memory[0xfffe];
	cpu.PC |= memory[0xffff] << 8;
	
	SET_STATUS_BREAK(cpu, 1);

	return 7;
}

size_t RTS(){
	u8 lo = pull();
	u8 hi = pull();
	
	cpu.PC = (hi<<8) + lo;

	return 6;	
}

size_t RTI(){
	u8 status = pull();
	cpu.P = 0x30 & cpu.P;
	cpu.P |= (status & 0xcf);

	u8 lo = pull();
	u8 hi = pull();
	
	cpu.PC = (hi<<8) + lo;

	return 6;	
}

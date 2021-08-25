
#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "custom_types.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void PHA(){
	push(cpu.A);
}

void PLA(){
	u8 acc = pull();	
	if(acc == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}	
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(acc));
	cpu.A = acc;
}

void PHP(){
	push(cpu.P | 0x10);
}

void PLP(){
	u8 status = pull() | 0x20;
	cpu.P = status;
}

void SEC(){
	SET_STATUS_CARRY(cpu, 1);
}

void SED(){
	SET_STATUS_DECIMAL(cpu, 1);
}

void SEI(){
	SET_STATUS_INTERUPT(cpu, 1);
}

void SEV(){
	SET_STATUS_OVERFLOW(cpu, 1);
}

void CLC(){
	SET_STATUS_CARRY(cpu, 0);
}

void CLD(){
	SET_STATUS_DECIMAL(cpu, 0);
}

void CLI(){
	SET_STATUS_INTERUPT(cpu, 0);
}

void CLV(){
	SET_STATUS_OVERFLOW(cpu, 0);
}

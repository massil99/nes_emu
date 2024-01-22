
#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "custom_types.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t PHA(){
	push(cpu.A);

	return 3;
}

size_t PLA(){
	u8 acc = pull();	
	if(acc == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}	
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(acc));
	cpu.A = acc;

	return 4;
}

size_t PHP(){
	push(cpu.P | 0x30);

	return 3;
}

size_t PLP(){
	u8 status = pull();
	
	cpu.P = 0x30 & cpu.P;
	cpu.P |= (status & 0xcf);

	return 4;
}

size_t SEC(){
	SET_STATUS_CARRY(cpu, 1);
	return 2;
}

size_t SED(){
	SET_STATUS_DECIMAL(cpu, 1);
	return 2;
}

size_t SEI(){
	SET_STATUS_INTERUPT(cpu, 1);
	return 2;
}

size_t SEV(){
	SET_STATUS_OVERFLOW(cpu, 1);
	return 2;
}

size_t CLC(){
	SET_STATUS_CARRY(cpu, 0);
	return 2;
}

size_t CLD(){
	SET_STATUS_DECIMAL(cpu, 0);
	return 2;
}

size_t CLI(){
	SET_STATUS_INTERUPT(cpu, 0);
	return 2;
}

size_t CLV(){
	SET_STATUS_OVERFLOW(cpu, 0);
	return 2;
}

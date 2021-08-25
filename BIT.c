
#include "add_mode.h"
#include "custom_types.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void BIT(u8 m){
	u8 temp = 0x00;	
	temp |= (cpu.A & 0x80) & (m & 0x80);
	temp |= (cpu.A & 0x40) & (m & 0x40);
	temp |= (cpu.A & 0x20) & (m & 0x20);
	temp |= (cpu.A & 0x10) & (m & 0x10);
	temp |= (cpu.A & 0x08) & (m & 0x08);
	temp |= (cpu.A & 0x04) & (m & 0x04);
	temp |= (cpu.A & 0x02) & (m & 0x02);
	temp |= (cpu.A & 0x01) & (m & 0x01);
	
	if(temp == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	} else{
		SET_STATUS_ZERO(cpu, 0);
	}

	SET_STATUS_NEGATIVE(cpu, U8_BIT7(m));
	SET_STATUS_OVERFLOW(cpu, U8_BIT6(m));
}

void BIT_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	BIT(mem);
}

void BIT_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	BIT(mem);
}

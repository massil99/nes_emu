
#include "add_mode.h"
#include "custom_types.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

#include "../utils/utils.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

size_t CMP(u8 m){
	SET_STATUS_CARRY(cpu, (cpu.A >= m));
	u8 temp  =  cpu.A - m;
	SET_STATUS_ZERO(cpu, (temp == 0x00));
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(temp));

	return 2;
} 

#define CMP_Immediate(mem) CMP(mem)

size_t CMP_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	CMP(mem);

	return 3;
}

size_t CMP_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	CMP(mem);

	return 4;
}

size_t CMP_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr]; 
	CMP(mem);

	return 4;
}

size_t CMP_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	CMP(mem);

	if(page_crossed(addr, mem))
		return 5;
	else 
		return 4;
}

size_t CMP_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	CMP(mem);

	if(page_crossed(addr, mem))
		return 5;
	else 
		return 4;
}

size_t CMP_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);	
	CMP(mem);

	return 6;
}

size_t CMP_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	CMP(mem);

	if(page_crossed(addr, mem))
		return 6;
	else 
		return 5;
}

/***********************************************************************/
/***********************        CPX       ******************************/
size_t CPX(u8 m){
	SET_STATUS_CARRY(cpu, (cpu.X >= m));
	u8 temp =  cpu.X - m;
	SET_STATUS_ZERO(cpu, (temp == 0x00));
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(temp));

	return 2;
}

#define CPX_Immediate(mem) CPX(mem)

size_t CPX_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	CPX(mem);

	return 3;
}

size_t CPX_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	CPX(mem);

	return 4;
}

/***********************************************************************/
/***********************        CPY       ******************************/
size_t CPY(u8 m){
	SET_STATUS_CARRY(cpu, (cpu.Y >= m));
	u8 temp =  cpu.Y - m;
	SET_STATUS_ZERO(cpu, (temp == 0x00));
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(temp));

	return 2;
}

#define CPY_Immediate(mem) CPY(mem)

size_t CPY_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	CPY(mem);

	return 3;
}

size_t CPY_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	CPY(mem);

	return 4;
}


#include "add_mode.h"
#include "custom_types.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void CMP(u8 m){
	SET_STATUS_CARRY(cpu, (cpu.A >= m));
	u8 temp  =  cpu.A - m;
	SET_STATUS_ZERO(cpu, (temp == 0x00));
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(temp));
} 

#define CMP_Immediate(mem) CMP(mem)

void CMP_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	CMP(mem);
}

void CMP_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	CMP(mem);
}

void CMP_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr]; 
	CMP(mem);
}

void CMP_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	CMP(mem);
}

void CMP_AbsoluteY(u16 addr){
	u8 mem = get_absolute_y(addr);
	CMP(mem);
}

void CMP_IndirectX(u8 addr){
	u8 mem = get_indirect_x(addr);	
	CMP(mem);
}

void CMP_IndirectY(u8 addr){
	u8 mem = get_indirect_y(addr);
	CMP(mem);
}

/***********************************************************************/
/***********************        CPX       ******************************/
void CPX(u8 m){
	SET_STATUS_CARRY(cpu, (cpu.X >= m));
	u8 temp =  cpu.X - m;
	SET_STATUS_ZERO(cpu, (temp == 0x00));
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(temp));
}

#define CPX_Immediate(mem) CPX(mem)

void CPX_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	CPX(mem);
}

void CPX_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	CPX(mem);
}

/***********************************************************************/
/***********************        CPY       ******************************/
void CPY(u8 m){
	SET_STATUS_CARRY(cpu, (cpu.Y >= m));
	u8 temp =  cpu.Y - m;
	SET_STATUS_ZERO(cpu, (temp == 0x00));
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(temp));
}

#define CPY_Immediate(mem) CPY(mem)

void CPY_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	CPY(mem);
}

void CPY_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	CPY(mem);
}

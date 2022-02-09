#include "add_mode.h"
#include "custom_types.h"
#include "stack.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

u8 DEC(u8 mem){
	u8 res = --mem;
	if(res == 0){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(res));
	return res;
}

void DEC_ZeroPage(u8 addr){
	u8 mem = get_zero_page(addr);
	u8 res = DEC(mem);
	set_zero_page(addr, res);
}

void DEC_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	u8 res = DEC(mem);
	set_zero_page_x(addr, res);
}

void DEC_Absolute(u16 addr){
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	u8 res = DEC(mem);
	memory[addr] = res;
}

void DEC_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	u8 res = DEC(mem);
	set_absolute_x(addr, res);
}

/***********************************************************************/
/***********************    DERegister    ******************************/
void DEX(){
	--cpu.X;

	if(cpu.X == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{	
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));
}

void DEY(){
	--cpu.Y;

	if(cpu.Y == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.Y));
}

/***********************************************************************/
/***********************        INC       ******************************/
u8 INC(u8 mem){
	u8 res = mem + 1;
	printf("%04x > %04x", mem, res);
	if(res == 0){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(res));
	return res;
}

void INC_ZeroPage(u8 addr){
	printf("pz %02x ", addr);
	u8 mem = get_zero_page(addr);
	u8 res = INC(mem);
	set_zero_page(addr, res);
}

void INC_ZeroPageX(u8 addr){
	u8 mem = get_zero_page_x(addr);
	u8 res = INC(mem);
	set_zero_page_x(addr, res);
}

void INC_Absolute(u16 addr){
	printf("abs %04x ", addr);
	assert(addr < MEMORY_SIZE);
	u8 mem = memory[addr];
	u8 res = INC(mem);
	memory[addr] = res;
}

void INC_AbsoluteX(u16 addr){
	u8 mem = get_absolute_x(addr);
	u8 res = INC(mem);
	set_absolute_x(addr, res);
}

/***********************************************************************/
/***********************    INCRegister    ******************************/
void INX(){
	++cpu.X;

	if(cpu.X == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.X));
}

void INY(){
	++cpu.Y;

	if(cpu.Y == 0x00){
		SET_STATUS_ZERO(cpu, 1);
	}else{
		SET_STATUS_ZERO(cpu, 0);
	}
	SET_STATUS_NEGATIVE(cpu, U8_BIT7(cpu.Y));
}

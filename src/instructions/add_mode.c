#include <stdlib.h>
#include <stdio.h>

#include "custom_types.h"
#include "cpu.h"
#include "memory.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

u8 get_zero_page(u8 addr){
	assert(addr >=0 && addr < MEMORY_SIZE);
	return memory[addr];
}
void set_zero_page(u8 addr, u8 val){
	assert(addr < MEMORY_SIZE);
	memory[addr] = val;
}

u8 get_zero_page_y(u8 addr){
	u16 sum = cpu.Y + addr; 	
	sum = sum & 0xff;
	return memory[sum];
}
void set_zero_page_y(u8 addr, u8 val){
	u16 sum = cpu.Y + addr; 	
	sum = sum & 0xff;
	memory[sum] = val;
}

u8 get_zero_page_x(u8 addr){
	u16 sum = cpu.X + addr; 	
	sum = sum & 0xff;
	return memory[sum];
}
void set_zero_page_x(u8 addr, u8 val){
	u16 sum = cpu.X + addr; 	
	sum = sum & 0xff;
	memory[sum] = val;
}

u8 get_absolute_x(u16 addr){
	u16 sum = cpu.X + addr; 	
	assert(sum < MEMORY_SIZE);	
	u8 res = memory[sum];
	return res;
}
void set_absolute_x(u16 addr, u8 val){
	u16 sum = cpu.X + addr; 	
	assert(sum < MEMORY_SIZE);	
	memory[sum] = val;
}

u8 get_absolute_y(u16 addr){
	u16 sum = cpu.Y + addr; 	
	assert(sum < MEMORY_SIZE);	
	return memory[sum];
}
void set_absolute_y(u16 addr, u8 val){
	u16 sum = cpu.Y + addr; 	
	assert(sum < MEMORY_SIZE);	
	memory[sum] = val;
}

u8 get_indirect(u16 addr){
	u16 sum = addr;
	u8 l_in_addr = memory[sum];

	sum += 1;
	assert(sum < MEMORY_SIZE);	
	u16 in_addr = (memory[sum] << 8)  + l_in_addr;

	assert(in_addr < MEMORY_SIZE);	
	return memory[in_addr];
}

u8 get_indirect_x(u16 addr){
	u16 sum = (cpu.X + addr) & 0xff; 	

	u8 l_in_addr = memory[sum];

	sum += 1;
	sum = sum & 0xff;
	u16 in_addr = (memory[sum] << 8) + l_in_addr;

	assert(in_addr < MEMORY_SIZE);	
	return memory[in_addr];
}

void set_indirect_x(u16 addr, u8 val){
	u16 sum = (cpu.X + addr) & 0xff; 	

	u8 l_in_addr = memory[sum];

	sum += 1;
	sum = sum & 0xff;
	u16 in_addr = (memory[sum] << 8) + l_in_addr;

	assert(in_addr < MEMORY_SIZE);	
	memory[in_addr] = val;
}

u8 get_indirect_y(u8 addr){
	u16 in_addr = ((memory[(u8)(addr + 1)] << 8) + memory[(u8)addr]) + cpu.Y; 	

	assert(in_addr < MEMORY_SIZE);	
	return memory[in_addr];
}

void set_indirect_y(u8 addr, u8 val){
	u16 in_addr = ((memory[(u8)(addr + 1)] << 8) + memory[(u8)addr]) + cpu.Y; 	

	assert(in_addr < MEMORY_SIZE);	
	memory[in_addr] = val;
}

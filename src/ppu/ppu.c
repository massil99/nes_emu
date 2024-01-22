#include <stdlib.h>
#include <stdio.h>

#include "../bit_manipulation.h"
#include "../memory.h"
#include "ppu.h"

u8 ppu_memory[PPU_MEMORY_SIZE];
u32 OAM[OAM_SIZE];
extern u8 memory[MEMORY_SIZE];

void power_up_ppu(){
	set_PPUCTRL(0);
	set_PPUMASK(0);
	set_PPUSTATUS(0xA0);
	//set_OAMADDR(0);
}

void set_PPUCTRL(u8 flag){
	for(u16 i = R_PPUCTRL; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_PPUMASK(u8 flag){
	for(u16 i = R_PPUMASK; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_PPUSTATUS(u8 flag){
	for(u16 i = R_PPUSTATUS; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_OAMADDR(u8 flag){
	for(u16 i = R_OAMADDR; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_OAMDATA(u8 flag){
	for(u16 i = R_OAMDATA; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_PPUSCROLL(u8 flag){
	for(u16 i = R_PPUSCROLL; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_PPUADDR(u8 flag){
	for(u16 i = R_PPUADDR; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}
void set_PPUDATA(u8 flag){
	for(u16 i = R_PPUDATA; i <= PPU_REGISTERS_BOUNDERY; i+=8){
		memory[i] = flag;
		printf("%04x %02x\n", i, memory[i]);
	}
}

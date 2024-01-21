#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 65536 

// Memory map
#define STACK_START 0x0100
#define STACK_END 0x01ff

#define ZERO_PAGE_START 0x0000	// RAM, zero-page
#define ZERO_PAGE_END   0x00FF	

#define STACK_START 0x0100 // CPU STACK
#define STACK_END   0x01ff

#define GP_RAM_START 0x0200 // RAM, general-purpose
#define GP_RAM_END   0x07FF

#define FIRST_MIRROR_START 0x0800	//(mirror of $0000-$07FF)
#define FIRST_MIRROR_END   0x1FFF	

#define PPU_REGISTER_START 0x2000 // PPU registers
#define PPU_REGISTER_END	0x2007

#define SECOND_MIRROR_START 0x2008 //(mirror of $2000-$2007)
#define SECOND_MIRROR_END   0x3FFF

#define APU_REGISTERS_START 0x4000	//APU registers
#define APU_REGISTERS_END   Ox400F

#define EXTRA_REGISTERS_START 0x4010 // DMC, joystick, APU registers
#define EXTRA_REGISTERS_END   0x4017 

#define CARTRIDGE_START 0x4020	// Cartridge (maybe mapper registers)
#define CARTRIDGE_END   0x5FFF	

#define CARTRIDGE_RAM_START 0x6000// Cartridge RAM (maybe battery-backed)
#define CARTRIDGE_RAM_END   0x7FFF

#define PRG_ROM_START 0x8000 // PRG ROM (maybe bank switched)
#define	PRG_ROM_END   0xFFFF

#define NMI_VECTOR_START 0xfffa	// NMI vector
#define	NMI_VECTOR_END   0xFFFB

#define RESET_VECTOR_START 0xfffc	// Reset vector
#define RESET_VECTOR_END   0xFFFD

#define BRK_VECTOR_START 0xfffe// BRK vector
#define BRK_VECTOR_END 0xFFFF	


#include "custom_types.h"

void dump_memory(u16 start);
#endif //MEMORY_H

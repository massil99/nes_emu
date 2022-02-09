#ifndef PPU_H_
#define PPU_H_

#include "../INST/custom_types.h"

#define PPU_MEMORY_SIZE 16384

#define OAM_SIZE 64

#define PPU_REGISTERS_BOUNDERY 0x3fff

#define R_PPUCTRL   0x2000
#define GET_PPUCTRL_FLAG_V\
	(memory[R_PPUCTRL] >> 7)
#define GET_PPUCTRL_FLAG_P \
	((memory[R_PPUCTRL] & 0x40) >> 6)
#define GET_PPUCTRL_FLAG_H \
	((memory[R_PPUCTRL] & 0x20) >> 5)
#define GET_PPUCTRL_FLAG_B \
	((memory[R_PPUCTRL] & 0x10) >> 4)
#define GET_PPUCTRL_FLAG_S \
	((memory[R_PPUCTRL] & 0x8) >> 3)
#define GET_PPUCTRL_FLAG_I \
	((memory[R_PPUCTRL] & 0x4) >> 2)
#define GET_PPUCTRL_FLAG_NN \
	(memory[R_PPUCTRL] & 0x3)

#define R_PPUMASK   0x2001
#define GET_PPUMASK_FLAG_BGR\
	(memory[R_PPUMASK] >> 5)
#define GET_PPUMASK_FLAG_s \
	((memory[R_PPUMASK] & 0x10) >> 4)
#define GET_PPUMASK_FLAG_b \
	((memory[R_PPUMASK] & 0x8) >> 3)
#define GET_PPUMASK_FLAG_M \
	((memory[R_PPUMASK] & 0x4) >> 2)
#define GET_PPUMASK_FLAG_m \
	((memory[R_PPUMASK] & 0x2) >> 1)
#define GET_PPUMASK_FLAG_G \
	(memory[R_PPUMASK] & 0x1)

#define R_PPUSTATUS 0x2002
#define GET_PPUSTATUS_FLAG_V \
	(memory[R_PPUSTATUS] >> 7)
#define GET_PPUSTATUS_FLAG_S \
	((memory[R_PPUSTATUS] & 0x40) >> 6)
#define GET_PPUSTATUS_FLAG_O \
	((memory[R_PPUSTATUS] & 0x20) >> 5)

#define R_OAMADDR   0x2003
#define R_OAMDATA   0x2004
#define R_PPUSCROLL 0x2005
#define R_PPUADDR   0x2006
#define R_PPUDATA   0x2007
#define R_OAMDMA    0x4014
void set_PPUCTRL(u8 flag);
void set_PPUMASK(u8 flag);
void set_PPUSTATUS(u8 flag);
void set_OAMADDR(u8 flag);
void set_OAMDATA(u8 flag);
void set_PPUSCROLL(u8 flag);
void set_PPUADDR(u8 flag);
void set_PPUDATA(u8 flag);

#endif //PPU_H_

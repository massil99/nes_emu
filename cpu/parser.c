#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "../INST/bit_manipulation.h"
#include "../INST/memory.h"
#include "../INST/instructions.h"
#include "../INST/custom_types.h"
#include "../INST/add_mode.h"
#include "../ppu/ppu.h"

#include "time.h"
#include "errno.h"

#define PRG_ROM_START_LOWER_BANK 0x8000
#define PRG_ROM_START_UPPER_BANK 0xc000
#define INES_FILE_SIGNATURE 0x4e45531a

typedef struct {
	u32 signature;;
	u8 PRG_SIZE;
	u8 CHR_SIZE;
	u8 FLAGS6;
	u8 FLAGS7;
	u8 FLAGS8;
	u8 FLAGS9;
	u8 FLAGS10;
} INES_Header;

extern u8 memory[MEMORY_SIZE];
extern CPU_registers cpu;
u8 ppu_memory[PPU_MEMORY_SIZE];

int msleep(long msec){
    struct timespec ts;
    int res;

    if (msec < 0){
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
} 

int main(int argc, char *argv[]){
	char *path = argv[1];
	FILE* file = fopen(path, "rb");
	INES_Header header = {0, 0, 0, 0, 0, 0, 0, 0};
	
	if(file == NULL){
		fprintf(stderr, "[ERROR]: No such file %s\n", path);
		exit(EXIT_FAILURE);
	}
	
	u8 buf;

	// File signature
	fread(&buf, sizeof(u8), 1, file); 
	header.signature |= buf << 24;
	fread(&buf, sizeof(u8), 1, file); 
	header.signature |= buf << 16;
	fread(&buf, sizeof(u8), 1, file);
	header.signature |= buf << 8;
	fread(&buf, sizeof(u8), 1, file);
	header.signature |= buf;

	// Checking file signature
	if(header.signature != INES_FILE_SIGNATURE){
		fprintf(stderr, "[ERROR]: %s not a NES file\n", path);	
		exit(EXIT_FAILURE);
	}
	
	// Reading header information
	fread(&header.PRG_SIZE, sizeof(u8), 1, file);
	fread(&header.CHR_SIZE, sizeof(u8), 1, file);
	fread(&header.FLAGS6,	sizeof(u8), 1, file);
	fread(&header.FLAGS7,	sizeof(u8), 1, file);
	fread(&header.FLAGS8,	sizeof(u8), 1, file);
	fread(&header.FLAGS9,	sizeof(u8), 1, file);
	fread(&header.FLAGS10,  sizeof(u8), 1, file);

	// Skiping blank bytes
	for(int i = 0; i < 5; i++)
		fread(&buf, sizeof(u8), 1, file);

	// Loading trainer
	if(U8_BIT2(header.FLAGS6)){
		printf("trainer available");
	}
	
	// Loading PRG rom
	if(header.PRG_SIZE == 1){
		// Single page rom
		for(int i = 0; i < 16384; i++){
			fread(&buf, sizeof(u8), 1, file);
			memory[i + PRG_ROM_START_LOWER_BANK] = buf;
		}	
		// Merroring
		for(int i = 0; i < 16384; i++){
			memory[i + PRG_ROM_START_UPPER_BANK] = memory[i + PRG_ROM_START_LOWER_BANK];
		}	
	} else {
		// Double paged rom
		for(int i = 0; i < header.PRG_SIZE*16384; i++){
			fread(&buf, sizeof(u8), 1, file);
			memory[i + PRG_ROM_START_LOWER_BANK] = buf;
		}	
	} 

	/*************** RAM SHIT ************/
/*	memory[0x180] = 0x33;
	memory[0x17f] = 0x69;
	memory[0x678] = 0xff;

	memory[0x33] = 0xa3;
	memory[0x97] = 0xff;
	memory[0x98] = 0xff;

	memory[0xff] = 0x46;
	memory[0x0] = 0x01;
	memory[0x245] = 0x012;*/
	/****************************************/

	// Loagding PPU information
	for(int i = 0; i < 8192; i++){
		fread(&buf, sizeof(u8), 1, file);
		ppu_memory[i] = buf;
	}	

	
	u16 addr = 0;
	cpu.PC = memory[0xfffc] + (memory[0xfffd] << 8);
	int i = 0;
	while(i < 8991){
		printf("A:(%02x) ", cpu.A);
		// PRINT_BYTE(cpu.A);
		 printf("X:(%02x) ", cpu.X);
		// PRINT_BYTE(cpu.X);
		printf("Y:(%02x) ", cpu.Y);
		// PRINT_BYTE(cpu.Y);
		printf("SP:(%02x) ", cpu.SP);
		// PRINT_BYTE(cpu.SP);
		printf("P:(%02x) ", cpu.P);
		// PRINT_BYTE(cpu.P);
		switch(memory[cpu.PC]){
			case OPC_ADCI:
				printf("%04x ADC %x ", cpu.PC, memory[cpu.PC+1]);
				ADC_Immediate(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ADCZP:
				printf("%04x ADC %x", cpu.PC, memory[cpu.PC+1]);
				ADC_ZeroPage(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ADCZPX:
				printf("%04x ADC %x", cpu.PC, memory[cpu.PC+1]);
				ADC_ZeroPageX(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ADCA:
				printf("%04x ADC %x", cpu.PC, memory[cpu.PC+1]);
				addr =  memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ADC_Absolute(addr);				
				cpu.PC += 3;
				break;
			case OPC_ADCAX:
				printf("%04x ADC %x", cpu.PC, memory[cpu.PC+1]);
				addr =  memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ADC_AbsoluteX(addr);				
				cpu.PC += 3;
				break;
			case OPC_ADCAY:
				addr =  memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x ADC %x", cpu.PC, addr);
				ADC_AbsoluteY(addr);				
				cpu.PC += 3;
				break;
			case OPC_ADCINDX:
				printf("%04x ADC %x", cpu.PC, addr);
				ADC_IndirectX(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ADCINDY:
				printf("%04x ADC %x", cpu.PC, memory[cpu.PC+1]);
				ADC_IndirectY(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;

			case OPC_ANDI:
				printf("%04x AND ", cpu.PC);
				AND_Immediate(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;

			case OPC_ANDZP:
				printf("%04x AND ", cpu.PC);
				AND_ZeroPage(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ANDZPX:
				printf("%04x AND ", cpu.PC);
				AND_ZeroPageX(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ANDA:
				printf("%04x AND ", cpu.PC);
				addr =  memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				AND_Absolute(addr);				
				cpu.PC += 3;
				break;
			case OPC_ANDAX:
				printf("%04x AND ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				AND_AbsoluteX(addr);				
				cpu.PC += 3;
				break;
			case OPC_ANDAY:
				printf("%04x AND ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				AND_AbsoluteY(addr);				
				cpu.PC += 3;
				break;
			case OPC_ANDINDX:
				printf("%04x AND ", cpu.PC);
				AND_IndirectX(memory[cpu.PC+1]);				
				cpu.PC += 2;
				break;
			case OPC_ANDINDY:
				printf("%04x AND ", cpu.PC);
				AND_IndirectY(memory[cpu.PC+1]);				
				cpu.PC += 2;

				break;
			case OPC_ASLACC:
				printf("%04x ASL ", cpu.PC);
				ASL_Accumulator();
				cpu.PC += 1;
				break;
			case OPC_ASLZP:
				printf("%04x ASL ", cpu.PC);
				ASL_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ASLZPX:
				printf("%04x ASL ", cpu.PC);
				ASL_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ASLA:
				printf("%04x ASL ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ASL_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_ASLAX:
				printf("%04x ASL ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ASL_AbsoluteX(addr);
				cpu.PC += 3;
				break;

			case OPC_BCCR:
				printf("%04x BCC %x ", cpu.PC, memory[cpu.PC+1]);
				BCC(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_BCSR:
				printf("%04x BCS %2x ", cpu.PC, memory[cpu.PC+1]);
				BCS(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_BEQR:
				printf("%04x BEQ ", cpu.PC);
				BEQ(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_BITZP:
				printf("%04x BITzp ", cpu.PC);
				BIT_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
					   break;
			case OPC_BITA:
				printf("%04x BITa ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				BIT_Absolute(addr);
				cpu.PC += 3;
				break;

			case OPC_BMIR: 
				printf("%04x BMI ", cpu.PC);
				BMI(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_BNER:
				printf("%04x BNE ", cpu.PC);
				BNE(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_BPLR:
				printf("%04x BPL %x", cpu.PC, memory[cpu.PC+1]);
				BPL(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_BRKIMP:
				printf("%04x BRK ", cpu.PC);
				BRK();
				break;

			case OPC_BVCR:
				printf("%04x BVC ", cpu.PC);
				s8 offset = (s8)  memory[cpu.PC+1];
				BVC(offset); 
				cpu.PC += 2;
				break;

			case OPC_BVSR:
				printf("%04x bvs ", cpu.PC);
				BVS(memory[cpu.PC+1]);
				cpu.PC +=  2;
				break;

			case OPC_CLCIMP:
				printf("%04x clc ", cpu.PC);
				CLC();
				cpu.PC += 1;
				break;

			case OPC_CLDIMP:
				printf("%04x cld ", cpu.PC);
				CLD();
				cpu.PC += 1;
				break;

			case OPC_CLIIMP:
				printf("%04x cli ", cpu.PC);
				CLI();
				cpu.PC += 1;
				break;

			case OPC_CLVIMP:
				printf("%04x clv ", cpu.PC);
				CLV();
				cpu.PC += 1;
				break;

			case OPC_CMPI:	
				printf("%04x CMP %02x", cpu.PC, memory[cpu.PC+1]);
				CMP_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CMPZP:	
				printf("%04x CMP %02x", cpu.PC, get_zero_page(memory[cpu.PC+1]));
				CMP_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CMPZPX:	
				printf("%04x CMP %02x", cpu.PC, get_absolute_x(memory[cpu.PC+1]));
				CMP_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CMPA:	
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x CMP %02x", cpu.PC, memory[addr]);
				CMP_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_CMPAX:	
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x CMP %02x", cpu.PC, memory[addr]);
				CMP_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_CMPAY:	
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x CMP %02x", cpu.PC,  memory[addr]);
				CMP_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_CMPINDX:	
				printf("%04x CMP %02x", cpu.PC, get_indirect_x(memory[cpu.PC+1]));
				CMP_IndirectX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CMPINDY:	
				printf("%04x CMP %02x", cpu.PC, get_indirect_y(memory[cpu.PC+1]));
				CMP_IndirectY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
	
			case OPC_CPXI:	
				printf("%04x cpx ", cpu.PC);
				CPX_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CPXZP:	
				printf("%04x cpx ", cpu.PC);
				CPX_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CPXA:	
				printf("%04x cpx ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				CPX_Absolute(addr);
				cpu.PC += 3;
				break;

			case OPC_CPYI:	
				printf("%04x cpy ", cpu.PC);
				CPY_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CPYZP:	
				printf("%04x cpy ", cpu.PC);
				CPY_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_CPYA:	
				printf("%04x cpy ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				CPY_Absolute(addr);
				cpu.PC += 3;
				break;

			case OPC_DECZP:
				printf("%04x dec ", cpu.PC);
				DEC_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_DECZPX:
				printf("%04x dec ", cpu.PC);
				DEC_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_DECA:	
				printf("%04x dec ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				DEC_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_DECAX:	
				printf("%04x dec ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				DEC_AbsoluteX(addr);
				cpu.PC += 3;
				break;

			case OPC_DEXIMP:
				printf("%04x dex ", cpu.PC);
				DEX();
				cpu.PC += 1;
				break;

			case OPC_DEYIMP:
				printf("%04x dey ", cpu.PC);
				DEY();
				cpu.PC += 1;
				break;

 			case OPC_EORI:
				printf("%04x EOR ", cpu.PC);
				EOR_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_EORZP:
				printf("%04x EOR ", cpu.PC);
				EOR_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_EORZPX: 
				printf("%04x EOR ", cpu.PC);
				EOR_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_EORA:
				printf("%04x EOR ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				EOR_Absolute(addr);
				cpu.PC += 3;
				break;
 			case OPC_EORAX:
				printf("%04x EOR ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				EOR_AbsoluteX(addr);
				cpu.PC += 3;
				break;
 			case OPC_EORAY:
				printf("%04x EOR ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				EOR_AbsoluteY(addr);
				cpu.PC += 3;
				break;
 			case OPC_EORINDX:
				printf("%04x EOR ", cpu.PC);
				EOR_IndirectX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_EORINDY:
				printf("%04x EOR ", cpu.PC);
				EOR_IndirectY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;

			case OPC_INCZP:
				printf("%04x inc ", cpu.PC);
				INC_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_INCZPX:
				printf("%04x inc ", cpu.PC);
				INC_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_INCA:
				printf("%04x inc ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				INC_Absolute(addr);
				cpu.PC += 3;
				break;
 			case OPC_INCAX:
				printf("%04x inc ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				INC_AbsoluteX(addr);
				cpu.PC += 3;
				break;

			case OPC_INXIMP:
				printf("%04x inx ", cpu.PC);
				INX();
				cpu.PC += 1;
				break;
			case OPC_INYIMP:
				printf("%04x iny ", cpu.PC);
				INY();
				cpu.PC += 1;
				break;

			case OPC_JMPA:
				printf("%04x jmp ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				JMP_Absolute(addr);
				break;
			case OPC_JMPIND:
				printf("%04x jmp ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				JMP_Indirect(addr);
				break;

			case OPC_JSRA:
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x jsr %04x | %02x %02x %02x", cpu.PC, addr, memory[cpu.PC], memory[cpu.PC+1],memory[cpu.PC+2]);
				JSR(addr);
				break;

 			case OPC_LDAI:
				printf("%04x LDAi %x ", cpu.PC, memory[cpu.PC+1]);
				LDA_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDAZP:
				printf("%04x LDAzp %x ", cpu.PC, get_zero_page(memory[cpu.PC+1]));
				LDA_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDAZPX: 
				printf("%04x LDAzpx %x ", cpu.PC, get_absolute_x(memory[cpu.PC+1]) );
				LDA_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDAA:
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x LDAa %x ", cpu.PC, addr);
				LDA_Absolute(addr);
				cpu.PC += 3;
				break;
 			case OPC_LDAAX:
				printf("%04x LDAax %x ", cpu.PC, get_absolute_x(cpu.PC + 1));
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LDA_AbsoluteX(addr);
				cpu.PC += 3;
				break;
 			case OPC_LDAAY:
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x LDAay  @%04x = %02x ", cpu.PC, addr, get_absolute_y(addr));
				LDA_AbsoluteY(addr);
				cpu.PC += 3;
				break;
 			case OPC_LDAINDX:
				printf("%04x LDAindx @%04x = %02x ", cpu.PC, memory[cpu.PC+1], get_absolute_y(memory[cpu.PC+1]));
				LDA_IndirectX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break; 
			case OPC_LDAINDY: 
				printf("%04x LDAindy @%04x = %02x ", cpu.PC, memory[cpu.PC+1], get_absolute_y(memory[cpu.PC+1]));
				LDA_IndirectY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;

 			case OPC_LDXI:
				printf("%04x LDXi ", cpu.PC);
				LDX_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDXZP:
				printf("%04x LDXzp ", cpu.PC);
				LDX_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDXZPY: 
				printf("%04x LDXzpy ", cpu.PC);
				LDX_ZeroPageY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDXA:
				printf("%04x LDXa ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LDX_Absolute(addr);
				cpu.PC += 3;
				break;
 			case OPC_LDXAY:
				printf("%04x LDXay ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LDX_AbsoluteY(addr);
				cpu.PC += 3;
				break;

 			case OPC_LDYI:
				printf("%04x ldy ", cpu.PC);
				LDY_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDYZP:
				printf("%04x ldy ", cpu.PC);
				LDY_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDYZPX: 
				printf("%04x ldy ", cpu.PC);
				LDY_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LDYA:
				printf("%04x ldy ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LDY_Absolute(addr);
				cpu.PC += 3;
				break;
 			case OPC_LDYAX:
				printf("%04x ldy ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LDY_AbsoluteX(addr);
				cpu.PC += 3;
				break;

 			case OPC_LSRACC:
				printf("%04x lsr ", cpu.PC);
				LSR_Accumulator(memory[cpu.PC+1]);
				cpu.PC += 1;
				break;
 			case OPC_LSRZP:
				printf("%04x lsr ", cpu.PC);
				LSR_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LSRZPX: 
				printf("%04x lsr ", cpu.PC);
				LSR_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
 			case OPC_LSRA:
				printf("%04x lsr ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LSR_Absolute(addr);
				cpu.PC += 3;
				break;
 			case OPC_LSRAX:
				printf("%04x lsr ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LSR_AbsoluteX(addr);
				cpu.PC += 3;
				break;

			case OPC_ING  :
			case OPC_ING1 :
			case OPC_ING2 :
			case OPC_ING3 :
			case OPC_ING4 :
			case OPC_ING5 :
			case OPC_ING6 :
				printf("%04x NOP ", cpu.PC);
				cpu.PC += 3;
				break;

			case OPC_SKB   :
			case OPC_SKB1  :
			case OPC_SKB2  :
			case OPC_SKB3  :
			case OPC_SKB4  :
			case OPC_SKB5  :
			case OPC_SKB6  :
			case OPC_SKB7  :
			case OPC_SKB8  :
			case OPC_SKB9  :
			case OPC_SKB10 :
			case OPC_SKB11 :
			case OPC_SKB12 :
				printf("%04x NOP ", cpu.PC);
				cpu.PC += 2;
				break;
	
			case OPC_NOP:
			case OPC_NOP_DUP1:
			case OPC_NOP_DUP2:
			case OPC_NOP_DUP3:
			case OPC_NOP_DUP4:
			case OPC_NOP_DUP5:
				printf("%04x NOP ", cpu.PC);
				cpu.PC += 1;
				break;
			
			case OPC_ORAI:
				printf("%04x ora ", cpu.PC);
				ORA_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ORAZP:
				printf("%04x ora ", cpu.PC);
				ORA_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ORAZPX: 
				printf("%04x ora ", cpu.PC);
				ORA_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ORAA:
				printf("%04x ora ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ORA_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_ORAAX:
				printf("%04x ora ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ORA_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_ORAAY:
				printf("%04x ora ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ORA_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_ORAINDX:
				printf("%04x ora ", cpu.PC);
				ORA_IndirectX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ORAINDY:	
				printf("%04x ora ", cpu.PC);
				ORA_IndirectY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
		
			case OPC_PHAIMP:
				printf("%04x pha ", cpu.PC);
				PHA();
				cpu.PC += 1;
				break;
			case OPC_PHPIMP:
				printf("%04x php ", cpu.PC);
				PHP();
				cpu.PC += 1;
				break;
			case OPC_PLAIMP:
				printf("%04x pla ", cpu.PC);
				PLA();
				cpu.PC += 1;
				break;
			case OPC_PLPIMP:
				printf("%04x plp ", cpu.PC);
				PLP();
				cpu.PC += 1;
				break;

			case OPC_ROLACC:
				printf("%04x rol ", cpu.PC);
				ROL_Accumulator();
				cpu.PC += 1;
				break;
			case OPC_ROLZP:
				printf("%04x rol ", cpu.PC);
				ROL_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ROLZPX:
				printf("%04x rol ", cpu.PC);
				ROL_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_ROLA:
				printf("%04x rol ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ROL_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_ROLAX:
				printf("%04x rol ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ROL_AbsoluteX(addr);
				cpu.PC += 3;
				break;
	

			case OPC_RORACC:
				printf("%04x ROR ", cpu.PC);
				ROR_Accumulator();
				cpu.PC += 1;
				break;
			case OPC_RORZP:
				printf("%04x ROR ", cpu.PC);
				ROR_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_RORZPX:
				printf("%04x ROR ", cpu.PC);
				ROR_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_RORA:
				printf("%04x ROR ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ROR_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_RORAX:
				printf("%04x ROR ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				ROR_AbsoluteX(addr);
				cpu.PC += 3;
				break;

			case OPC_RTIIMP:
				printf("%04x rti ", cpu.PC);
				RTI();
				break;

			case OPC_RTSIMP:
				printf("%04x rts ", cpu.PC);
				RTS();
				cpu.PC++;
				break;

			case OPC_SBCI_U:
			case OPC_SBCI:
				printf("%04x SBCi %02x ", cpu.PC, memory[cpu.PC+1]);
				SBC_Immediate(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_SBCZP:
				printf("%04x sbc ", cpu.PC);
				SBC_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_SBCZPX:
				printf("%04x sbc ", cpu.PC);
				SBC_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_SBCA:
				printf("%04x sbc ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				SBC_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_SBCAX:
				printf("%04x sbc ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				SBC_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_SBCAY:
				printf("%04x sbc ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				SBC_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_SBCINDX:
				printf("%04x sbc ", cpu.PC);
				SBC_IndirectX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_SBCINDY:
				printf("%04x sbc ", cpu.PC);
				SBC_IndirectY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			
			case OPC_SECIMP:
				printf("%04x sec ", cpu.PC);
				SEC();
				cpu.PC += 1;	
				break;

			case OPC_SEDIMP:
				printf("%04x sed ", cpu.PC);
				SED();
				cpu.PC += 1;	
				break;

			case OPC_SEIIMP:
				printf("%04x sei ", cpu.PC);
				SEI();
				cpu.PC += 1;	
				break;

			case OPC_STAZP:
				printf("%04x STA ", cpu.PC);
				STA_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STAZPX:
				printf("%04x sta ", cpu.PC);
				STA_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STAA:
				printf("%04x sta ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				STA_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_STAAX:
				printf("%04x sta ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				STA_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_STAAY:
				printf("%04x sta ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				STA_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_STAINDX:
				printf("%04x sta ", cpu.PC);
				STA_IndirectX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STAINDY:
				printf("%04x sta ", cpu.PC);
				STA_IndirectY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;

			case OPC_STXZP:
				printf("%04x stx ", cpu.PC);
				STX_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STXZPY:
				printf("%04x stx ", cpu.PC);
				STX_ZeroPageY(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STXA:
				printf("%04x stx ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				STX_Absolute(addr);
				cpu.PC += 3;
				break;

			case OPC_STYZP:
				printf("%04x sty ", cpu.PC);
				STY_ZeroPage(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STYZPX:
				printf("%04x sty ", cpu.PC);
				STY_ZeroPageX(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			case OPC_STYA:
				printf("%04x sty ", cpu.PC);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				STY_Absolute(addr);
				cpu.PC += 3;
				break;

			case OPC_TAXIMP:
				printf("%04x tax ", cpu.PC);
				TAX();
				cpu.PC += 1;
				break;

			case OPC_TAYIMP:
				printf("%04x tay ", cpu.PC);
				TAY();
				cpu.PC += 1;
				break;

			case OPC_TSXIMP:
				printf("%04x tsx ", cpu.PC);
				TSX();
				cpu.PC += 1;
				break;

			case OPC_TXAIMP:
				printf("%04x txa ", cpu.PC);
				TXA();
				cpu.PC += 1;
				break;

			case OPC_TXSIMP:
				printf("%04x txs ", cpu.PC);
				TXS();
				printf("txs %x", cpu.SP);
				cpu.PC += 1;
				break;

			case OPC_TYAIMP:
				printf("%04x tya ", cpu.PC);
				TYA();
				cpu.PC += 1;
				break;
			
			case OPC_ALR:
				printf("%04x ALR %02x ", cpu.PC, memory [cpu.PC+1]);
				ALR(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;

			case OPC_ANC:
				printf("%04x ANC %02x ", cpu.PC, memory[cpu.PC+1]);
				ANC(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
			
			case OPC_ARR:
				printf("%04x ARR %02x ", cpu.PC, memory[cpu.PC+1]);
				ARR(memory[cpu.PC+1]);
				cpu.PC += 2;
				break;
				
			case OPC_AXS:
				printf("%04x AXS %02x ", cpu.PC, memory[cpu.PC+1]);
				AXS(memory[cpu.PC+1]);
				cpu.PC += 1;
				break;

			case OPC_LAXa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x LAXa %02x ", cpu.PC, memory[addr]);
				LAX_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_LAXay   :
				printf("%04x LAXay %02x ", cpu.PC, get_absolute_y(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				LAX_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_LAXzp   :
				printf("%04x LAXzp %02x ", cpu.PC, get_zero_page(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				LAX_ZeroPage(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;
			case OPC_LAXzpy  :
				printf("%04x LAXzpy %02x ", cpu.PC, get_absolute_y(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				LAX_ZeroPageY(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;
			case OPC_LAXINDX :
				printf("%04x LAXindx %02x ", cpu.PC, get_indirect_x(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				LAX_IndirectX(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;
			case OPC_LAXINDY :
				printf("%04x LAXindy %02x ", cpu.PC, get_indirect_y(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				LAX_IndirectY(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;

			case OPC_SAXa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SAXa %02x ", cpu.PC, memory[addr]);
				SAX_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_SAXzp   :
				printf("%04x SAXzp %02x ", cpu.PC, get_zero_page(memory[cpu.PC+1]));
 				SAX_ZeroPage(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;
			case OPC_SAXzpy  :
				printf("%04x SAXzpy %02x ", cpu.PC, get_absolute_y(memory[cpu.PC+1]));
				SAX_ZeroPageY(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;
			case OPC_SAXINDX :
				printf("%04x SAXindx %02x ", cpu.PC, get_indirect_x(memory[cpu.PC+1]));
 				SAX_IndirectX(memory[cpu.PC + 1]);
				cpu.PC += 2;
				break;

			case OPC_DCPa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x DCPa %02x ", cpu.PC, memory[addr]);
				DCP_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_DCPax   :
				printf("%04x DCPax %02x ", cpu.PC, get_absolute_x(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				DCP_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_DCPay   :
				printf("%04x DCPay %02x ", cpu.PC, get_absolute_y(memory[cpu.PC+1] + (memory[cpu.PC+2] <<8)));
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				DCP_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_DCPzp   :
				printf("%04x DCPzp %02x ", cpu.PC, get_zero_page(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				DCP_ZeroPage(addr);
				cpu.PC += 2;
				break;
			case OPC_DCPzpx  :
				printf("%04x DCPzpx %02x ", cpu.PC, get_absolute_x(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				DCP_ZeroPageX(addr);
				cpu.PC += 2;
				break;
			case OPC_DCPINDX :
				printf("%04x DCPindx %02x ", cpu.PC, get_indirect_x(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				DCP_IndirectX(addr);
				cpu.PC += 2;
				break;
			case OPC_DCPINDY :
				printf("%04x DCPindy %02x ", cpu.PC, get_indirect_y(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				DCP_IndirectY(addr);
				cpu.PC += 2;
				break;

			case OPC_ISCa    :
				printf("%04x ISBa %02x ", cpu.PC, memory[addr]);
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8);
				ISC_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_ISCax   :
				printf("%04x ISBax %02x ", cpu.PC, get_absolute_x(memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8)));
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8);
				ISC_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_ISCay   :
				printf("%04x ISBay %02x ", cpu.PC, get_absolute_y(memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8)));
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8);
				ISC_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_ISCzp   :
				printf("%04x ISBzp %02x ", cpu.PC, get_zero_page(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				ISC_ZeroPage(addr);
				cpu.PC += 2;
				break;
			case OPC_ISCzpx  :
				printf("%04x ISBzpx %02x ", cpu.PC, get_absolute_x(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				ISC_ZeroPageX(addr);
				cpu.PC += 2;
				break;
			case OPC_ISCINDX :
				printf("%04x ISBindx %02x ", cpu.PC, get_indirect_x(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				ISC_IndirectX(addr);
				cpu.PC += 2;
				break;
			case OPC_ISCINDY :
				printf("%04x ISBindy %02x ", cpu.PC, get_indirect_y(memory[cpu.PC+1]));
				addr = memory[cpu.PC+1];
				ISC_IndirectY(addr);
				cpu.PC += 2;
				break;
			
			case OPC_RLAa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8);
				printf("%04x RLAa %02x ", cpu.PC, memory[addr]);
				RLA_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_RLAax   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8);
				printf("%04x RLAax %02x ", cpu.PC, get_absolute_x(addr));
				RLA_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_RLAay   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2]  << 8);
				printf("%04x RLAay %02x ", cpu.PC, get_absolute_y(addr));
				RLA_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_RLAzp   :
				addr = memory[cpu.PC+1];
				printf("%04x RLAzp %02x ", cpu.PC, get_zero_page(addr));
				RLA_ZeroPage(addr);
				cpu.PC += 2;
				break;
			case OPC_RLAzpx  :
				addr = memory[cpu.PC+1];
				printf("%04x RLAzpx %02x ", cpu.PC, get_absolute_x(addr));
				RLA_ZeroPageX(addr);
				cpu.PC += 2;
				break;
			case OPC_RLAINDX :
				addr = memory[cpu.PC+1];
				printf("%04x RLAindx %02x ", cpu.PC, get_indirect_x(addr));
				RLA_IndirectX(addr);
				cpu.PC += 2;
				break;
			case OPC_RLAINDY :
				addr = memory[cpu.PC+1];
				printf("%04x RLAindy %02x ", cpu.PC, get_indirect_y(addr));
				RLA_IndirectY(addr);
				cpu.PC += 2;
				break;

			case OPC_RRAa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x RRAa %02x ", cpu.PC,memory[addr]);
				RRA_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_RRAax   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x RRAax %02x ", cpu.PC, get_absolute_x(addr));
				RRA_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_RRAay   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x RRAay %02x ", cpu.PC, get_absolute_y(addr));
				RRA_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_RRAzp   :
				addr = memory[cpu.PC+1];
				printf("%04x RRAzp %02x ", cpu.PC, get_zero_page(addr));
				RRA_ZeroPage(addr);
				cpu.PC += 2;
				break;
			case OPC_RRAzpx  :
				addr = memory[cpu.PC+1];
				printf("%04x RRAzpx %02x ", cpu.PC, get_absolute_x(addr));
				RRA_ZeroPageX(addr);
				cpu.PC += 2;
				break;
			case OPC_RRAINDX :
				addr = memory[cpu.PC+1];
				printf("%04x RRAindx %02x ", cpu.PC, get_indirect_x(addr));
				RRA_IndirectX(addr);
				cpu.PC += 2;
				break;
			case OPC_RRAINDY :
				addr = memory[cpu.PC+1];
				printf("%04x RRAindx %02x ", cpu.PC, get_indirect_y(addr));
				RRA_IndirectY(addr);
				cpu.PC += 2;
				break;

			case OPC_SLOa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SLOa %02x ", cpu.PC,memory[addr]);
				SLO_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_SLOax   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SLOax %02x ", cpu.PC, get_absolute_x(addr));
				SLO_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_SLOay   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SLOay %02x ", cpu.PC, get_absolute_y(addr));
				SLO_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_SLOzp   :
				addr = memory[cpu.PC+1];
				printf("%04x SLOzp %02x ", cpu.PC, get_zero_page(addr));
				SLO_ZeroPage(addr);
				cpu.PC += 2;
				break;
			case OPC_SLOzpx  :
				addr = memory[cpu.PC+1];
				printf("%04x SLOzpx %02x ", cpu.PC, get_absolute_x(addr));
				SLO_ZeroPageX(addr);
				cpu.PC += 2;
				break;
			case OPC_SLOINDX :
				addr = memory[cpu.PC+1];
				printf("%04x SLOindx %02x ", cpu.PC, get_indirect_x(addr));
				SLO_IndirectX(addr);
				cpu.PC += 2;
				break;
			case OPC_SLOINDY :
				addr = memory[cpu.PC+1];
				printf("%04x SLOindy %02x ", cpu.PC, get_indirect_y(addr));
				SLO_IndirectY(addr);
				cpu.PC += 2;
				break;

			case OPC_SREa    :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SREa %02x ", cpu.PC,memory[addr]);
				SRE_Absolute(addr);
				cpu.PC += 3;
				break;
			case OPC_SREax   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SREax %02x ", cpu.PC, get_absolute_x(addr));
				SRE_AbsoluteX(addr);
				cpu.PC += 3;
				break;
			case OPC_SREay   :
				addr = memory[cpu.PC+1] + (memory[cpu.PC+2] << 8);
				printf("%04x SREay %02x ", cpu.PC, get_absolute_y(addr));
				SRE_AbsoluteY(addr);
				cpu.PC += 3;
				break;
			case OPC_SREzp   :
				addr = memory[cpu.PC+1];
				printf("%04x SREzp %02x ", cpu.PC, get_zero_page(addr));
				SRE_ZeroPage(addr);
				cpu.PC += 2;
				break;
			case OPC_SREzpx  :
				addr = memory[cpu.PC+1];
				printf("%04x SREzpx %02x ", cpu.PC, get_absolute_x(addr));
				SRE_ZeroPageX(addr);
				cpu.PC += 2;
				break;
			case OPC_SREINDX :
				addr = memory[cpu.PC+1];
				printf("%04x SREindx %02x ", cpu.PC, get_indirect_x(addr));
				SRE_IndirectX(addr);
				cpu.PC += 2;
				break;
			case OPC_SREINDY :
				addr = memory[cpu.PC+1];
				printf("%04x SREindy %02x ", cpu.PC, get_indirect_y(addr));
				SRE_IndirectY(addr);
				cpu.PC += 2;
				break;

			default:
				printf("%04x NOP %3x ", cpu.PC, memory[cpu.PC]);
				++cpu.PC;
		}
		i++;
		printf("\n");
	}
	fclose(file);
	return EXIT_SUCCESS;
}

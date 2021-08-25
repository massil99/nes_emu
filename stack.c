
#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "stack.h"

#include "custom_types.h"

extern CPU_registers cpu;
extern u8 memory[MEMORY_SIZE];

void push(u8 byte){
	if(cpu.SP > 0) {
		memory[STACK_START + cpu.SP--] = byte;	
	}
}

void push_word(u16 word){
	if(cpu.SP > 1){
		u8 byte = (u8) (word >> 8);
		memory[STACK_START + cpu.SP--] = byte;	

		byte = (u8)(word & 0xff);
		memory[STACK_START + cpu.SP--] = byte;	
	}
}

u8 pull(){
	if(cpu.SP <= 0xff){
		return memory[STACK_START + ++cpu.SP];
	} else {
		return 0;
	}
}

u16 pull_word(){
	u16 result = 0x00;
	if(cpu.SP <= 0xff - 1){
		result = memory[STACK_START + ++cpu.SP]; 	
		result |= memory[STACK_START + ++cpu.SP] << 8;
	}
	return result;
}

void print_stack(){
	for(int i = 0xff; i > cpu.PC ; i--){
		printf("|"BYTE_TO_BINARY_PATTERN"|\n", BYTE_TO_BINARY(memory[STACK_START + i]));
	}
	printf("----------\n");
	printf("- STACK  -\n");
	printf("----------\n");
}

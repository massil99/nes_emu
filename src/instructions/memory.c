#include "memory.h"
#include "custom_types.h"
#include <stdio.h>

u8 memory[MEMORY_SIZE] = {0};


void dump_memory(u16 start){
	printf("memeory starts here \n");
	for(int i = start; i < MEMORY_SIZE; i++){
		if(i % 4 == 0)
			printf(" ");	
		if(i % 16 == 0)
			printf("\n%04x: ",i);
		printf("%02x", memory[i]);
	} 
	printf("\nmemeory ends here \n");
}

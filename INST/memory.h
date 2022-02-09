#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 65536 

#define STACK_START 0x01a0
#define STACK_END 0x01ff
#include "custom_types.h"

void dump_memory(u16 start);
#endif //MEMORY_H

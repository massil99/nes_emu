#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include "custom_types.h"

#define STACK_SIZE 96 

void push(u8 byte);
void push_word(u16 word);
u8 pull();
u16 pull_word();
void print_stack(); 

#endif //STACK_H_

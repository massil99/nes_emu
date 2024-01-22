#ifndef PSW_H_
#define PSW_H_

#include "cpu.h"
#include "stack.h"

size_t PHA();
size_t PLA();
size_t PHP();
size_t PLP();
size_t SEC();
size_t SED();
size_t SEI();
size_t SEV();
size_t CLC();
size_t CLD();
size_t CLI();
size_t CLV();

#endif //PSW_H_

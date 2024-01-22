#ifndef BRANCHING_H_
#define BRANCHING_H_

#include "custom_types.h"
#include <stdbool.h>

size_t BCC(s8 offset);
size_t BCS(s8 offset);
size_t BEQ(s8 offset);
size_t BNE(s8 offset);
size_t BMI(s8 offset);
size_t BPL(s8 offset);
size_t BVC(s8 offset);
size_t BVS(s8 offset);
size_t JMP(u16 m);
#define JMP_Absolute(addr) JMP(addr)
size_t JMP_Indirect(u16 addr);
size_t JSR(u16 addr);

#endif //BRANCHING_H_

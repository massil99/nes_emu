#ifndef BRANCHING_H_
#define BRANCHING_H_

#include "custom_types.h"
#include <stdbool.h>

bool BCC(s8 offset);
bool BCS(s8 offset);
bool BEQ(s8 offset);
bool BNE(s8 offset);
bool BMI(s8 offset);
bool BPL(s8 offset);
bool BVC(s8 offset);
bool BVS(s8 offset);
void JMP(u16 m);
#define JMP_Absolute(addr) JMP(addr)
void JMP_Indirect(u16 addr);
void JSR(u16 addr);

#endif //BRANCHING_H_

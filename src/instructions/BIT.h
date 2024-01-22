#ifndef BIT_H_
#define BIT_H_

#include "custom_types.h"

void BIT(u8 m);
size_t BIT_ZeroPage(u8 addr);
size_t BIT_Absolute(u16 addr);
#endif //BIT_H_

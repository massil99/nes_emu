#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>
#include "../instructions/custom_types.h" 

bool page_crossed(u16 addr, u16 newaddr);

#endif //_UTILS_H_

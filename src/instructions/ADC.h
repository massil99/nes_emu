#ifndef ADC_H_
#define ADC_H_

#include "custom_types.h"

size_t ADC(u8 m);
#define ADC_Immediate(mem) ADC(mem) 
size_t ADC_ZeroPage(u8 addr);
size_t ADC_ZeroPageX(u8 addr);
size_t ADC_Absolute(u16 addr);
size_t ADC_AbsoluteX(u16 addr);
size_t ADC_AbsoluteY(u16 addr);
size_t ADC_IndirectX(u8 addr);
size_t ADC_IndirectY(u8 addr);

#endif //ADC_H_

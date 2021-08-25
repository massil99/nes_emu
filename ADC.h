#ifndef ADC_H_
#define ADC_H_

#include "custom_types.h"

void ADC(u8 m);
#define ADC_Immediate(mem) ADC(mem) 
void ADC_ZeroPage(u8 addr);
void ADC_ZeroPageX(u8 addr);
void ADC_Absolute(u16 addr);
void ADC_AbsoluteX(u16 addr);
void ADC_AbsoluteY(u16 addr);
void ADC_IndirectX(u8 addr);
void ADC_IndirectY(u8 addr);

#endif //ADC_H_

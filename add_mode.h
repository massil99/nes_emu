#ifndef ADD_MODE_H_
#define ADD_MODE_H_

#include "cpu.h"
#include "custom_types.h"
#include "memory.h"
	
u8 get_zero_page(u8 addr);
void set_zero_page(u8 addr, u8 val);
u8 get_zero_page_y(u8 addr);
void set_zero_page_y(u8 addr, u8 val);
u8 get_zero_page_x(u8 addr);
void set_zero_page_x(u8 addr, u8 val);
u8 get_absolute_x(u16 addr);
void set_absolute_x(u16 addr, u8 val);
u8 get_absolute_y(u16 addr);
void set_absolute_y(u16 addr, u8 val);
u8 get_indirect(u16 addr);
u8 get_indirect_x(u16 addr);
void set_indirect_x(u16 addr, u8 val);
u8 get_indirect_y(u16 addr);
void set_indirect_y(u16 addr, u8 val);

#endif // ADD_MODE_H_

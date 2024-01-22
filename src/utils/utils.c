
#include "utils.h"

bool page_crossed(u16 addr, u16 newaddr){
	int p1 = addr % 0x00ff;
	int p2 = newaddr % 0x00ff;

	return p1 != p2;
}

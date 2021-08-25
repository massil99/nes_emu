#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#include <stdio.h>

#define BYTE_TO_BINARY(byte) \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

#define PRINT_BYTE(byte) \
	printf(BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(byte))
#define WORD_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN

#define WORD_TO_BINARY(word)  \
	BYTE_TO_BINARY(word>>8),\
	BYTE_TO_BINARY(word)
#define PRINT_WORD(word) \
	printf(WORD_TO_BINARY_PATTERN"\n", WORD_TO_BINARY(word))

#define U8_BIT0(u) ((uint8_t) (0x01 & u)) 
#define U8_BIT1(u) ((uint8_t) ((0x02 & u) >> 1))
#define U8_BIT2(u) ((uint8_t) ((0x04 & u) >> 2))
#define U8_BIT3(u) ((uint8_t) ((0x08 & u) >> 3))
#define U8_BIT4(u) ((uint8_t) ((0x10 & u) >> 4))
#define U8_BIT5(u) ((uint8_t) ((0x20 & u) >> 5))
#define U8_BIT6(u) ((uint8_t) ((0x40 & u) >> 6))
#define U8_BIT7(u) ((uint8_t) ((0x80 & u) >> 7))

#endif //BIT_MANIPULATION_H_

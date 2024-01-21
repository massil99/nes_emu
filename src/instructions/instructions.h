#ifndef INSTRUCTIONS_H_H
#define INSTRUCTIONS_H_H

#include "ADC.h"
#include "AND.h"
#include "ASL.h"
#include "BIT.h"
#include "BRANCHING.h"
#include "COMPARE.h"
#include "cpu.h"
#include "EOR.h"
#include "INCDEC.h"
#include "LSR.h"
#include "ORA.h"
#include "PSW.h"
#include "ROL.h"
#include "ROR.h"
#include "SBC.h"
#include "stack.h"
#include "subroutine_call.h"
#include "unofficial.h"

#define OPC_ADCI    0x69
#define OPC_ADCZP   0x65
#define OPC_ADCZPX  0x75
#define OPC_ADCA    0x6d
#define OPC_ADCAX   0x7d
#define OPC_ADCAY   0x79
#define OPC_ADCINDX 0x61
#define OPC_ADCINDY 0x71

#define OPC_ANDI    0x29
#define OPC_ANDZP   0x25
#define OPC_ANDZPX  0x35
#define OPC_ANDA    0x2d
#define OPC_ANDAX   0x3d
#define OPC_ANDAY   0x39
#define OPC_ANDINDX 0x21
#define OPC_ANDINDY 0x31

#define OPC_ASLACC 0x0a
#define OPC_ASLZP  0x06
#define OPC_ASLZPX 0x16
#define OPC_ASLA   0x0e
#define OPC_ASLAX  0x1e

#define OPC_BCCR 0x90
#define OPC_BCSR 0xb0
#define OPC_BEQR 0xF0
#define OPC_BVCR 0x50
#define OPC_BVSR 0x70

#define OPC_BITZP 0x24
#define OPC_BITA  0x2c

#define OPC_BMIR   0x30
#define OPC_BNER   0xd0
#define OPC_BPLR   0x10
#define OPC_BRKIMP 0x00

#define OPC_CLCIMP 0x18
#define OPC_CLDIMP 0xd8
#define OPC_CLIIMP 0x58
#define OPC_CLVIMP 0xb8

#define OPC_CMPI    0xc9
#define OPC_CMPZP   0xc5
#define OPC_CMPZPX  0xd5
#define OPC_CMPA    0xcd
#define OPC_CMPAX   0xdd
#define OPC_CMPAY   0xd9
#define OPC_CMPINDX 0xc1
#define OPC_CMPINDY 0xd1

#define OPC_CPXI  0xE0
#define OPC_CPXZP 0xe4
#define OPC_CPXA  0xec
              
#define OPC_CPYI  0xc0
#define OPC_CPYZP 0xc4
#define OPC_CPYA  0xcc

#define OPC_DECZP  0xc6
#define OPC_DECZPX 0xd6
#define OPC_DECA   0xce
#define OPC_DECAX  0xde

#define OPC_DEXIMP 0xca 
#define OPC_DEYIMP 0x88

#define OPC_EORI    0x49
#define OPC_EORZP   0x45
#define OPC_EORZPX  0x55
#define OPC_EORA    0x4d
#define OPC_EORAX   0x5d
#define OPC_EORAY   0x59
#define OPC_EORINDX 0x41
#define OPC_EORINDY 0x51

#define OPC_INCZP  0xe6
#define OPC_INCZPX 0xf6
#define OPC_INCA   0xee
#define OPC_INCAX  0xfe

#define OPC_INXIMP 0xe8
#define OPC_INYIMP 0xc8

#define OPC_JMPA   0x4c
#define OPC_JMPIND 0x6c
#define OPC_JSRA   0x20

#define OPC_LDAI    0xa9
#define OPC_LDAZP   0xa5
#define OPC_LDAZPX  0xb5
#define OPC_LDAA    0xad
#define OPC_LDAAX   0xbd
#define OPC_LDAAY   0xb9
#define OPC_LDAINDX 0xa1
#define OPC_LDAINDY 0xb1

#define OPC_LDXI   0xa2
#define OPC_LDXZP  0xa6
#define OPC_LDXZPY 0xb6
#define OPC_LDXA   0xae
#define OPC_LDXAY  0xbe

#define OPC_LDYI   0xa0
#define OPC_LDYZP  0xa4
#define OPC_LDYZPX 0xb4
#define OPC_LDYA   0xac
#define OPC_LDYAX  0xbc

#define OPC_LSRACC 0x4a
#define OPC_LSRZP  0x46
#define OPC_LSRZPX 0x56
#define OPC_LSRA   0x4e
#define OPC_LSRAX  0x5e

#define OPC_NOP      0xea

#define OPC_ORAI    0x09
#define OPC_ORAZP   0x05
#define OPC_ORAZPX  0x15
#define OPC_ORAA    0x0d
#define OPC_ORAAX   0x1d
#define OPC_ORAAY   0x19
#define OPC_ORAINDX 0x01
#define OPC_ORAINDY 0x11

#define OPC_PHAIMP 0x48

#define OPC_PHPIMP 0x08

#define OPC_PLAIMP 0x68

#define OPC_PLPIMP 0x28

#define OPC_ROLACC 0x2a
#define OPC_ROLZP  0x26
#define OPC_ROLZPX 0x36
#define OPC_ROLA   0x2e
#define OPC_ROLAX  0x3e

#define OPC_RORACC 0x6a
#define OPC_RORZP  0x66
#define OPC_RORZPX 0x76
#define OPC_RORA   0x6e
#define OPC_RORAX  0x7e

#define OPC_RTIIMP 0x40
#define OPC_RTSIMP 0x60

#define OPC_SBCI    0xe9
#define OPC_SBCI_U  0xeB
#define OPC_SBCZP   0xe5
#define OPC_SBCZPX  0xf5
#define OPC_SBCA    0xed
#define OPC_SBCAX   0xfd
#define OPC_SBCAY   0xf9
#define OPC_SBCINDX 0xe1
#define OPC_SBCINDY 0xf1

#define OPC_SECIMP 0x38

#define OPC_SEDIMP 0xf8

#define OPC_SEIIMP 0x78

#define OPC_STAZP   0x85
#define OPC_STAZPX  0x95
#define OPC_STAA    0x8d
#define OPC_STAAX   0x9d
#define OPC_STAAY   0x99
#define OPC_STAINDX 0x81
#define OPC_STAINDY 0x91

#define OPC_STXZP  0x86
#define OPC_STXZPY 0x96
#define OPC_STXA   0x8e

#define OPC_STYZP  0x84
#define OPC_STYZPX 0x94
#define OPC_STYA   0x8c

#define OPC_TAXIMP 0xaa

#define OPC_TAYIMP 0xa8

#define OPC_TSXIMP 0xba

#define OPC_TXAIMP 0x8a

#define OPC_TXSIMP 0x9a

#define OPC_TYAIMP 0x98

/********************* UNOFFICIAL INSTS *****************/
#define OPC_ALR 0x4b
#define OPC_ANC 0x0b
#define OPC_ARR 0X6B
#define OPC_AXS 0xcb

#define OPC_LAXa    0xaf
#define OPC_LAXay   0xbf
#define OPC_LAXzp   0xa7
#define OPC_LAXzpy  0xb7
#define OPC_LAXINDX 0xa3
#define OPC_LAXINDY 0xb3

#define OPC_SAXa    0x8f
#define OPC_SAXzp   0x87
#define OPC_SAXzpy  0x97
#define OPC_SAXINDX 0x83

#define OPC_DCPa    0xcf
#define OPC_DCPax   0xdf
#define OPC_DCPay   0xdb
#define OPC_DCPzp   0xc7
#define OPC_DCPzpx  0xd7
#define OPC_DCPINDX 0xc3
#define OPC_DCPINDY 0xd3

#define OPC_ISCa    0xef
#define OPC_ISCax   0xff
#define OPC_ISCay   0xfb
#define OPC_ISCzp   0xe7
#define OPC_ISCzpx  0xf7
#define OPC_ISCINDX 0xe3
#define OPC_ISCINDY 0xf3

#define OPC_RLAa    0x2f
#define OPC_RLAax   0x3f
#define OPC_RLAay   0x3b
#define OPC_RLAzp   0x27
#define OPC_RLAzpx  0x37
#define OPC_RLAINDX 0x23
#define OPC_RLAINDY 0x33

#define OPC_RRAa    0x6f
#define OPC_RRAax   0x7f
#define OPC_RRAay   0x7b
#define OPC_RRAzp   0x67
#define OPC_RRAzpx  0x77
#define OPC_RRAINDX 0x63
#define OPC_RRAINDY 0x73

#define OPC_SLOa    0x0f
#define OPC_SLOax   0x1f
#define OPC_SLOay   0x1b
#define OPC_SLOzp   0x07
#define OPC_SLOzpx  0x17
#define OPC_SLOINDX 0x03
#define OPC_SLOINDY 0x13

#define OPC_SREa    0x4f
#define OPC_SREax   0x5f
#define OPC_SREay   0x5b
#define OPC_SREzp   0x47
#define OPC_SREzpx  0x57
#define OPC_SREINDX 0x43
#define OPC_SREINDY 0x53


#define OPC_NOP_DUP1 0x1a
#define OPC_NOP_DUP2 0x3a
#define OPC_NOP_DUP3 0x5a
#define OPC_NOP_DUP4 0x7a
#define OPC_NOP_DUP5 0xfa

#define OPC_SKB   0x80
#define OPC_SKB1  0x82
#define OPC_SKB2  0xC2
#define OPC_SKB3  0xE2
#define OPC_SKB4  0x04
#define OPC_SKB5  0x14
#define OPC_SKB6  0x34
#define OPC_SKB7  0x44
#define OPC_SKB8  0x54
#define OPC_SKB9  0x64
#define OPC_SKB10 0x74
#define OPC_SKB11 0xD4
#define OPC_SKB12 0xF4

#define OPC_ING  0x0C
#define OPC_ING1 0x1C
#define OPC_ING2 0x3C
#define OPC_ING3 0x5C
#define OPC_ING4 0x7C 
#define OPC_ING5 0xDC 
#define OPC_ING6 0xFC
#endif //INSTRUCTIONS_H_H

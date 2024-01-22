CC=gcc
FLAGS=-g
SRC=src/cpu/*.c src/instructions/*.c src/utils/*.c
OUTPUT=./output
EXEC=emu

all:
	${CC} -o${OUTPUT}/${EXEC} ${SRC} ${FLAGS}
	

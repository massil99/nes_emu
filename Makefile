run: test
	./test

test: 
	gcc -o test *.c

clean: 
	rm test 
	rm *.o

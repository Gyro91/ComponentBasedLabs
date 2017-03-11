CFLAGS=-Wall 
LIB=-lm

all: hello
	 
hello: hellounit.o hellomain.o 
	gcc -o $@ $^ $(LIB)

hellounit.o: hellounit.c
	gcc $(CFLAGS) -c $^ -o $@

hellomain.o: hellomain.c
	gcc $(CFLAGS) -c $^ -o $@
	
clean:
	rm *.o hello




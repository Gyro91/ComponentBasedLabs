CFLAGS=-Wall 
LIB=-lhellounit -lm

ifdef DEBUG
CFLAGS += -g
else
CFLAGS += -O3
endif

.PHONY:
all: hello

hello: hellounit.so hellomain.o module2.o
	gcc -o $@ hellomain.o module2.o -L. $(LIB) 

hellounit.so: hellounit.c
	gcc -o libhellounit.so -fPIC -shared $^

hellomain.o: hellomain.c
	gcc $(CFLAGS) -c $^ -o $@

module2.o: module2.c
	gcc $(CFLAGS) -c $^ -o $@

.PHONY:
clean:
	rm -f *.o hello *.so




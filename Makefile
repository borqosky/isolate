PROG=isolate
CFLAGS=-I

compile: %.o: %.c
	gcc -c -o $@ $<

all: $(PROG).o
	gcc -o $(PROG) $(PROG).o

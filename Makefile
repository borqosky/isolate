PROG=isolate
CFLAGS=-I
DIRS=bin

$(shell mkdir -p $(DIRS))

%.o: %.c
	gcc -c -o bin/$@ $<

compile: $(PROG).o
	gcc -o bin/$(PROG) bin/$(PROG).o

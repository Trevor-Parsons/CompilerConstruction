CC=g++
CFLAGS=-I.
DEPS = token.h testScanner.h scanner.h
OBJ = main.o testScanner.o scanner.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

P1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o P1

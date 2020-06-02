CC=g++
CFLAGS=-I.
DEPS = token.h scanner.h parser.h testTree.h
OBJ = main.o scanner.o parser.o testTree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

statSem: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o statSem

CC=g++
CFLAGS=-I. -std=c++11
DEPS = token.h scanner.h parser.h testTree.h
OBJ = main.o scanner.o parser.o testTree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

frontEnd: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o frontEnd

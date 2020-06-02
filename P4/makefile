CC=g++
CFLAGS=-I.
DEPS = token.h scanner.h parser.h testTree.h codeGenerator.h
OBJ = main.o scanner.o parser.o testTree.o codeGenerator.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compile: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o compile *.txt *.asm

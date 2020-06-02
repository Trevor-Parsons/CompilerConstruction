CC=g++
CFLAGS=-I.
DEPS = node.h buildTree.h traversals.h
OBJ = main.o buildTree.o traversals.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

P0: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *.inorder *.postorder *.levelorder P0

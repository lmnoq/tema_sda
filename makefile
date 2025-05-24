CC=gcc
CFLAGS=-Wall -Wextra -g

OBJS=tema2.o tree.o heap.o huffman.o

tema2: $(OBJS)
	$(CC) -o tema2 $(OBJS)

clean:
	rm -f tema2 *.o

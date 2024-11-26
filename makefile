CFLAGS = -Wall -g
LDFLAGS = -lm

CC = gcc

objects = myavl.o arvoreAVL.o
     
all: myavl 

myavl: $(objects)
	$(CC) $^ -o $@ $(LDFLAGS)

myavl.o: myavl.c arvoreAVL.h
	$(CC) -c $< $(CFLAGS)

arvoreAVL.o: arvoreAVL.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(objects)

purge:
	rm -f $(objects) myavl
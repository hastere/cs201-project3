OBJS = prim.o scanner.o node.o vertex.o dll.o binheap.o
OPTS = -Wall -g -std=c99

trees : $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim -lm

prim.o : prim.c scanner.h binheap.h vertex.h node.h
	gcc $(OPTS) -c prim.c

scanner.o : scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

node.o : node.c node.h dll.h vertex.h
	gcc $(OPTS) -c node.c

vertex.o : vertex.c vertex.h node.h
	gcc $(OPTS) -c vertex.c

dll.o : dll.c dll.h node.h
	gcc $(OPTS) -c dll.c

binheap.o : binheap.c binheap.h dll.h node.h
	gcc $(OPTS) -c binheap.c

test :
	prim g1

clean :
	rm -f $(OPJS) prim

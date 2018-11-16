CC=gcc
FLAGS=-g -O3 -Wall
OBJS=m.o str.o list.o element.o
TESTS=list.test.o element.test.o

vespa: $(OBJS)
	$(CC) main.c $(OBJS) $(FLAGS) -o vespa

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

test: $(OBJS) $(TESTS)
	$(CC) list.test.o $(OBJS) -o test.list
	./test.list && echo "List Passed" || echo "List Failed";
	$(CC) element.test.o $(OBJS) -o test.element
	./test.element && echo "Elemente Passed" || echo "Element Failed";

clear:
	rm *.o
	rm test.*

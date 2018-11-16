CC=gcc
FLAGS=-g -O3 -Wall
OBJS=m.o str.o list.o element.o place.o out.o object.o bool.o
TESTS=list.test.o element.test.o place.test.o out.test.o object.test.o

vespa: $(OBJS)
	$(CC) main.c $(OBJS) $(FLAGS) -o vespa

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

test: $(OBJS) $(TESTS)
	$(CC) list.test.o $(OBJS) -o test.list
	./test.list && echo "List Passed" || echo "List Failed";
	$(CC) element.test.o $(OBJS) -o test.element
	./test.element && echo "Elemente Passed" || echo "Element Failed";
	$(CC) place.test.o $(OBJS) -o test.place
	./test.place && echo "Place Passed" || echo "Place Failed";
	$(CC) out.test.o $(OBJS) -o test.out
	./test.out && echo "Out Passed" || echo "Out Failed";
	$(CC) object.test.o $(OBJS) -o test.object
	./test.object && echo "Object Passed" || echo "Object Failed";

clear:
	rm *.o
	rm test.*

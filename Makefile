CC=gcc
FLAGS=-g -O3 -Wall
OBJS=m.o str.o list.o

vespa: $(OBJS)
	$(CC) main.c $(OBJS) $(FLAGS) -o vespa

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)
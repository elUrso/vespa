LOADLIBES= -lfl -lreadline
CFLAGS=-Wall -g

%.c: %.y
	bison $<
	mv $*.tab.c $*.c

avent: main.o avent.o aventl.o coisas.o symrec.o

avent.c : avent.y

aventl.o: aventl.l avent.c

clean:
	rm -f avent *tab* *.o *~ avent.c avent.tgz
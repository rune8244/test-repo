#Makefile

CC=gcc
CFLAGS=
OBJS=testsh.o handleCmd.o historytest.o
LIBS=
all :	testSH

testSH:	$(OBJS)
	$(CC) $(CFLAGS) -o testSH $(OBJS) $(LIBS)

testsh.o:	testsh.c
	$(CC) $(CFLAGS) -c testsh.c

handleCmd.o:	handleCmd.c
	$(CC) $(CFLAGS) -c handleCmd.c

historytest.o:	historytest.c
	$(CC) $(CFLAGS) -c historytest.c

clean:
	rm -f $(OBJS) testSH core

# sm_list project
CC:=gcc
AR:=ar
CFLAGS:=-O2 -Wall
all: main.o smlist.o
	$(CC) -o smlist.exe main.o smlist.o
lib-static: smlist.o
	$(AR) cr libsmlist.a smlist.o
lib-dynamic: smlist.o
	$(CC) -shared -o smlist.so smlist.o
main.o: main.c
	$(CC) -c $(CFLAGS) main.c
smlist.o: smlist.c
	$(CC) -c $(CFLAGS) smlist.c
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.a
	rm -f *.so
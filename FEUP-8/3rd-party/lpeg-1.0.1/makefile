LIBNAME = lpeg

COPT = -O2
# COPT = -DLPEG_DEBUG -g

CFLAGS = $(COPT) -std=c99 -I../lua-5.3.1/src
CC = gcc

FILES = lpvm.o lpcap.o lptree.o lpcode.o lpprint.o

all: liblpeg.a	

liblpeg.a: $(FILES)
	ar rcu $@ $(FILES)
	ranlib $@

lpcap.o: lpcap.c lpcap.h lptypes.h
	$(CC) -c lpcap.c $(CFLAGS) -o $@

lpcode.o: lpcode.c lptypes.h lpcode.h lptree.h lpvm.h lpcap.h
	$(CC) -c lpcode.c $(CFLAGS) -o $@

lpprint.o: lpprint.c lptypes.h lpprint.h lptree.h lpvm.h lpcap.h
	$(CC) -c lpprint.c $(CFLAGS) -o $@

lptree.o: lptree.c lptypes.h lpcap.h lpcode.h lptree.h lpvm.h lpprint.h
	$(CC) -c lptree.c $(CFLAGS) -o $@

lpvm.o: lpvm.c lpcap.h lptypes.h lpvm.h lpprint.h lptree.h
	$(CC) -c lpvm.c $(CFLAGS) -o $@

COPT = -O3

CFLAGS = $(COPT)
CC = gcc

FILES = \
	egif_lib.o \
	dgif_lib.o \
	gifalloc.o \
	gif_font.o \
	gif_hash.o \
	gif_err.o \
	quantize.o \
	openbsd-reallocarray.o

all: libgif.a

libgif.a: $(FILES)
	ar rcu $@ $(FILES)
	ranlib $@

egif_lib.o: ../egif_lib.c
	$(CC) -c ../egif_lib.c $(CFLAGS) -o $@

dgif_lib.o: ../dgif_lib.c
	$(CC) -c ../dgif_lib.c $(CFLAGS) -o $@

gif_hash.o: ../gif_hash.c
	$(CC) -c ../gif_hash.c $(CFLAGS) -o $@

gif_err.o: ../gif_err.c
	$(CC) -c ../gif_err.c $(CFLAGS) -o $@

gifalloc.o: ../gifalloc.c
	$(CC) -c ../gifalloc.c $(CFLAGS) -o $@

gif_font.o: ../gif_font.c
	$(CC) -c ../gif_font.c $(CFLAGS) -o $@

quantize.o: ../quantize.c
	$(CC) -c ../quantize.c $(CFLAGS) -o $@

openbsd-reallocarray.o: ../openbsd-reallocarray.c
	$(CC) -c ../openbsd-reallocarray.c $(CFLAGS) -o $@

CFLAGS = -DWREN_OPT_META -DWREN_OPT_RANDOM -I../src/include -I../src/optional -I../src/vm
SRC_VM = ../src/vm
SRC_OPT = ../src/optional
CC = emcc

FILES = \
	wren_compiler.o \
	wren_core.o \
	wren_debug.o \
	wren_primitive.o \
	wren_utils.o \
	wren_value.o \
	wren_vm.o \
	wren_opt_meta.o \
	wren_opt_random.o

all: libwren.a

libwren.a: $(FILES)
	emar rcu $@ $(FILES)
	emranlib $@

wren_compiler.o: $(SRC_VM)/wren_compiler.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_core.o: $(SRC_VM)/wren_core.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_debug.o: $(SRC_VM)/wren_debug.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_primitive.o: $(SRC_VM)/wren_primitive.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_utils.o: $(SRC_VM)/wren_utils.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_value.o: $(SRC_VM)/wren_value.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_vm.o: $(SRC_VM)/wren_vm.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_opt_meta.o: $(SRC_OPT)/wren_opt_meta.c
	$(CC) -c $< $(CFLAGS) -o $@

wren_opt_random.o: $(SRC_OPT)/wren_opt_random.c
	$(CC) -c $< $(CFLAGS) -o $@


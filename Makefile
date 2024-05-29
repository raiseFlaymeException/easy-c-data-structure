CC = gcc
CXX = g++
DEBUG = gdb

STANDARD = -std=c11

OPTI = -O3

WARNINGS = -Wall -Wextra -Wpedantic -Werror

HEADERDIR = src/include
LIBDIR = src/lib

LIBC_CPP = -static-libstdc++ -static-libgcc
HIDEWINDOW = -mwindows

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

HEADERS = $(call rwildcard,src/include,*.h)
EXTERNAL_HEADERS = $(call rwildcard,src/include/external,*.h)
INTERNAL_HEADERS = $(filter-out $(EXTERNAL_HEADERS),$(HEADERS))
SOURCES = $(call rwildcard,src/c,*.c)
COMPILED = $(subst .c,.o,$(SOURCES)) 

QUIET = > nul 2>&1

LIB =

all: bin/example_array.exe bin/example_string.exe bin/example_hashmap.exe

bin/%.exe: %.c $(COMPILED)
	$(CC) $< $(COMPILED) -o $@ $(LIB) -I $(HEADERDIR) -L $(LIBDIR) $(WARNING) $(STANDARD)

bin/example_array_debug.exe: example_array.c $(SOURCES)
	$(CC) -ggdb3 $< $(COMPILED) -o $@ $(LIB) -I $(HEADERDIR) -L $(LIBDIR) $(WARNING) $(STANDARD)

bin/example_string_debug.exe: example_string.c $(SOURCES)
	$(CC) -ggdb3 $< $(COMPILED) -o $@ $(LIB) -I $(HEADERDIR) -L $(LIBDIR) $(WARNING) $(STANDARD)

bin/example_hashmap_debug.exe: example_hashmap.c $(SOURCES)
	$(CC) -ggdb3 $< $(COMPILED) -o $@ $(LIB) -I $(HEADERDIR) -L $(LIBDIR) $(WARNING) $(STANDARD)

bin/example_arena_debug.exe: example_arenea.c $(SOURCES)
	$(CC) -ggdb3 $< $(COMPILED) -o $@ $(LIB) -I $(HEADERDIR) -L $(LIBDIR) $(WARNING) $(STANDARD)

bin/example_queue_debug.exe: example_queue.c $(SOURCES)
	$(CC) -ggdb3 $< $(COMPILED) -o $@ $(LIB) -I $(HEADERDIR) -L $(LIBDIR) $(WARNING) $(STANDARD)

run_example_array: bin/example_array.exe
	./$<

run_example_string: bin/example_string.exe
	./$<

run_example_hashmap: bin/example_hashmap.exe
	./$<

run_example_arena: bin/example_arena.exe
	./$<

run_example_queue: bin/example_queue.exe
	./$<

src/c/%.o: src/c/%.c
	$(CC) -c $< -o $@ -I $(HEADERDIR) $(WARNINGS) $(STANDARD) $(OPTI)

.PHONY: clean
.SILENT: clean
clean:
	-del main.o $(QUIET)
	-del /S src\c\*.o $(QUIET)

.PHONY: cleanmore
.SILENT: cleanmore
cleanmore: clean
	-del bin\*.exe $(QUIET)

	-del bin\main.ipp $(QUIET)

CFLAGS=-Wall -g -DNDEBUG

# compile lib files then create the executable
all: lib_compile
	clang ex29.c -ldl -o ex29

# compile lib files
lib_compile:
	clang -c libex29.c -o libex29.o
	clang -shared -o libex29.so libex29.o

# clean up
clean:
	rm -rf *.dSYM
	rm -f libex29.o
	rm -f libex29.so
	rm -f ex29

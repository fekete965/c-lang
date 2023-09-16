CFLAGS=-Wall -g

all:
	clang -c ex22.c -o ex22.o
	clang ex22.c ex22_main.c -o ex22_main

prod:
	clang -DNDEBUG -c ex22.c -o ex22.o
	clang -DNDEBUG ex22.o ex22_main.c -o ex22_main

clean:
	rm -rf *.dSYM
	rm -f ex22_main
	rm -f ex22.o

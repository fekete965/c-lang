CFLAGS=-Wall -g

all:
	clang -c ex22_extra.c -o ex22_extra.o
	clang ex22_extra.o ex22_main_extra.c -o ex22_main_extra

prod:
	clang -DNDEBUG -c -c ex22_extra.c -o ex22_extra.o
	clang -DNDEBUG ex22_extra.o ex22_main_extra.c -o ex22_main_extra

clean:
	rm -rf *.dSYM
	rm -f ex22_main_extra
	rm -f ex22_extra.o

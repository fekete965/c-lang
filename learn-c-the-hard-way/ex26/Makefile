CFLAGS=-Wall -g

debug: logfind

prod:
	clang -DNDEBUG logfind.c -o logfind

clean:
	rm -rf *.dSYM
	rm -f logfind

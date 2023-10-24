CFLAGS=-Wall -g

debug: logfind_using_glob

prod:
	clang -DNDEBUG logfind_using_glob.c -o logfind_using_glob

clean:
	rm -rf *.dSYM
	rm -f logfind_using_glob

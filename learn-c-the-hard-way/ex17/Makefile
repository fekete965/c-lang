CFLAGS=-Wall -g

all: ex17 ex17_extra ex17_extra_stack ex17_extra_with_global_conn

clean:
	rm -rf *.dSYM
	rm -f db.dat
	rm -f ex17
	rm -f ex17_extra
	rm -f ex17_extra_stack
	rm -f ex17_extra_with_global_conn

test: clean
	./ex17_extra.sh

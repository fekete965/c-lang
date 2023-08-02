CFLAGS=-Wall -g

# To run this in the terminal, we need to use:
# make -f ex2.1.mak clean 
# This is because the file isn't named as "make"
clean:
	rm -f ex1
	rm -f ex3
	rm -f ex7
	rm -f ex8
	rm -f ex9

all:
	make ex1
	make ex3
	make ex7
	make ex8
	make ex9

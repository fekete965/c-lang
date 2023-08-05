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
	rm -f ex10
	rm -f ex10_extra
	rm -f ex11
	rm -f ex11_extra
	rm -f ex12
	rm -f ex12_extra
	rm -f ex13
	rm -f ex13_extra
	rm -f ex14
	rm -f ex14_extra

# To run this in the terminal, we need to use:
# make -f ex2.1.mak all 
# This is because the file isn't named as "make"
all:
	make ex1
	make ex3
	make ex7
	make ex8
	make ex9
	make ex10
	make ex10_extra
	make ex11
	make ex11_extra
	make ex12
	make ex12_extra
	make ex13
	make ex13_extra
	make ex14
	make ex14_extra

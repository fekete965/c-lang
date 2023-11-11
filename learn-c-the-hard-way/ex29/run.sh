# clean up
rm -rf *.dSYM
rm -f libex29.o
rm -f libex29.so
rm -f ex29

# compile the lib file and make the .so
# you may need -fPIC here on some platforms. add that if you get an error
clang -c libex29.c -o libex29.o
clang -shared -o libex29.so libex29.o

# make the loader program
clang -Wall -g -DNDEBUG ex29.c -ldl -o ex29

# try it out with some things that work
echo 'EXECUTING: ./ex29 ./libex29.so print_a_message "hello there"'
./ex29 ./libex29.so print_a_message "hello there"
echo

echo 'EXECUTING: ./ex29 ./libex29.so uppercase "hello there"'
./ex29 ./libex29.so uppercase "hello there"
echo

echo 'EXECUTING: ./ex29 ./libex29.so lowercase "HELLO THERE"'
./ex29 ./libex29.so lowercase "HELLO THERE"
echo

echo 'EXECUTING: ./ex29 ./libex29.so fail_on_purpose "I fail"'
./ex29 ./libex29.so fail_on_purpose "I fail"
echo

# try to give it bad args
echo 'EXECUTING: ./ex29 ./libex29.so fail_on_purpose'
./ex29 ./libex29.so fail_on_purpose
echo

# try calling a function that is not there
echo './ex29 ./libex29.so asasdasd asdasd'
./ex29 ./libex29.so asasdasd asdasd
echo

# try loaading a .so that is not there
echo './ex29 ./libx.so dsadas dsadas'
./ex29 ./libx.so dsadas dsadas
echo

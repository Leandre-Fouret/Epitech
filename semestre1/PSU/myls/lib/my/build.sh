#/bin/bash

# Create object files
gcc -c *.c

# Create the lib
ar rc libmy.a *.o

# Delete object files
rm *.o

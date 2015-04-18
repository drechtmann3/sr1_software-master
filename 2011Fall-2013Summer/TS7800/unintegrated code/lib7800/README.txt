This is a statically linked library of utilities for the TS-7800 SBC.
The makefile compiles all files into the library archive
7800lib.a, which can be linked like this:
gcc -o main main.c 7800lib.a -I../lib
...where main.c is a source file in a program using the library. The
headers containing library functions used by the program must be #included.
The flag -I../lib tells the compiler to look in the folder ../lib for
header files; thus a file can include the desired library header with
#include "libHeader.h"
...even though the header isn't in the same directory.

The library is statically linked, which means that if the library is
recompiled then any programs using it must also be recompiled to reflect
the changes.

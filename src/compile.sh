#!/bin/sh
echo "compiling"

gcc NeticaEx.c -c -I. -L../bin 
cp -f NeticaEx.o ../lib
rm ./NeticaEx.o

gcc ../lib/NeticaEx.o Main.cpp -o Main.a -I. -L../lib/64bit -lrt -lnetica -lpthread -lstdc++ -lm

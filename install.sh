#!/bin/bash

clang -Wall tictactoe.c tictactoe.h -c

clang -Wall tictactoe.o -o tictactoe

sudo mv tictactoe /usr/bin/tictactoe

rm tictactoe.o tictactoe.h.gch


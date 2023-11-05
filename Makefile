CC=clang -Wall

all: tictactoe test

######################################################################
#                       Règles de compilation                        #
######################################################################

%.o: %.c
	$(CC) -c $<

tictactoe.o: tictactoe.c tictactoe.h

######################################################################
#                       Règles d'édition de liens                    #
######################################################################

tictactoe: tictactoe.o
	$(CC) $^ -o $@

clean:
	rm -f tictactoe *.o

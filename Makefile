CC=g++ -g
COPTIONS=`pkg-config --cflags --libs gtk+-3.0`
C_DIR=tictactoe_c
CPP_DIR=tictactoe_c++

all: tictactoe tictactoe.o tictactoec.o tictactoe+.o window.o grid.o gridUI.o button.o case.o

######################################################################
#                       Règles de compilation                        #
######################################################################

tictactoe.o: tictactoe.cpp $(C_DIR)/tictactoec.h $(CPP_DIR)/tictactoe+.h
	$(CC) $(COPTIONS) -c $<

tictactoec.o: $(C_DIR)/tictactoec.c $(C_DIR)/tictactoec.h
	$(CC) -c $<

case.o: $(CPP_DIR)/case.cpp $(CPP_DIR)/case.h
	$(CC) $(COPTIONS) -c $<

button.o: $(CPP_DIR)/button.cpp $(CPP_DIR)/button.h
	$(CC) $(COPTIONS) -c $<

gridUI.o: $(CPP_DIR)/gridUI.cpp $(CPP_DIR)/gridUI.h $(CPP_DIR)/grid.h $(CPP_DIR)/case.h $(CPP_DIR)/tictactoe+.h
	$(CC) $(COPTIONS) -c $<

grid.o: $(CPP_DIR)/grid.cpp $(CPP_DIR)/grid.h $(CPP_DIR)/case.h
	$(CC) $(COPTIONS) -c $<

window.o: $(CPP_DIR)/window.cpp $(CPP_DIR)/window.h
	$(CC) $(COPTIONS) -c $<

tictactoe+.o: $(CPP_DIR)/tictactoe+.cpp $(CPP_DIR)/tictactoe+.h $(CPP_DIR)/grid.h $(CPP_DIR)/case.h $(CPP_DIR)/window.h $(CPP_DIR)/button.h $(CPP_DIR)/gridUI.h
	$(CC) $(COPTIONS) -c $<

######################################################################
#                       Règles d'édition de liens                    #
######################################################################

tictactoe: tictactoe.o tictactoec.o tictactoe+.o window.o grid.o gridUI.o button.o case.o
	$(CC) $^ -o $@ `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -f tictactoe *.o

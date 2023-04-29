CC = g++
LIB_DIR = ./lib
DIR = `basename $(CURDIR)`
OPT = -O3 -march=native -std=c++11
#==================================================================
NAME1 = BubbleSort
NAME2 = SelectionSort
NAME3 = InsertionSort
NAME4 = Generator

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
CPP1 = $(NAME1).cpp
CPP2 = $(NAME2).cpp
CPP3 = $(NAME3).cpp
CPP4 = $(NAME4).cpp

all: $(CPP1) $(CPP2) $(CPP3) $(CPP4)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)
	$(CC) $(OPT) $(CPP2) -o $(EXEC2)
	$(CC) $(OPT) $(CPP3) -o $(EXEC3)
	$(CC) $(OPT) $(CPP4) -o $(EXEC4)

#==================================================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o *.exe *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


CC = g++
LIB_DIR = ./lib
DIR = `basename $(CURDIR)`
OPT = -std=c++11
#==================================================================
NAME1 = LinkedList
EXEC1 = $(NAME1).x
CPP1 = $(NAME1).cpp

NAME2 = Generator
EXEC2 = $(NAME2).x
CPP2 = $(NAME2).cpp

NAME3 = 
EXEC3 = $(NAME3).x
CPP3 = $(NAME3).cpp

all: $(CPP1) $(CPP2)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)
	$(CC) $(OPT) $(CPP2) -o $(EXEC2)

run1: $(CPP1)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)

run2: $(CPP2)
	$(CC) $(OPT) $(CPP2) -o $(EXEC2)

#==================================================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o *.exe *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


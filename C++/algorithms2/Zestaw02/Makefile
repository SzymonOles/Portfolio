CC = g++
LIB_DIR = ./lib
DIR = `basename $(CURDIR)`
OPT = -std=c++11
#==================================================================
NAME1 = Queue
EXEC1 = $(NAME1).x
CPP1 = $(NAME1).cpp

NAME2 = Radix
EXEC2 = $(NAME2).x
CPP2 = $(NAME2).cpp

NAME3 = Generator
EXEC3 = $(NAME3).x
CPP3 = $(NAME3).cpp

all: $(CPP1) $(CPP2)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)
	$(CC) $(OPT) $(CPP2) -o $(EXEC2)

Queue: $(CPP1)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)

Radix: $(CPP2)
	$(CC) $(OPT) $(CPP2) -o $(EXEC2)

Generator: $(CPP3)
	$(CC) $(OPT) $(CPP3) -o $(EXEC3)

#==================================================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


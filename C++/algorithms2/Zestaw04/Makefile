CC = g++
LIB_DIR = ./lib
DIR = `basename $(CURDIR)`
OPT = -std=c++11
#==================================================================
NAME1 = ArrayList
NAME2 = Generator
NAME3 = CursorList

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
CPP1 = $(NAME1).cpp
CPP2 = $(NAME2).cpp
CPP3 = $(NAME3).cpp

all: $(CPP1) $(CPP2) $(CPP3)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)
#	$(CC) $(OPT) $(CPP2) -o $(EXEC2)
	$(CC) $(OPT) $(CPP3) -o $(EXEC3)

run1: $(CPP1)
	$(CC) $(OPT) $(CPP1) -o $(EXEC1)

run2: $(CPP2)
	$(CC) $(OPT) $(CPP2) -o $(EXEC2)

run3: $(CPP3)
	$(CC) $(OPT) $(CPP3) -o $(EXEC3)

#==================================================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o *.exe *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


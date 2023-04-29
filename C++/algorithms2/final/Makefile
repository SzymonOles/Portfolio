CC = g++
LIB_DIR = ./lib
DIR = `basename $(CURDIR)`
OPT = -O3 -march=native -std=c++11
SFML = -lsfml-graphics -lsfml-window -lsfml-system
#==================================================================
NAME1 = main
NAME2 = 
NAME3 = 
NAME4 = 

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
CPP1 = $(NAME1).cpp
CPP2 = $(NAME2).cpp
CPP3 = $(NAME3).cpp
CPP4 = $(NAME4).cpp

all: $(CPP1) 
	$(CC) $(OPT) $(CPP1) -o $(EXEC1) $(SFML)
	./$(EXEC1)

#==================================================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o *.exe *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar:
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


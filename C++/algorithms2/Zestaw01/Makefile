CC = g++
LIB_DIR = ./lib
DIR = `basename $(CURDIR)`
OPT = -std=c++11
#==================================================================
IN1 = Stack.cpp ArrayStack.hpp
OUT1 = Stack.x

IN2 = Generator.cpp
OUT2 = Generator.x

IN3 = ONP.cpp ArrayStack.hpp
OUT3 = ONP.x

Stack: $(IN1)
	$(CC) $(OPT) $(IN1) -o $(OUT1)

Generator: $(IN2)
	$(CC) $(OPT) $(IN2) -o $(OUT2)

ONP: $(IN3)
	$(CC) $(OPT) $(IN3) -o $(OUT3)

#==================================================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


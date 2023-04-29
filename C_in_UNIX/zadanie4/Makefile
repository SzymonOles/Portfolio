.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

FILE1 = plik1.txt
FILE2 = plik2.txt
NAME1 = main

EXEC1  = $(NAME1).x  

OBJS1  = $(NAME1).o
#############################################################################
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

LDLIBS = -lm

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1)
###############################################################################
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
###############################################################################
.PHONY: run1

run1: $(EXEC1)
	./$(EXEC1) $(FILE1) $(FILE2)	
	diff -s $(FILE1) $(FILE2)	
# ###############################################################################
# Archiwizacja i kompresja
.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

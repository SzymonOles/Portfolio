.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`
#nazwy============================================
NAME1 = powielacz
NAME2 = program

EXEC1  = $(NAME1).x  
EXEC2  = $(NAME2).x  

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

LIBNAME = libmycode
LIB1o = $(LIBNAME).o
LIB1c = $(LIBNAME).c

HEADER = mycode.h

NAZWA = $(EXEC2)
LPROC = 2
LSEKC = 2
#flagi==========================================
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC -pthread
LFLAGS = -Wall -std=c99 -pedantic -O -pthread

LDLIBS = -lm

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.c
	$(CO) $(CFLAGS) -c $<
#kompilacja=====================================
.PHONY: all
all: $(EXEC1) $(EXEC2)

$(LIB1o): $(LIB1c) $(HEADER)
	$(LD) $(LFLAGS) -c $(LIB1c)

$(EXEC1): $(OBJS1) $(LIB1c)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIB1c)
	$(LD) -o $@ $(LFLAGS) $^

#run============================================
.PHONY: run1 run2
run1: $(EXEC2) $(EXEC1)
	./$(EXEC1) $(NAZWA) $(LPROC) $(LSEKC)

#sprzatanie=======================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

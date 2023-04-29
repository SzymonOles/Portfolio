.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`
#nazwy============================================
NAME1 = klient
NAME2 = serwer

PATHNAME1 = ./$(EXEC1)
PATHNAME2 = ./$(EXEC2)

EXEC1  = $(NAME1).x  
EXEC2  = $(NAME2).x  

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

LIB = mylib
LIB1c = $(LIB).c

#flagi==========================================
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC 
LFLAGS = -Wall -std=c99 -pedantic -O 

LDLIBS = -lm -lrt

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

$(EXEC1): $(OBJS1) $(LIB1c)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2) $(LIB1c)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

#run============================================
.PHONY: run
run: $(EXEC1) $(EXEC2)
	xterm -hold -title SERWER -bg darkred -e $(PATHNAME2) &
	xterm -hold -title KLIENT1 -bg darkgreen -e $(PATHNAME1) &
	xterm -hold -title KLIENT2 -bg darkgreen -e $(PATHNAME1)

#sprzatanie=======================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

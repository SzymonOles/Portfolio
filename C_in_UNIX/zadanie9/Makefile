.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`
#nazwy============================================
NAME1 = main

PATHNAME1 = ./$(EXEC1)

EXEC1  = $(NAME1).x  

OBJS1  = $(NAME1).o

LIB1c = 

WATKI = 3
SEKCJE = 3
#flagi==========================================
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

LDLIBS = -lm -lpthread

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
all: $(EXEC1)

$(EXEC1): $(OBJS1) $(LIB1c)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

#run============================================
.PHONY: run
run: $(EXEC1)
	./$(EXEC1) $(WATKI) $(SEKCJE)

#sprzatanie=======================================
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

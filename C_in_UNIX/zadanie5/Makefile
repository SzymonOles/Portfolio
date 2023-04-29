.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

FILE1 = plik1.txt
FILE2 = plik2.txt
FIFO = fifo
NAME1 = main
NAME2 = producent
NAME3 = konsument

EXEC1  = $(NAME1).x  
EXEC2  = $(NAME2).x  
EXEC3  = $(NAME3).x  

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o

PATH1=./$(EXEC2)
PATH2=./$(EXEC3)
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
all: $(EXEC1) $(EXEC2) $(EXEC3)
###############################################################################
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
###############################################################################
.PHONY: run1

run1: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(FILE1) $(FIFO) $(FILE2) $(EXEC2) $(EXEC3)		
	diff -s $(FILE1) $(FILE2)

run2: $(EXEC2) $(EXEC3)
	mkfifo -m 0777 $(FIFO)
	xterm -hold -title $(NAME2) -e $(PATH1) $(FILE1) $(FIFO) & xterm -hold -title $(NAME3) -e $(PATH2) $(FIFO) $(FILE2)
	unlink $(FIFO)
	diff -s $(FILE1) $(FILE2)	
# ###############################################################################
# Archiwizacja i kompresja
.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

DIR = `basename $(CURDIR)`

NAME1 = glowny
NAME2 = producent
NAME3 = konsument
NAME4 = semafory
NAME5 = pamiec
LIB1 = $(NAME4)
LIB2 = $(NAME5)
INPUT = 1.txt
OUTPUT = 2.txt

ARG1 = $(EXEC2)
ARG2 =	./$(EXEC2)
ARG3 = $(EXEC3)
ARG4 = ./$(EXEC3)
ARG5 = ./$(INPUT)
ARG6 = ./$(OUTPUT)
ARG7 = /SemaforProducent
ARG8 = /SemaforKonsument
ARG9 = /Pamiec

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x
EXEC3  = $(NAME3).x
EXEC1s = $(NAME1)s.x
EXEC2s = $(NAME2)s.x
EXEC3s = $(NAME3)s.x
EXEC1d1 = $(NAME1)d1.x
EXEC2d1 = $(NAME2)d1.x
EXEC3d1 = $(NAME3)d1.x
EXEC1d2 = $(NAME1)d2.x
EXEC2d2 = $(NAME2)d2.x
EXEC3d2 = $(NAME3)d2.x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

LIBS1  = $(LIB1).c
LIBS2  = $(LIB2).c

LIB_NAME = funkcje
LIB_DIR = ./lib
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so
LIB_OBJS = $(OBJS4) $(OBJS5)
HEADS4 = $(NAME4).h
HEADS5 = $(NAME5).h

CFLAGS = -Wall -std=gnu99 -pedantic -O -pthread
LFLAGS = -Wall -std=gnu99 -pedantic -O -pthread
LDLIBS = -lrt

CO = gcc
LD = $(CO)

AR = ar

ARFLAGS = rsv

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(LIB_SHAR): $(LIB_OBJS) 
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC1s) $(EXEC2s) $(EXEC3s) $(EXEC1d) $(EXEC2d) $(EXEC3d)

$(EXEC1): $(OBJS1) $(LIBS1) $(LIBS2)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2) $(LIBS1) $(LIBS2)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

$(EXEC3): $(OBJS3) $(LIBS1) $(LIBS2)
	$(LD) -o $@ $(CFLAGS) $^ $(LDLIBS)

$(EXEC1s): $(OBJS1) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2s): $(OBJS2) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3s): $(OBJS3) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC1d1): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC2d1): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC3d1): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC1d2): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2d2): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3d2): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(OBJS4): $(HEADS4)
$(OBJS5): $(HEADS5)

.PHONY: run runs rund1 rund2

run: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5) $(ARG6) $(ARG7) $(ARG8) $(ARG9)
	diff -s $(INPUT) $(OUTPUT)

runs: $(EXEC1s) $(EXEC2s) $(EXEC3s)
	./$(EXEC1s) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5) $(ARG6) $(ARG7) $(ARG8) $(ARG9)
	diff -s $(INPUT) $(OUTPUT)

rund1: $(EXEC1d1) $(EXEC2d1) $(EXEC3d1)
	./$(EXEC1d1) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5) $(ARG6) $(ARG7) $(ARG8) $(ARG9)
	diff -s $(INPUT) $(OUTPUT)

rund2: $(EXEC1d2) $(EXEC2d2) $(EXEC3d2)
	( export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1d2) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5) $(ARG6) $(ARG7) $(ARG8) $(ARG9) )
	diff -s $(INPUT) $(OUTPUT)

#backup
# run: $(EXEC1) $(EXEC2) $(EXEC3)
# 	./$(EXEC1) $(EXEC2) $(EXEC3)
# 	diff -s $(INPUT) $(OUTPUT)

# runs: $(EXEC1s) $(EXEC2s) $(EXEC3s)
# 	./$(EXEC1s) $(EXEC2s) $(EXEC3s)
# 	diff -s $(INPUT) $(OUTPUT)

# rund1: $(EXEC1d1) $(EXEC2d1) $(EXEC3d1)
# 	./$(EXEC1d1) $(EXEC2d1) $(EXEC3d1)
# 	diff -s $(INPUT) $(OUTPUT)

# rund2: $(EXEC1d2) $(EXEC2d2) $(EXEC3d2)
# 	( export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
# 	./$(EXEC1d2) $(EXEC2d2) $(EXEC3d2) )
# 	diff -s $(INPUT) $(OUTPUT)

.PHONY: clean tar

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
GCC = gcc
oT = -fopenmp -O3 

CFLAGS = -lm 

oL= Otime.c

BINDIR = ../BIN/
PROGS = $(BINDIR)MMFF1c 

all: MMFF1c

clean:
	$(RM) $(PROGS)

MMFF1c:
	$(GCC) $(oT) $(oL) $@.c -o $(BINDIR)$@ $(CFLAGS)

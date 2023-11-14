GCC = gcc
pT = -lpthread -O3
oT = -fopenmp -O3

CFLAGS = -m64 -IAPI/include -IAPI/bin -lpapi
CLinks = -m64 

BINDIR = ../BIN/

all: Otime 

clean:
	rm *.o 

Otime:
	$(GCC) $(oT) -c $@.c $(CLinks)


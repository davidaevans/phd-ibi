PROG =	mc

SRCS = load.c geometry.c keywords.c main.c read.c recipes.c generate.c simulate.c calculate.c dump.c overlap.c potential.c

OBJS = load.o geometry.o keywords.o main.o read.o recipes.o generate.o simulate.o calculate.o dump.o overlap.o potential.o

LIBS = -lm
CC = cc
CFLAGS = -O2 -Wall
LDFLAGS = -s

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(PROG) $(OBJS)

dump.o: global.h prototypes.h
geometry.o: global.h prototypes.h
main.o: global.h prototypes.h
overlap.o: global.h prototypes.h
percolate.o: global.h prototypes.h
spanning.o: global.h prototypes.h
read.o: global.h prototypes.h
recipes.o: global.h prototypes.h
simulate.o: global.h prototypes.h
potentials.o: global.h prototypes.h
generate.o: global.h prototypes.h
load.o: global.h prototypes.h

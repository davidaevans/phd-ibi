PROG =	rdf

SRCS = load.c keywords.c main.c read.c rdf.c geometry.c

OBJS = load.o keywords.o main.o read.o rdf.o geometry.o

LIBS = -lm
CC = cc
CFLAGS = -O2 -Wall
LDFLAGS = -s

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(PROG) $(OBJS)

load.o: global.h prototypes.h
main.o: global.h prototypes.h
read.o: global.h prototypes.h
rdf.o: global.h prototypes.h
geometry.o: global.h prototypes.h
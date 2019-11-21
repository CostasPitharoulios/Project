IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = Point.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Point.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cluster: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o cluster

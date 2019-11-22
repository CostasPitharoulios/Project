IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = Point.hpp Clustering.hpp Curve.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Point.o Clustering.o Curve.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cluster: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean runv runc

runv:
	./cluster -i vectors_dataset_small.csv -o output.txt -c cluster.conf

runc:
	./cluster -i trajectories_dataset_small.csv -o output.txt -c cluster.conf

clean:
	rm -f $(ODIR)/*.o cluster

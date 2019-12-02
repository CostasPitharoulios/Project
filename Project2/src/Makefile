IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -g -O3

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = Point.hpp Clustering.hpp Curve.hpp dist.hpp util.hpp G.hpp H.hpp LSH.hpp CurveHashing.hpp Grid.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Point.o Clustering.o Curve.o dist.o util.o ANN/G.o ANN/H.o ANN/LSH.o ANN/Grid.o ANN/CurveHashing.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cluster: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean runv runc

runv:
	./cluster -i my_vectors_test.csv -o output.txt -c cluster.conf

runc:
	./cluster -i my_curves_test.csv -o output.txt -c cluster.conf

debug:
	valgrind ./cluster -i trajectories_dataset_small.csv -o output.txt -c cluster.conf

clean:
	rm -f $(ODIR)/*.o $(ODIR)/ANN/*.o cluster

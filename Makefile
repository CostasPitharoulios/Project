all: curvesDemo lshDemo hyperCubeDemo

curvesDemo : Curves/main.o Point.o Curves/Curve.o Curves/readingFunctions.o Curves/curveHashing.o Curves/LSHC.o Curves/Grid.o dist.o H.o G.o LSH/LSH.o util.o HyperCube/HC.o
	g++ Curves/main.o  Point.o Curves/Curve.o Curves/readingFunctions.o Curves/curveHashing.o Curves/LSHC.o Curves/Grid.o dist.o H.o G.o LSH/LSH.o HyperCube/HC.o util.o -o curvesDemo -g -O3

lshDemo : LSH/main.o Point.o dist.o H.o G.o LSH/LSH.o util.o Curves/Curve.o
	g++ LSH/main.o Point.o dist.o H.o G.o LSH/LSH.o util.o Curves/Curve.o -o lshDemo -O3

hyperCubeDemo : HyperCube/main.o Point.o dist.o H.o G.o HyperCube/HC.o util.o Curves/Curve.o
	g++ HyperCube/main.o  Point.o dist.o H.o G.o HyperCube/HC.o util.o Curves/Curve.o -o hyperCubeDemo -O3

Curves/main.o : Curves/main.cpp
	g++ -c Curves/main.cpp -g -o Curves/main.o -O3

Point.o : Point.cpp Point.hpp
	g++ -c Point.cpp -o Point.o -g -O3

Curves/Curve.o	: Curves/Curve.cpp Curves/Curve.hpp
	g++ -c Curves/Curve.cpp -o Curves/Curve.o -g -O3

Curves/LSHC.o: Curves/LSHC.cpp Curves/LSHC.hpp
	g++ -c Curves/LSHC.cpp -o Curves/LSHC.o -g -O3

Curves/readingFunctions.o:	Curves/readingFunctions.cpp Curves/readingFunctions.hpp	
	g++ -c Curves/readingFunctions.cpp -o Curves/readingFunctions.o -g -O3

Curves/curveHashing.o:	Curves/curveHashing.cpp Curves/curveHashing.hpp
	g++ -c Curves/curveHashing.cpp -o Curves/curveHashing.o -g -O3

Curves/Grid.o:	Curves/Grid.cpp Curves/Grid.hpp
	g++ -c Curves/Grid.cpp -o Curves/Grid.o -g  -O3

LSH/main.o : LSH/main.cpp
	g++ -c LSH/main.cpp -o LSH/main.o -g  -O3

H.o : H.cpp
	g++ -c H.cpp -o H.o -g -O3

G.o : G.cpp
	g++ -c G.cpp -o G.o -g -O3

LSH/LSH.o : LSH/LSH.cpp LSH/LSH.hpp
	g++ -c LSH/LSH.cpp -o LSH/LSH.o -g -O3

util.o : util.cpp
	g++ -c util.cpp -o util.o -g -O3

dist.o : dist.cpp
	g++ -c dist.cpp -o dist.o -g -O3

HyperCube/main.o : HyperCube/main.cpp
	g++ -c HyperCube/main.cpp -o HyperCube/main.o -g  -O3

HyperCube/HC.o : HyperCube/HC.cpp HyperCube/HC.hpp
	g++ -c HyperCube/HC.cpp -o HyperCube/HC.o -g -O3

clean:
	rm curvesDemo Curves/main.o Point.o Curves/Curve.o Curves/readingFunctions.o Curves/curveHashing.o Curves/LSHC.o Curves/Grid.o lshDemo LSH/main.o dist.o H.o G.o LSH/LSH.o util.o HyperCube/main.o HyperCube/HC.o hyperCubeDemo

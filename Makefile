all: Curves/demo LSH/demo #HC/demo

Curves/demo : Curves/main.o Point.o Curves/Curve.o Curves/readingFunctions.o Curves/DTW.o Curves/curveHashing.o Curves/LSHC.o Curves/Grid.o dist.o H.o G.o LSH/LSH.o util.o
	g++ Curves/main.o  Point.o Curves/Curve.o Curves/readingFunctions.o Curves/DTW.o Curves/curveHashing.o Curves/LSHC.o Curves/Grid.o dist.o H.o G.o LSH/LSH.o util.o -o Curves/demo -g

LSH/demo : LSH/main.o Point.o dist.o H.o G.o LSH/LSH.o util.o
	g++ LSH/main.o Point.o dist.o H.o G.o LSH/LSH.o util.o -o LSH/demo

Curves/main.o : Curves/main.cpp
	g++ -c Curves/main.cpp -g -o Curves/main.o

Point.o : Point.cpp Point.hpp
	g++ -c Point.cpp -o Point.o -g

Curves/Curve.o	: Curves/Curve.cpp Curves/Curve.hpp
	g++ -c Curves/Curve.cpp -o Curves/Curve.o -g

Curves/DTW.o:	Curves/DTW.cpp
	g++ -c Curves/DTW.cpp -o Curves/DTW.o -g

Curves/LSHC.o: Curves/LSHC.cpp Curves/LSHC.hpp
	g++ -c Curves/LSHC.cpp -o Curves/LSHC.o -g

Curves/readingFunctions.o:	Curves/readingFunctions.cpp Curves/readingFunctions.hpp	
	g++ -c Curves/readingFunctions.cpp -o Curves/readingFunctions.o -g

Curves/curveHashing.o:	Curves/curveHashing.cpp Curves/curveHashing.hpp
	g++ -c Curves/curveHashing.cpp -o Curves/curveHashing.o -g

Curves/Grid.o:	Curves/Grid.cpp Curves/Grid.hpp
	g++ -c Curves/Grid.cpp -o Curves/Grid.o -g 

LSH/main.o : LSH/main.cpp
	g++ -c LSH/main.cpp -o LSH/main.o -g 

H.o : H.cpp
	g++ -c H.cpp -o H.o -g

G.o : G.cpp
	g++ -c G.cpp -o G.o -g

LSH/LSH.o : LSH/LSH.cpp LSH/LSH.hpp
	g++ -c LSH/LSH.cpp -o LSH/LSH.o -g

util.o : util.cpp
	g++ -c util.cpp -o util.o -g

dist.o : dist.cpp
	g++ -c dist.cpp -o dist.o -g

clean:
	rm Curves/demo Curves/main.o Point.o Curves/Curve.o Curves/readingFunctions.o Curves/DTW.o Curves/curveHashing.o Curves/LSHC.o Curves/Grid.o LSH/demo LSH/main.o dist.o H.o G.o LSH/LSH.o util.o

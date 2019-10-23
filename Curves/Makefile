demo : main.o ../Point.o Curve.o readingFunctions.o DTW.o curveHashing.o LSHC.o Grid.o ../LSH/LSH.o
	g++ main.o  ../Point.o Curve.o readingFunctions.o DTW.o curveHashing.o LSHC.o Grid.o ../LSH/LSH.o -o demo -g

main.o : main.cpp
	g++ -c main.cpp -g

../Point.o : ../Point.cpp ../Point.hpp
	g++ -c ../Point.cpp -o ../Point.o -g

Curve.o	: Curve.cpp Curve.hpp
	g++ -c Curve.cpp -o Curve.o -g

DTW.o:	DTW.cpp
	g++ -c DTW.cpp -o DTW.o -g

LSHC.o: LSHC.cpp LSHC.hpp
	g++ -c LSHC.cpp -o LSHC.o -g

../LSH/LSH.o: ../LSH/LSH.cpp ../LSH/LSH.hpp
	g++ -c ../LSH/LSH.cpp -o ../LSH/LSH.o -g

readingFunctions.o:	readingFunctions.cpp readingFunctions.hpp	
	g++ -c readingFunctions.cpp -o readingFunctions.o -g

curveHashing.o:	curveHashing.cpp curveHashing.hpp
	g++ -c curveHashing.cpp -o curveHashing.o -g

Grid.o:	Grid.cpp Grid.hpp
	g++ -c Grid.cpp -o Grid.o -g 

clean:
	rm demo main.o ../Point.o Curve.o readingFunctions.o DTW.o curveHashing.o LSHC.o Grid.o ../LSH/LSH.o

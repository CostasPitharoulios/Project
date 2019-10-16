demo : main.o ../Point.o Curve.o readingFunctions.o DTW.o curveHashing.o
	g++ main.o  ../Point.o Curve.o readingFunctions.o DTW.o curveHashing.o -o demo 

main.o : main.cpp
	g++ -c main.cpp

../Point.o : ../Point.cpp ../Point.hpp
	g++ -c ../Point.cpp -o ../Point.o

Curve.o	: Curve.cpp Curve.hpp
	g++ -c Curve.cpp -o Curve.o

DTW.o:	DTW.cpp DTW.o
	g++ -c DTW.cpp -o DTW.o

readingFunctions.o:	readingFunctions.cpp readingFunctions.hpp	
	g++ -c readingFunctions.cpp -o readingFunctions.o

curveHashing.o:	curveHashing.cpp curveHashing.hpp
	g++ -c curveHashing.cpp -o curveHashing.o

clean:
	rm demo main.o ../Point.o Curve.o readingFunctions.o DTW.o curveHashing.o

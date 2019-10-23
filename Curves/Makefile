demo : main.o Curve.o ../Point.o readingFunctions.o curveHashing.o LSHC.o Grid.o ../dist.o
	g++ main.o  ../Point.o Curve.o readingFunctions.o curveHashing.o LSHC.o Grid.o ../dist.o -o demo -g

main.o : main.cpp
	g++ -c main.cpp -g

../Point.o : ../Point.cpp ../Point.hpp
	g++ -c ../Point.cpp -o ../Point.o -g

Curve.o	: Curve.cpp Curve.hpp
	g++ -c Curve.cpp -o Curve.o -g

LSHC.o: LSHC.cpp LSHC.hpp
	g++ -c LSHC.cpp -o LSHC.o -g

readingFunctions.o:	readingFunctions.cpp readingFunctions.hpp	
	g++ -c readingFunctions.cpp -o readingFunctions.o -g

curveHashing.o:	curveHashing.cpp curveHashing.hpp
	g++ -c curveHashing.cpp -o curveHashing.o -g

Grid.o:	Grid.cpp Grid.hpp
	g++ -c Grid.cpp -o Grid.o -g 

../dist.o:	../dist.cpp ../dist.hpp
	g++ -c ../dist.cpp -o ../dist.o -g

clean:
	rm demo main.o ../Point.o Curve.o readingFunctions.o curveHashing.o LSHC.o Grid.o ../dist.o

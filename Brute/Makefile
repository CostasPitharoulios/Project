demo : main.o ../Point.o ../dist.o Curve.o
	g++ main.o  ../Point.o ../dist.o Curve.o -o demo

main.o : main.cpp
	g++ -c main.cpp

Curve.o : ../Curves/Curve.cpp
	g++ -c ../Curves/Curve.cpp

../Point.o : ../Point.cpp ../Point.hpp
	g++ -c ../Point.cpp -o ../Point.o

../dist.o : ../dist.cpp ../dist.hpp
	g++ -c ../dist.cpp -o ../dist.o

clean:
	rm demo main.o ../Point.o ../dist.o

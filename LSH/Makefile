demo : main.o ../Point.o ../dist.o
	g++ main.o  ../Point.o ../dist.o -o demo

main.o : main.cpp
	g++ -c main.cpp

../Point.o : ../Point.cpp ../Point.hpp
	g++ -c ../Point.cpp -o ../Point.o

../dist.o : ../dist.cpp ../dist.hpp
	g++ -c ../dist.cpp -o ../dist.o

clean:
	rm demo main.o ../Point.o ../dist.o

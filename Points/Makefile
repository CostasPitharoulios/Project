demo : main.o ../Point.o
	g++ main.o  ../Point.o -o demo

main.o : main.cpp
	g++ -c main.cpp

../Point.o : ../Point.cpp ../Point.hpp
	g++ -c ../Point.cpp -o ../Point.o

clean:
	rm demo main.o ../Point.o

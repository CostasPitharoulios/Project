demo : main.o ../Point.o ../dist.o H.o ../util.o
	g++ main.o  ../Point.o ../dist.o H.o ../util.o -o demo

main.o : main.cpp
	g++ -c main.cpp -g

../Point.o : ../Point.cpp
	g++ -c ../Point.cpp -o ../Point.o -g

../dist.o : ../dist.cpp
	g++ -c ../dist.cpp -o ../dist.o -g

H.o : H.cpp
	g++ -c H.cpp -g

../util.o : ../util.cpp
	g++ -c ../util.cpp -o ../util.o -g

clean:
	rm demo main.o ../Point.o ../dist.o H.o ../util.o

demo : main.o ../Point.o ../dist.o ../H.o ../G.o HC.o ../util.o
	g++ main.o  ../Point.o ../dist.o ../H.o ../G.o HC.o ../util.o -o demo

main.o : main.cpp
	g++ -c main.cpp -g

../Point.o : ../Point.cpp
	g++ -c ../Point.cpp -o ../Point.o -g

../H.o : ../H.cpp
	g++ -c ../H.cpp -o ../H.o -g

../G.o : ../G.cpp
	g++ -c ../G.cpp -o ../G.o -g

HC.o : HC.cpp
	g++ -c HC.cpp -o HC.o -g

../util.o : ../util.cpp
	g++ -c ../util.cpp -o ../util.o -g

../dist.o : ../dist.cpp
	g++ -c ../dist.cpp -o ../dist.o -g

clean:
	rm demo main.o ../Point.o ../dist.o ../H.o HC.o ../G.o ../util.o

all: Driver.o QHeap.o Food.o Order.o Orders.o Store.o
	g++ -Wall Driver.cpp QHeap.o Food.o Order.o Orders.o Store.o -std=c++11 -o driver

QHeap.o : QHeap.h
	g++ -Wall -c -std=c++11

Food.o : Food.cpp Food.h
	g++ -Wall -c -std=c++11 Food.cpp

Driver.o: Driver.cpp
	g++ -Wall -c -std=c++11 Driver.cpp

Store.o: Store.cpp Store.h
	g++ -Wall -c -std=c++11 Store.cpp

Order.o: Order.cpp Order.h
	g++ -Wall -c -std=c++11 Order.cpp

Orders.o: Orders.cpp Orders.h
	g++ -Wall -c -std=c++11 Orders.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./driver
Vector: funkcijos.o
	g++ -o mainVector mainVector.cpp funkcijos.o

List: funkcijos.o
	g++ -o mainList mainList.cpp funkcijos.o

Deque: funkcijos.o
	g++ -o mainDeque mainDeque.cpp funkcijos.o

funkcijos:
	g++ -c funkcijos.cpp

clean:
	del *.o mainVector mainList mainDeque
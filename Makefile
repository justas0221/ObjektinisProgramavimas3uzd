main: funkcijos.o
	g++ -o mainVector mainVector.cpp funkcijos.o
	
Vector: funkcijos.o
	g++ -o mainVector mainVector.cpp funkcijos.o -O3

funkcijos:
	g++ -c funkcijos.cpp -O3

clean:
	del *.o mainVector
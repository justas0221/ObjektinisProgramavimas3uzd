main: funkcijos.o
	g++ -o mainVector mainVector.cpp funkcijos.o
	
Vector: funkcijos.o
	g++ -o mainVector mainVector.cpp funkcijos.o

funkcijos:
	g++ -c funkcijos.cpp

clean:
	del *.o mainVector
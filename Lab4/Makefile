Lab4_3973887764: Matrix.o main.o
	g++ Matrix.o main.o -o Lab4_3973887764
    
Matrix.o: Matrix.h
	g++ -c Matrix.cpp
    
main.o: main.cpp Matrix.h
	g++ -c main.cpp
    
clean:
	rm *.o Lab*

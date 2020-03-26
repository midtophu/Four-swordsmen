CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku_solve

sudoku_dancing_links.o : sudoku.h SDK.h
	g++ -c sudoku_dancing_links.cc -O2 

neighbor.o : sudoku.h SDK.h
	g++ -c neighbor.cc -O2 
sudoku_basic.o : sudoku.h SDK.h
	g++ -c sudoku_basic.cc -O2 

sudoku_solve: main.cc neighbor.o  sudoku_dancing_links.o sudoku.h SDK.h sudoku_basic.o
	g++   -O2  -o $@ $^ -lpthread

clean:
	-rm sudoku_dancing_links.o
	-rm neighbor.o
	-rm sudoku_basic.o
	-rm sudoku_solve

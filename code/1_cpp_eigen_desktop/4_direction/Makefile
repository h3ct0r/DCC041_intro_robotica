CC=g++
CFLAGS=-std=c++17 -Wall
INCLUDE_EIGEN=/opt/homebrew/Cellar/eigen/5.0.1/include/eigen3
INCLUDE_MATPLOT=/opt/homebrew/Cellar/matplotplusplus/1.2.2/include
LIB_MATPLOT=/opt/homebrew/Cellar/matplotplusplus/1.2.2/lib
OBJ_DIR=.

main: main.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE_EIGEN) -I$(INCLUDE_MATPLOT) -L$(LIB_MATPLOT) -lmatplot -lm main.cpp -o main

run: main
	./main

clean:
	rm -f main
CC=g++
CFLAGS=-std=c++14 -Wall
INCLUDE_EIGEN=/opt/homebrew/include/eigen3
OBJ_DIR=.

main: main.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE_EIGEN) main.cpp -o main

run: main
	./main

clean:
	rm -f main
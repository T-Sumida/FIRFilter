CC=g++
INC= -I./src
CFLAGS = -c -g -Wall -Wextra -ln

all: test

%.o: %.cpp
	$(CC) -O3 -c -o $@ $< $(INC) $(CFLAGS)

test.o: test.cpp
	$(CC) -O3 -c test.cpp $(INC)

clean:
	rm test
	rm *.o
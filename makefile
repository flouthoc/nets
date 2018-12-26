CC=g++
CFLAGS=-std=c++11
OBJ=main.o
DEPS=nets.h

%.o: %.h (DEPS)
		$(CC) $(CFLAGS) -c $< -o $@


main: main.cpp
	$(CC) $(CFLAGS) -o $@ $^
	


.PHONY: clean cleanall

clean:
	rm *.o

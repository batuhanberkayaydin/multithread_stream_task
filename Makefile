########################################## MAKEFILE ######################################
CC = g++

CFLAGS +=-std=c++14 -I ./
SRCS = *.cpp
PROG = main

OPENCV = `pkg-config opencv4 --cflags --libs`
THREAD = -lpthread

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(OPENCV) $(THREAD)

clean:
	rm -f main main.o
	rm -rf main

########################################## MAKEFILE ######################################
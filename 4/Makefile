CC = gcc
AR = ar -rcs
FLAGS = -Wall -w

all: dir_traversal

dir_traversal.o:  dir_traversal.c 
	$(CC) $(FLAGS) -c  dir_traversal.c 
	
dir_traversal: dir_traversal.o
	$(CC) $(FLAGS) dir_traversal.o -o dir_traversal

.PHONI : clean

clean:
	-rm dir_traversal *.o 2>/dev/null
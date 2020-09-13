
CC = gcc
AR = ar -rcs
FLAGS = -Wall

all: check_pid

check_pid.o:  check_pid.c
	$(CC) $(FLAGS) -c  check_pid.c
	
check_pid: check_pid.o
	$(CC) $(FLAGS) check_pid.o -o check_pid

.PHONI : clean

clean:
	-rm check_pid *.o  2>/dev/null



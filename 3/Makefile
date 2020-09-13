CC = gcc
AR = ar -rcs
FLAGS = -Wall

all: set_policy

set_policy.o:  set_policy.c 
	$(CC) $(FLAGS) -c  set_policy.c 
	
set_policy: set_policy.o
	$(CC) $(FLAGS) set_policy.o -o set_policy

.PHONI : clean

clean:
	-rm set_policy *.o  2>/dev/null

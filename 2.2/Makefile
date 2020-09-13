CC = gcc
AR = ar -rcs
FLAGS = -Wall

all: server client

client.o:  client.c
	$(CC) $(FLAGS) -c  client.c
	
client: client.o
	$(CC) $(FLAGS) client.o -o client

server.o:  server.c
	$(CC) $(FLAGS) -c  server.c
	
server: server.o
	$(CC) $(FLAGS) server.o -o server

.PHONI : clean

clean:
	-rm server client *.o  2>/dev/null
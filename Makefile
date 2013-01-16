# 
# Junhua Zhang
# Ryerson University
# Computer Engineering Student
# This is assignment4
# junhua.zhang@ryerson.ca
# 

CC = gcc
CFLAGS = -g -Wall

#invoke in termainl by $make all
#only one executable: test
all: server client

#exectuable server client depends on 
server: server.o  dealer.o
	gcc $(CFLAGS) -o server server.o dealer.o

client: client.o
	gcc $(CFLAGS) -o client client.o


#server.o depends on server.c
server.o: server.c

#client.o depends on client.c
client.o: client.c

#dealer.o depends on dealer.c
dealer.o: dealer.c

#invoke in terminal by $make clean
# remove following files:
#   with ~ (i.e. *~)
#   a.out
#   server client exectuable
#   all .o files, i.e. (*.o)
clean:
	rm -f *~ core a.out *.o client server

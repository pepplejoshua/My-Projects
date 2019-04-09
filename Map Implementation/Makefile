# Makefile for the socket programming tutorial
#

freq = BSTree.o Map.o freq.o BSTree.h Map.h
server = ServerSocket.o Socket.o server.o Formatter.h ServerSocket.h Socket.h SocketException.h
client = ClientSocket.o Socket.o client.o Formatter.h ServerSocket.h Socket.h SocketException.h


all : freq

server: $(freq)
	g++ -o freq $(freq)

BSTree: BSTree.cc
Map: Map.cc
freq: freq.cc

clean:
	rm -f *.o freq *~

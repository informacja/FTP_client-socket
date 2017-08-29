all: main

main.o: main.cpp ftp.h
	g++ -c -g main.cpp ftp.h -std=c++11

main: main.o
	g++ -g -o main main.o

clean:
	rm main main.o
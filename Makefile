all: main

main.o: ftp.h main.cpp
	g++ -c -g ftp.h main.cpp -std=c++11 -Wno-write-strings -Wno-format-security

main: main.o
	g++ -g -o main main.o

clena:
	rm main main.o


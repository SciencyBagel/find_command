BIN = findf
CC := g++

$(BIN):findf.o utilities.o
	$(CC) findf.o utilities.o -o $@
	rm -f *.o

findf.o:findf.cpp
	$(CC) -c findf.cpp

utilities.o:utilities.cpp
	$(CC) -c utilities.cpp

clean:
	rm -f findf *.o

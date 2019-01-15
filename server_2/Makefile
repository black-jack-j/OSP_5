SOURCE = ./src
HEADERS = $(SOURCE)/headers
SHARED = ../shared_headers
TARGET = server

objects = main.o dead_pool.o

server : $(objects)
	gcc -pthread -o $(TARGET) $(objects)

main.o : $(SOURCE)/main.c
	gcc -c $(SOURCE)/main.c -iquote $(HEADERS)

dead_pool.o : $(SOURCE)/dead_pool.c
	gcc -c $(SOURCE)/dead_pool.c -iquote $(HEADERS)
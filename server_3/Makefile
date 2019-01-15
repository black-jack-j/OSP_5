SOURCE = ./src
HEADERS = $(SOURCE)/headers
SHARED = ../shared_headers
TARGET_DIR = ./bin
TARGET = lab5_1 

objects = server.o lab5_info.o server_io.o

server : $(objects)
	gcc -o server $(objects)

server.o :
	gcc -c $(SOURCE)/server.c -iquote $(SHARED) -iquote $(HEADERS)

lab5_info.o : $(SHARED)/lab5_info.c
	gcc -c $(SHARED)/lab5_info.c

server_io.o : $(SOURCE)/server_io.c
	gcc -c $(SOURCE)/server_io.c -iquote $(SHARED) -iquote $(HEADERS)
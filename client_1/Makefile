SOURCE = ./src
HEADERS = $(SOURCE)/headers
SHARED = ../shared_headers
TARGET_DIR = ./bin
TARGET = lab5_1 

objects = client.o lab5_info.o client_io.o

client : $(objects)
	gcc -o client $(objects)

client.o :
	gcc -c $(SOURCE)/client.c -iquote $(SHARED) -iquote $(HEADERS)

lab5_info.o : $(SHARED)/lab5_info.c
	gcc -c $(SHARED)/lab5_info.c

client_io.o : $(SOURCE)/client_io.c
	gcc -c $(SOURCE)/client_io.c -iquote $(SHARED) -iquote $(HEADERS)
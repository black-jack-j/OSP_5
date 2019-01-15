#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "lab5_info.h"
#include "client_io.h"

int main(int argc, char* argv[]){
	if(argc < 2){
		fprintf(stderr, "no arguments recieved\n");
		exit(EXIT_FAILURE);
	}
	int msgid;
	sscanf(argv[1], "%d", &msgid);
	init(msgid, CLIENT_MODE, PERM);
	if(!client_snd()){
		struct info _info;
		if(client_rcv(&_info) > 0){
			print_info(&_info);
			exit(EXIT_SUCCESS);
		}else{
			fprintf(stderr, "can't read from queue\n");
		}
	}else fprintf(stderr, "can't write to queue\n");
	exit(EXIT_FAILURE);
}
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "lab5_info.h"
#include <signal.h>
#include "server_io.h"

void sigproc(int num);

int main(int argc, char* argv[]){
	signal(SIGINT, sigproc);
	struct info* _info = new_info(getpid(), getuid(), getgid());
	printf("pid: %d\n", _info->pid);
	init(_info->pid, SERVER_MODE, PERM);
	int oldtime = time(NULL);
	int curtime;
	int rcv;
	while(1){
		if((curtime = time(NULL)) - oldtime >= 1){
			_info->elapsed_time++;
			getloadavg(_info->load, 3);
			oldtime = curtime;
		}
		if((rcv = server_rcv()) > 0){
			server_snd(_info);
		}
	}
	return 0;
}

void sigproc(int num){
	signal(SIGINT, sigproc);
	if(clear()){
		fprintf(stderr, "message queue could not be deleted\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "message queue was deleted\n");
	exit(EXIT_SUCCESS);
}
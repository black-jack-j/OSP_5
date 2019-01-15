#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "lab5_info.h"
#include <signal.h>
#include "server_io.h"

struct info* _info;

void print_pid(int num);

void print_uid(int num);

void print_gid(int num);

void print_time(int num);

void print_load(int num);

int main(int argc, char* argv[]){
	struct sigaction pid = {0};
	struct sigaction uid = {0};
	struct sigaction gid = {0};
	struct sigaction timer = {0};
	struct sigaction load = {0};
	pid.sa_handler = print_pid;
	gid.sa_handler = print_gid;
	uid.sa_handler = print_uid;
	timer.sa_handler = print_time;
	load.sa_handler = print_load;
	sigaction(SIGHUP, &pid, NULL);
	sigaction(SIGINT, &uid, NULL);
	sigaction(SIGTERM, &gid, NULL);
	sigaction(SIGUSR1, &timer, NULL);
	sigaction(SIGUSR2, &load, NULL);
	_info = new_info(getpid(), getuid(), getgid());
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

void print_pid(int num){
	printf("PID: %d\n", _info->pid);
}

void print_uid(int num){
	printf("UID: %d\n", _info->uid);
}

void print_gid(int num){
	printf("GID: %d\n", _info->gid);
}

void print_time(int num){
	printf("ELAPSED_TIME: %d\n", _info->elapsed_time);
}

void print_load(int num){
	printf("LOAD: %f (1), %f (5), %f (15)\n", _info->load[0], _info->load[1], _info->load[2]);
}
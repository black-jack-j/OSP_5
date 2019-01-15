#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include "lab5_info.h"
#include <stdio.h>
int MSGID = 0;
struct message{
	long type;
	struct info _info;
};

int init(int pid, int mode, int perm){
	if(!MSGID){
		if(mode == SERVER_MODE) MSGID = msgget(pid, IPC_CREAT | perm);
		else if(mode == CLIENT_MODE) MSGID = msgget(pid, perm);
		else MSGID = -1; 
	}
	return MSGID;
}

struct info* new_info(int pid, int uid, int gid){
	struct info* this = malloc(sizeof(struct info));
	this->pid = pid;
	this->gid = gid;
	this->uid = uid;
	this->elapsed_time = 0;
	return this;
}

int clear(){
	return msgctl(MSGID, IPC_RMID, NULL);
}

void print_info(struct info* _info){
	printf("PID: %d, UID: %d, GID: %d, TIME: %d, ", _info->pid, _info->uid, _info->gid, _info->elapsed_time);
	printf("average load: %f (1), %f (5), %f (15)\n", _info->load[0], _info->load[1], _info->load[2]);
}
#include "server_io.h"
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>

static int PID = -1;

int server_rcv(){
	struct rqst_msg msg;
	long size = sizeof(struct rqst_msg) - sizeof(long);
	long read = msgrcv(MSGID, &msg, size, RQST_TYPE, IPC_NOWAIT);
	if(read > 0){
		PID = msg.pid;
		printf("%d\n", PID);
	}
	return read;
}

int server_snd(struct info* _info){
	if(PID == -1) return -666;
	struct rspn_msg msg;
	msg.mtype = PID;
	msg._info = *_info;
	int size = sizeof(struct rspn_msg) - sizeof(long);
	int send = msgsnd(MSGID, &msg, size, IPC_NOWAIT);
	if(!send) PID = -1;
	return send; 
}
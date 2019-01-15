#include "client_io.h"
#include <sys/msg.h>
#include <sys/ipc.h>
#include "lab5_info.h"
#include <unistd.h>

static int PID = -1;

int client_snd(){
	struct rqst_msg msg;
	msg.mtype = RQST_TYPE;
	msg.pid = getpid();
	int size = sizeof(struct rqst_msg) - sizeof(long);
	int send = msgsnd(MSGID, &msg, size, IPC_NOWAIT);
	if(!send) PID = msg.pid;
	return send;
}

int client_rcv(struct info* _info){
	if(PID == -1) return -666;
	struct rspn_msg msg;
	int size = sizeof(struct rspn_msg) - sizeof(long);
	int rcv = msgrcv(MSGID, &msg, size, PID, 0);
	if(rcv > 0){
		*_info = msg._info;
		PID = -1;
	}
	return rcv;
}
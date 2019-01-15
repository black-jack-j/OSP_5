#ifndef LAB5_INFO
#define LAB5_INFO
#define RQST_TYPE 1
#define PERM 0666
#define CLIENT_MODE 666
#define SERVER_MODE 13
extern int MSGID;

struct info
{
	int pid;
	int uid;
	int gid;
	int elapsed_time;
	double load[3];
};

struct rqst_msg
{
	long mtype;
	int pid;
};

struct rspn_msg
{
	long mtype;
	struct info _info;
};

struct info* new_info(int pid, int uid, int gid);

int init(int pid, int mode, int perm);

void print_info(struct info* _info);

int clear();
#endif
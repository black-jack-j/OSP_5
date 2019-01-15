#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <semaphore.h>
#include "dead_pool.h"

static sem_t _sem;

void* inverse_order(void* arg){
	char* string = (char*)arg;
	int len = strlen(string);
	char tmp;
	sem_wait(&_sem);
	for(int i=0;i<len/2;i++){
		tmp = string[i];
		string[i] = string[len-i-1];
		string[len-i-1] = tmp;
	}
	sem_post(&_sem);
	return NULL;
}

void* inverse_case(void* arg){
	char* string = (char*) arg;
	int len = strlen(string);
	sem_wait(&_sem);
	for(int i=0;i<len;i++){
		string[i] = isupper(string[i]) ? tolower(string[i]) : toupper(string[i]);
	}
	sem_post(&_sem);
	return NULL;
}

int main(int argc, char const *argv[]){
	pthread_t tid1;
	pthread_t tid2;
	sem_init(&_sem, 0, 1);
	void* ex_status;
	char val[] = "abcdefghijklmnopqrstuvwxyz";
	job _job1 = inverse_order;
	job _job2 = inverse_case;
	struct dead_list* list = new_list();
	struct dead_node* node1 = new_node(_job1, val);
	struct dead_node* node2 = new_node(_job2, val);
	append_list(list, &node1);
	append_list(list, &node2);
	struct iterator* _iter = new_iterator(list);
	struct i_node* next_node;
	while(1){
		if(!has_next(_iter)) break;
		time_t now = time(NULL);
		while(time(NULL) == now);
		now = time(NULL);
		next_node = next(_iter);
		pthread_create(&tid1, NULL, next_node->val->_job, next_node->val->args);
		next_node = next(_iter);
		pthread_create(&tid2, NULL, next_node->val->_job, next_node->val->args);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		printf("%s\n", val);
	}
	return 0;
}
#include "dead_pool.h"
#include <stdlib.h>

struct dead_list* new_list(){
	struct dead_list* this = malloc(sizeof(struct dead_list));
	this->head = NULL;
	this->crnt = NULL;
}

struct dead_node* new_node(job _job, void* args){
	struct dead_node* this = malloc(sizeof(struct dead_node));
	this->next = NULL;
	this->_job = _job;
	this->args = args;
	return this;
}

void append_list(struct dead_list* list, struct dead_node** node){
	if(!list->head){
		list->head = *node;
		list->crnt = list->head;
		return;
	}
	struct dead_node* tmp = list->head;
	while(tmp->next) tmp = tmp->next;
	tmp->next = *node;
	return;
}

static void append_iterator(struct iterator* iterator, const struct dead_node* node){
	struct i_node* next = malloc(sizeof(struct i_node));
	next->val = node;
	next->next = NULL;
	if(!iterator->next){
		iterator->next = next;
	}else
	{
		struct i_node* tmp = iterator->next;
		while(tmp->next) tmp = tmp->next;
		tmp->next = next;
	}
}

struct iterator* new_iterator(struct dead_list* list){
	struct iterator* this = malloc(sizeof(struct iterator));
	this->next = NULL;
	struct dead_node* tmp = list->head;
	while(tmp){
		append_iterator(this, tmp);
		tmp = tmp->next;
	}
	struct i_node* temp = this->next;
	if(temp){
		while(temp->next) temp = temp->next;
		temp->next = this->next;
	}
	return this;
}

struct i_node* next(struct iterator* iterator){
	struct i_node* tmp = iterator->next;
	iterator->next = iterator->next->next;
	return tmp;
}

bool has_next(struct iterator* iterator){
	return iterator->next;
}
#ifndef DEAD_POOL
#define DEAD_POOL

#include <stdbool.h>

typedef void* (*job)(void*);

struct dead_node
{
	job _job;
	void* args;
	struct dead_node* next;
};

struct dead_list
{
	struct dead_node* head;
	struct dead_node* crnt;
};

struct i_node{
	const struct dead_node* val;
	struct i_node* next;
};

struct iterator{
	struct i_node* next;
};

struct dead_list* new_list();

struct dead_node* new_node(job _job, void* args);

void append_list(struct dead_list* list, struct dead_node** node);

struct iterator* new_iterator(struct dead_list* list);

struct i_node* next(struct iterator* iterator);

bool has_next(struct iterator* iterator);

#endif
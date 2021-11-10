/*
 *	Implementation of a stack of void pointers
 */

#include "stack.h"

struct Stack{
	void **content;
 	int next;
 	int size;
};

const size_t VSIZE = sizeof(void *);

struct Stack *initstack(int size){
	struct Stack *s = malloc(sizeof(struct Stack));
	if(size == -1)
		size = MAXSTACKSIZE;
	s->size = size;
	s->next = 0;
	s->content = malloc(size*VSIZE);
	return s;
}

int isempty(struct Stack *s){
	return (s->next == 0);
}

int isfull(struct Stack *s){
	return (s->next >= s->size);
}

int push(struct Stack *s, void *element){
	if(isfull(s))
		return -1;
	int start = s->next * VSIZE;
	*(s->content + start) = element;
	s->next++;
	return 1;
}

void *top(struct Stack *s){
	if(isempty(s)) 
		return NULL;
	int start = (s->next - 1) * VSIZE;
	return *(s->content + start);
}

void *pop(struct Stack *s){
	if(isempty(s))
		return NULL;
	void *out = top(s);
	s->next--;
	return out;
}

void freestack(struct Stack *s){
	free(s->content);
	free(s);
}


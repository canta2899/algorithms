#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAXSTACKSIZE 125000 // 1MB of void pointers

struct Stack;

/*
 * Initializes a stack with a capacity
 * of "size" pointers. If size is -1 allocates
 * the MAXSTACKSIZE value
 */
struct Stack *initstack(int size);


/* 
 * Returns 1 if stack is empty
 * 0 otherwise 
 */
int isempty(struct Stack *s);


/* 
 * Returns 1 if stack is full
 * 0 otherwise 
 */
int isfull(struct Stack *s);


/* 
 * Pushes element inside stack
 * Returns 1 if push was successful
 * Returns -1 otherwise (stack overflow) 
 */
int push(struct Stack *s, void *element);


/*
 * Returns a pointer to the top element of
 * the stack. Returns NULL pointer is the
 * stack is empty
 */
void *top(struct Stack *s);


/**
 * Return a pointer to the top element
 * of the stack and removes it
 */
void *pop(struct Stack *s);


/*
 * Frees the stack structure with its content
 * After calling freestack, the behavious of
 * the functions will be undefined
 */
void freestack(struct Stack *s);

#endif

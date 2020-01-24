#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#define init_length 16

static void push(struct stack *this, long int pos)
{
	if (this->index < this->length) {
		this->base[++(this->index)] = pos;
		return;
	}
	this->base = (long int *)realloc(this->base, sizeof(long int) * (this->length *= 2));
	assert(this->base != (void *)0);
	this->base[++(this->index)] = pos;
}

static void pop(struct stack *this)
{
	if (this->index >= 0) {
		--(this->index);
	}
}

static long int top(struct stack *this)
{
	assert(this->index >= 0);
	return this->base[this->index];
}

static long int size(struct stack *this)
{
	return this->index + 1;
}

void init_stack(stack_t *stack)
{
	if (stack == (void *)0) {
		return;
	}
	if ((*stack = (struct stack *)calloc(1, sizeof(struct stack))) == (void *)0) {
		return;
	}
	if (((*stack)->base = malloc(init_length * sizeof(long int))) == (void *)0) {
		free(*stack);
		return;
	}
	(*stack)->index = -1;
	(*stack)->length = init_length;
	(*stack)->push = push;
	(*stack)->pop = pop;
	(*stack)->top = top;
	(*stack)->size = size;
}

void close_stack(stack_t stack)
{
	free(stack->base);
	free(stack);
}

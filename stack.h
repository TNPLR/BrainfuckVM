#ifndef STACK_H_
#define STACK_H_
typedef struct stack{
	long int index;
	long int length;
	long int *base;
	void (*push)(struct stack *this, long int pos);
	void (*pop)(struct stack *this);
	long int (*top)(struct stack *this);
	long int (*size)(struct stack *this);
} *stack_t;
void init_stack(stack_t * stack);
void close_stack(stack_t stack);
#endif /* STACK_H_ */

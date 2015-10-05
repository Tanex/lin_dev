#include "global.h"

struct stack calc_stack;

int power(int base, int exp);

void stack_init()
{
	calc_stack.top_free = 0;
}

int stack_pop()
{
	if (calc_stack.top_free == 0)
		error("Error: stack_pop(): stack is empty...");
	return calc_stack.stack_array[--calc_stack.top_free];	
}

void stack_push(int value)
{
	if (calc_stack.top_free == STACK_SIZE)
		error("Error: stack_push(): stack is full");
	calc_stack.stack_array[calc_stack.top_free++] = value;
}

void stack_operator(int oper)
{
	int r_op = stack_pop();
	int l_op = stack_pop();

	switch (oper)
	{
	case '+': stack_push(l_op + r_op); break;
	case '-': stack_push(l_op - r_op); break;
	case '*': stack_push(l_op * r_op); break;
	case '/': stack_push(l_op / r_op); break;
	case '^': stack_push(power(l_op, r_op)); break;
	case DIV: stack_push(div(l_op, r_op).quot); break;
	case MOD: stack_push(l_op % r_op); break;

	default: error("Invalid operator passed to stack_operator();"); break;
	}
}

int power(int base, int exp)
{
	if (exp < 0)
		return 0;
	int sum = 1;
	for(int i = 0; i < exp; i++)
	{
		sum *= base;
	}
	return sum;
}


#include "stack.h"
#include <stdio.h>

int mystack::count = 0;
int mystack::getcount()
{	
	return count;
}

mystack::mystack(int size) : max_size(2048), top(0), data(0)
{
	// max_size = 2048;
	data = new int[size];
	
	init();
	count++;
}
mystack::~mystack()
{
	if(data)
		delete[] data;
	count--;
}

void mystack::init()
{
	top = 0;
}

int mystack::isempty()
{
	return top == 0;
}

void mystack::push(int value)
{
	this->data[this->top++] = value;
	printf("in mystack::push, this = %p\n", this);
}

int mystack::pop()
{
	return data[--top];
}

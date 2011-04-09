#include <iostream>
#include <stdio.h>
#include "stack.h"
using namespace std;

int main(int argc, char* argv[])
{
	mystack s;
	s << 10 << 8 << 6;
	int a;
	s >> a;
	cout << a << endl;
	s >> a;
	cout << a << endl;
	s >> a;
	cout << a << endl;
	return 0;
}

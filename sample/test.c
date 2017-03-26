#include<stdio.h>
#include "test.h"

int Add(int a, int b)
{
	return a+b;
}

int main()
{
	int a=10;
	int b=20;
	int c = Add(a,b);
	printf("a + b = %d\n",c);
	max(a, b);
	printf("hello world!\n");
	return 0;
}

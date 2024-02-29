#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int** a;
	a = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		a[i] = new int[5]{0,0,0,0,0};
	}

	for (int i = 0; i < 5; i++)
	{
		delete[] a[i];
	}
	delete[]a;
}
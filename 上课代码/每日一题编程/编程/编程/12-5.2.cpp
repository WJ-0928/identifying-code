#if 0
#include<iostream>
using namespace std;
#define N 3.14
bool cat(double n, double r)
{
	double C = 2 * N*r;
	if (C >= n)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	double n, r;
	while (cin >> n >> r)
	{
		if (cat(n, r) == 1)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
}
#endif

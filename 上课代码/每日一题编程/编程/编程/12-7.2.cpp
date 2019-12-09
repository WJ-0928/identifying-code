#if 0
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		if (n == 0)
			break;
		else
		{
			cout << pow(5, n) - 4 << " " << pow(4, n) + n - 4 << endl;
		}
	}
	return 0;
}
#endif
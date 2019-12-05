#if 0
#include<iostream>
#include<string>
using namespace std;
int number(int n)
{
	if (n < 10)
	{
		return n;
	}
	int sum = 0;
	while (n > 0)
	{
		sum += n % 10;
		n /= 10;
	}
	if (sum >= 10)
	{
		sum = number(sum);
	}
	return sum;
	
}
int main()
{
	string n;
	while (cin >> n)
	{
		int sum = 0;
		for (auto& c : n)
		{
			sum += c - '0';
		}
		cout << number(sum) << endl;
	}
}
#endif

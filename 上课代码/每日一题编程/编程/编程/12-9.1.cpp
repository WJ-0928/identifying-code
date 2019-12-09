#if 0
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string s;
	while (getline(cin, s))
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				cout << str[(int(s[i]) - 65 - 5 + 26) % 26];
			}
			else
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
	return 0;
}
#endif

#include <iostream>
using namespace std;
#include <algorithm>
bool IsPrime(int n)
{
	for (int i = 2; i<n; i++)
	{
		if (i % 2 == 0)
			return false;
	}
	return true;
}
int main()
{
	int num;
	int i;
	int x;
	int y;
	while (cin >> num)
	{
		for (i = 1; i <= num / 2; i++)
		{
			if (IsPrime(i) && IsPrime(num - i))
			{
				x = i;
				y = num - i;
			}
		}
		cout << x << endl;
		cout << y << endl;
	}
	return 0;
}
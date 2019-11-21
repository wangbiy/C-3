#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INT_MAX 100001
int main()
{
	int n, m;
	while (cin >> n >> m)
	{
		vector<int> dp(m + 1, INT_MAX);
		dp[n] = 0;
		for (int i = n; i <= m; i++)
		{
			for (int j = 2; j*j <= i; j++)
			{
				if (i%j == 0)
				{
					if (i + j <= m)
						dp[i + j] = min(dp[i + j], dp[i] + 1);
					if (i + i / j <= m)
						dp[i + i / j] = min(dp[i + i / j], dp[i] + 1);
				}
			}
		}
		if (dp[m] = INT_MAX)
			cout << "-1" << endl;
		else
			cout << dp[m] << endl;
	}
}
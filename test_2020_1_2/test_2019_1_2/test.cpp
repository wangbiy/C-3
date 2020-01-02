#include <iostream>
using namespace std;
#include <vector>
#include <string>
#define min(a,b) a<b ? a:b
//回文串分割
bool isPal(string& s, int start, int end)
{
	while (start<end)
	{
		if (s[start] != s[end])
		{
			return false;
		}
		start++;
		end--;
	}
	return true;
}
int minCut(string s) {
	int len = s.size();
	vector<int> minSum(len + 1, 0);
	for (int i = 1; i <= len; ++i)
	{
		minSum[i] = i - 1;//一开始每一个字符都分割，一定是回文串
	}
	for (int i = 1; i <= len; ++i)
	{
		for (int j = 0; j<i; ++j)
		{
			if (isPal(s, 0, i - 1))//整体是回文串
			{
				minSum[i] = 0;
				break;
			}
			if (isPal(s, j, i - 1))
			{
				minSum[i] = min(minSum[i], minSum[j] + 1);
			}
		}
	}
	return minSum[len];
}
int main()
{
	string s = "aab";
	int ret = minCut(s);
	cout << ret << endl;
	return 0;
}
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
int minCut2(string s) 
{
	if (s.empty()) return 0;
	int len = s.size();
	vector<int> cut;
	// F(i)初始化
	// F(0）= -1，必要项，如果没有这一项，对于重叠字符串“aaaaa”会产生错误的结果
	for (int i = 0; i < 1 + len; ++i) {
		cut.push_back(i - 1);
	}
	vector<vector<bool> > mat = getMat(s);
	for (int i = 1; i < 1 + len; ++i) {
		for (int j = 0; j < i; ++j) {
			// F(i) = min{F(i), 1 + F(j)}, where j<i && j+1到i是回文串
			// 从最长串判断，如果从第j+1到i为回文字符串
			// 则再加一次分割，从1到j，j+1到i的字符就全部分成了回文字符串
			if (mat[j][i - 1]) {
				cut[i] = min(cut[i], 1 + cut[j]);
			}
		}
	}
	return cut[len];
}
vector<vector<bool> > getMat(string s) 
{
	int len = s.size();
	vector<vector<bool> > mat = vector<vector<bool> >(len, vector<bool>(len,false));
	for (int i = len - 1; i >= 0; --i) {
		for (int j = i; j < len; ++j) {
			if (j == i) 
			{
				// 单字符为回文字符串
				mat[i][j] = true;
			}
			else if (j == i + 1) 
			{
				// 相邻字符如果相同，则为回文字符串
				mat[i][j] = (s[i] == s[j]);
			}
			else 
			{
				// F(i,j) = {s[i]==s[j] && F(i+1,j-1)
				// j > i+1
				mat[i][j] = ((s[i] == s[j]) && mat[i + 1][j - 1]);
			}
		}
	}
	return mat;
}
int main()
{
	string s = "aab";
	int ret = minCut(s);
	cout << ret << endl;
	int ret = minCut2(s);
	cout << ret << endl;
	return 0;
}
#include <iostream>
using namespace std;
#include <vector>
#include <string>
#define min(a,b) a<b ? a:b
//���Ĵ��ָ�
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
		minSum[i] = i - 1;//һ��ʼÿһ���ַ����ָһ���ǻ��Ĵ�
	}
	for (int i = 1; i <= len; ++i)
	{
		for (int j = 0; j<i; ++j)
		{
			if (isPal(s, 0, i - 1))//�����ǻ��Ĵ�
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
	// F(i)��ʼ��
	// F(0��= -1����Ҫ����û����һ������ص��ַ�����aaaaa�����������Ľ��
	for (int i = 0; i < 1 + len; ++i) {
		cut.push_back(i - 1);
	}
	vector<vector<bool> > mat = getMat(s);
	for (int i = 1; i < 1 + len; ++i) {
		for (int j = 0; j < i; ++j) {
			// F(i) = min{F(i), 1 + F(j)}, where j<i && j+1��i�ǻ��Ĵ�
			// ������жϣ�����ӵ�j+1��iΪ�����ַ���
			// ���ټ�һ�ηָ��1��j��j+1��i���ַ���ȫ���ֳ��˻����ַ���
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
				// ���ַ�Ϊ�����ַ���
				mat[i][j] = true;
			}
			else if (j == i + 1) 
			{
				// �����ַ������ͬ����Ϊ�����ַ���
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
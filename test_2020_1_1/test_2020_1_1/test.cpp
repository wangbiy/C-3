#include <iostream>
using namespace std;
#include <vector>
#define max(x,y) x>y ? x:y
//背包问题
int backPackII(int m, vector<int> A, vector<int> V) 
{
	if (A.empty() || V.empty() || m < 1)
		return 0;
	int N = A.size() + 1;
	int M = m + 1;
	vector<vector<int>> ret;//用来保存重量和价值
	ret.resize(N);
	for (int i = 0; i < N; ++i)
	{
		ret[i].resize(M);
	}
	for (int i = 1; i < N; ++i)
	{
		for (int j = 1; j < M; ++j)
		{
			if (A[i - 1]>j)//如果背包已经满了
			{
				ret[i][j] = ret[i - 1][j];
			}
			//说明背包可以装下
			else
			{
				int tmp = ret[i - 1][j - A[i - 1]] + V[i - 1];//第i个商品对应的下标是i-1
				ret[i][j] = max(tmp, ret[i - 1][j]);
			}
		}
	}
	return ret[N - 1][m];
}
//保存结果的数组优化为一维数组
int backPackII2(int m, vector<int> A, vector<int> V)
{
	if (A.empty() || V.empty() || m < 1)
		return 0;
	vector<int> result;
	int N = A.size();
	int M = m + 1;
	result.resize(M, 0);
	//这里的i-1理解为上一行，因此从0开始
	for (int i = 0; i < N; ++i)//i表示每一行
	{
		for (int j = M - 1; j > 0; --j)//j表示遍历当前行的每一列
		{
			if (A[i] > j)
				result[j] = result[j];
			else
			{
				int tmp = result[j - A[i]] + V[i];
				result[j] = max(tmp, result[j]);
			}
		}
	}
	return result[m];
}
int main()
{
	vector<int> A{ 1, 10, 5, 2, 1 };
	vector<int> V{ 1, 10, 2, 5, 3 };
	int ret = backPackII(14, A, V);
	cout << ret << endl;

	ret = backPackII2(14, A, V);
	cout << ret << endl;	
	return 0;
}
#include <iostream>
using namespace std;
#include <vector>
#define max(x,y) x>y ? x:y
//��������
int backPackII(int m, vector<int> A, vector<int> V) 
{
	if (A.empty() || V.empty() || m < 1)
		return 0;
	int N = A.size() + 1;
	int M = m + 1;
	vector<vector<int>> ret;//�������������ͼ�ֵ
	ret.resize(N);
	for (int i = 0; i < N; ++i)
	{
		ret[i].resize(M);
	}
	for (int i = 1; i < N; ++i)
	{
		for (int j = 1; j < M; ++j)
		{
			if (A[i - 1]>j)//��������Ѿ�����
			{
				ret[i][j] = ret[i - 1][j];
			}
			//˵����������װ��
			else
			{
				int tmp = ret[i - 1][j - A[i - 1]] + V[i - 1];//��i����Ʒ��Ӧ���±���i-1
				ret[i][j] = max(tmp, ret[i - 1][j]);
			}
		}
	}
	return ret[N - 1][m];
}
//�������������Ż�Ϊһά����
int backPackII2(int m, vector<int> A, vector<int> V)
{
	if (A.empty() || V.empty() || m < 1)
		return 0;
	vector<int> result;
	int N = A.size();
	int M = m + 1;
	result.resize(M, 0);
	//�����i-1���Ϊ��һ�У���˴�0��ʼ
	for (int i = 0; i < N; ++i)//i��ʾÿһ��
	{
		for (int j = M - 1; j > 0; --j)//j��ʾ������ǰ�е�ÿһ��
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
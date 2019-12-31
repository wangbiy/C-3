#include <iostream>
using namespace std;
#include <vector>
//求左上角到右下角的路径总数
int uniquePaths(int m, int n) 
{
	if (m<1 || n<1)
		return 0;
	vector<vector<int>> arr(m, vector<int>(n, 1));
	for (int i = 1; i<m; ++i)
	{
		for (int j = 1; j<n; ++j)
		{
			arr[i][j] = arr[i][j - 1] + arr[i - 1][j];
		}
	}
	return arr[m - 1][n - 1];
}
//加上障碍
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
	if (obstacleGrid.empty() || obstacleGrid[0].empty())
		return 0;
	int row = obstacleGrid.size();
	int col = obstacleGrid[0].size();
	vector<vector<int>> ret(row, vector<int>(col, 0));
	for (int i = 0; i<row; ++i)//考虑第一列的情况
	{
		if (obstacleGrid[i][0] == 1)
			break;
		else
			ret[i][0] = 1;
	}
	for (int i = 0; i<col; ++i)//考虑第一行的情况
	{
		if (obstacleGrid[0][i] == 1)
			break;
		else
			ret[0][i] = 1;
	}
	for (int i = 1; i<row; ++i)
	{
		for (int j = 1; j<col; ++j)
		{
			if (obstacleGrid[i][j] == 1)
				ret[i][j] = 0;
			else
				ret[i][j] = ret[i][j - 1] + ret[i - 1][j];
		}
	}
	return ret[row - 1][col - 1];
}
//最短路径
#include <functional>
#define min(x,y) x<y ? x:y
int minPathSum(vector<vector<int> > &grid) 
{
	if (grid.empty() || grid[0].empty())
		return 0;
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> ret(m, vector<int>(n, 0));
	ret[0][0] = grid[0][0];
	for (int i = 1; i<m; ++i)//第一列
	{
		ret[i][0] = ret[i - 1][0] + grid[i][0];
	}
	for (int i = 1; i<n; ++i)
	{
		ret[0][i] = ret[0][i - 1] + grid[0][i];
	}
	for (int i = 1; i<m; ++i)
	{
		for (int j = 1; j<n; ++j)
		{
			ret[i][j] = min(ret[i - 1][j], ret[i][j - 1]) + grid[i][j];
		}
	}
	return ret[m - 1][n - 1];
}
int main()
{
	int m = 10;
	int n = 10;
	int ret = uniquePaths(m, n);
	cout << ret << endl;
	vector<vector<int>> arr(m, vector<int>(n, 0));
	ret = uniquePathsWithObstacles(arr);
	cout << ret << endl;
	vector<vector<int>> grid{{ 1, 4, 5 }, { 2, 7, 8 }, { 3, 9, 0 }};
	ret = minPathSum(grid);
	cout << ret << endl;
	return 0;
}
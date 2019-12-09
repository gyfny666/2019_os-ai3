#include<iostream>
using namespace std;
const int N = 100;
int n, w;
int W[N], V[N];
int max(int a, int b)
{
	return a > b ? a : b;
}
//从第i个物品开始挑选总重小于j的部分
int solve(int i, int j)
{
	int res;
	if (i == n)//已经没有剩余的物品了
		res = 0;
	else if (j < W[i])
		res = solve(i + 1, j);
	else
	{
		res = max(solve(i + 1, j), solve(i + 1, j - W[i]) + V[i]);//一个物品选还是不选都试一下
	}
	return res;
}
int main()
{
	cin >> n >> w;
	for (int i = 0; i < n; i++)
		cin >> W[i];
	for (int i = 0; i < n; i++)
		cin >> V[i];
	cout << solve(0, w) << endl;
	return 0;
}

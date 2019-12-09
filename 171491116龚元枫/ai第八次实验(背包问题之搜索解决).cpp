#include<iostream>
using namespace std;
const int N = 100;
int n, w;
int W[N], V[N];
int max(int a, int b)
{
	return a > b ? a : b;
}
//�ӵ�i����Ʒ��ʼ��ѡ����С��j�Ĳ���
int solve(int i, int j)
{
	int res;
	if (i == n)//�Ѿ�û��ʣ�����Ʒ��
		res = 0;
	else if (j < W[i])
		res = solve(i + 1, j);
	else
	{
		res = max(solve(i + 1, j), solve(i + 1, j - W[i]) + V[i]);//һ����Ʒѡ���ǲ�ѡ����һ��
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

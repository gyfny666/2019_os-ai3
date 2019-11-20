#include<stdio.h>
#include<string.h>
#define INF 0x3f3f3f3f
int mp[1010][1010],dis[1010],book[1010],n,m;
void dijkstra()
{
	for(int i=1;i<=n;i++)
	{
		dis[i]=mp[1][i];
	}
	for(int i=1;i<=n-1;i++)//找n-1轮 
	{
		int minn=INF,u;
		for(int j=1;j<=n;j++)//找与上一个点最近的点 
		{
			if(book[j]==0&&dis[j]<minn)
			{
				minn=dis[j];
				u=j;
			}
		}
		book[u]=1;
		for(int j=1;j<=n;j++)//找着最近的点后通过这个最近的点更新其余的点到起点的距离 
		{
			if(book[j]==0&&dis[u]+mp[u][j]<dis[j])//book[j]==0和dis[j]<INF看心情写吧= = 
			{
				dis[j]=dis[u]+mp[u][j];
			}
		}
	}
	printf("%d\n",dis[n]);
}
 
int main()
{
	while(~scanf("%d%d",&n,&m)&&n+m)
	{
		for(int i=1;i<=n;i++)//下标从0还是1开始由题目的标号决定 
		{
			for(int j=1;j<=n;j++)//如果是0建议都从0开始计数,是1则1 
			{
				if(i==j) mp[i][j]=0;
				else mp[i][j]=INF;
			}
		}
		memset(book,0,sizeof(book));
		
		int u,v,w;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			if(w<mp[u][v]) mp[u][v]=mp[v][u]=w;
		}
		dijkstra();//这道题固定起点为1,也可在函数里自定义起点 
	}
	return 0;
}

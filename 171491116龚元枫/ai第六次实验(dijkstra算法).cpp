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
	for(int i=1;i<=n-1;i++)//��n-1�� 
	{
		int minn=INF,u;
		for(int j=1;j<=n;j++)//������һ��������ĵ� 
		{
			if(book[j]==0&&dis[j]<minn)
			{
				minn=dis[j];
				u=j;
			}
		}
		book[u]=1;
		for(int j=1;j<=n;j++)//��������ĵ��ͨ���������ĵ��������ĵ㵽���ľ��� 
		{
			if(book[j]==0&&dis[u]+mp[u][j]<dis[j])//book[j]==0��dis[j]<INF������д��= = 
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
		for(int i=1;i<=n;i++)//�±��0����1��ʼ����Ŀ�ı�ž��� 
		{
			for(int j=1;j<=n;j++)//�����0���鶼��0��ʼ����,��1��1 
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
		dijkstra();//�����̶����Ϊ1,Ҳ���ں������Զ������ 
	}
	return 0;
}

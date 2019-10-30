#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
int k;
int flag;
char s[10][10];
int a[10][10];
int dx[10]={1,2,1,2,-1,-2,-1,-2};
int dy[10]={2,1,-2,-1,-2,-1,2,1};
int ans[10][10]={{1,1,1,1,1},{0,1,1,1,1},{0,0,-1,1,1},{0,0,0,0,1},{0,0,0,0,0}};
//1表示黑，0表示白 
bool judge()
{
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++){
			if(a[i][j]!=ans[i][j])
				return 0;
		}
	return 1;
}
bool check(int t)
{
	int m=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++){
			if(a[i][j]!=ans[i][j]){
				m++;
				if(m+t>k) return 0;
			}
		}
	return 1;
}
void Astar(int t,int x,int y)
{
	if(t==k){
		if(judge())	flag=1;
		return ;
	}
	if(flag)
		return;
	int xx,yy;
	for(int i=0;i<8;i++){
		xx=x+dx[i];
		yy=y+dy[i];
		if(xx<0||xx>4||yy<0||yy>4)
			continue;
		swap(a[xx][yy],a[x][y]);
		if(check(t)) Astar(t+1,xx,yy);
		swap(a[xx][yy],a[x][y]);
	}		
}
int main()
{
	int t;
	scanf("%d",&t);	
	while(t--){
		for(int i=0;i<5;i++)
			scanf("%s",s[i]);
		int x,y;
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++){
				if(s[i][j]=='1')
					a[i][j]=1;
					else if(s[i][j]=='0')
						a[i][j]=0;
						else
							a[i][j]=-1;//表示这个位置是空着的 
			}			
		for(x=0;x<5;x++){
			for(y=0;y<5;y++)
				if(s[x][y]=='*')
					break;//这里找到空格的初始位置 		
			if(s[x][y]=='*')
				break;	
		}
		flag=0;
		for(k=0;k<=15;k++){
			Astar(0,x,y);
			if(flag){
				printf("%d\n",k);
				break;
			}	
		}
		if(!flag)
			printf("-1\n");
	}
	return 0;
}
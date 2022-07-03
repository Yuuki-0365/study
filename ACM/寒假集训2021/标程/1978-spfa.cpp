#include<cstdio>
#include<cstring>
#include<cmath>
#define maxl 1010
#define eps 1e-8

int n,m;
int a[maxl],ehead[maxl],num[maxl];
double mul[maxl],dis[maxl];
double w[maxl][maxl];
struct ed{int to,nxt;} e[maxl*maxl];
bool yes;
bool vis[maxl],in[maxl];

void prework()
{
	memset(ehead,0,sizeof(ehead));
	memset(vis,false,sizeof(vis));
	int u,v;double l;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			w[i][j]=100;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&u,&v,&l);
		if(log2(l)<w[u][v]-eps)
			w[u][v]=log2(l);
		e[i].to=v;e[i].nxt=ehead[u];ehead[u]=i;
	}
}

void spfa(int s)
{
	int head=0,tail=1,u,v;
	for(int i=1;i<=n;i++)
		dis[i]=2000000000,num[i]=0;
	a[1]=s;in[s]=true;num[s]=1;dis[s]=0;
	while(head!=tail)
	{
		head++;head%=maxl;
		u=a[head];vis[u]=true;in[u]=false;
		for(int i=ehead[u];i>0;i=e[i].nxt)
		{
			v=e[i].to;
			if(dis[u]+w[u][v]<dis[v])
			{
				dis[v]=dis[u]+w[u][v];
				if(!in[v])
				{
					in[v]=true;num[v]++;
					if(num[v]>n)
					{
						yes=true;
						return;
					}
					tail++;tail%=maxl;
					a[tail]=v;
				}
			}
		}
	}
}

void mainwork()
{
	yes=false;
	for(int i=1;i<=n && !yes;i++)
	if(!vis[i])
		spfa(i);
}

void print()
{
	if(yes)
		printf("YES\n");
	else
		printf("NO\n");
}

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		prework();
		mainwork();
		print();
	}
	return 0;
}
/**********************************************************************
	Problem: 1978
	User: liufengwei
	Language: C++
	Result: AC
	Time:316 ms
	Memory:17100 kb
**********************************************************************/


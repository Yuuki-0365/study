#include<cstdio>
#include<cstring>
#define maxl 1010
#define eps 1e-7

int n,m;
int a[maxl],in[maxl],ehead[maxl];
double mul[maxl];
double w[maxl][maxl];
struct ed{int to,nxt;} e[maxl*maxl];
bool yes;
bool vis[maxl],vise[maxl*maxl];

void prework()
{
	memset(ehead,0,sizeof(ehead));
	memset(vis,false,sizeof(vis));
	memset(in,0,sizeof(in));
	memset(vise,false,sizeof(vise));
	int u,v;double l;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			w[i][j]=100;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&u,&v,&l);
		if(l<w[u][v]-eps)
			w[u][v]=l;
		e[i].to=v;e[i].nxt=ehead[u];ehead[u]=i;
	}
}

void dfs(int k,int u)
{
	int v;double d,t;vis[u]=true;
	for(int i=ehead[u];i>0 && !yes;i=e[i].nxt)
	if(!vise[i])
	{
		v=e[i].to;d=mul[k-1]*w[u][v];
		vise[i]=true;
		if(in[v])
		{
			t=d/mul[in[v]];
			if(t<1-eps)
			{
				yes=true;
				return;
			}
		}
		a[k]=v;in[v]=k;mul[k]=d;
		dfs(k+1,v);
		a[k]=0;in[v]=0;mul[k]=0;
	}
	
}

void mainwork()
{
	yes=false;mul[0]=1;
	for(int i=1;i<=n;i++)
	if(!vis[i])
	{
		a[1]=i;in[i]=1;mul[1]=1;
		dfs(2,i);
		a[1]=0;in[i]=0;mul[1]=0;
	}
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
	Problem: 1167
	User: summerteam100
	Language: C++
	Result: AC
	Time:88 ms
	Memory:18072 kb
**********************************************************************/


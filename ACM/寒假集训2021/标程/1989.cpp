#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 10010
#define maxl 50010
#define inf 2000000001

using namespace std;

int n,m,st,en,maxw,cnt,ans;
long long resl;
int ehead[maxn],w[maxn];
long long dis[maxn];
struct ed{int to,nxt;long long l;} e[maxl<<1];
typedef pair<long long,int> node;
priority_queue<node,vector<node>,greater<node> > q;
bool in[maxn];

inline int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}

inline int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

void prework()
{
	int u,v;long long l;
	st=read(),en=read(),resl=read();
	maxw=0;
	for(int i=1;i<=n;i++)
	{
		w[i]=read();
		maxw=max(maxw,w[i]);
		ehead[i]=0;
	}
	cnt=0;
	for(int i=1;i<=m;i++)
	{
		u=read();v=read();l=read();
		e[++cnt].to=v;e[cnt].nxt=ehead[u];e[cnt].l=l;ehead[u]=cnt;
		e[++cnt].to=u;e[cnt].nxt=ehead[v];e[cnt].l=l;ehead[v]=cnt;
	}
}

bool dij(int mid)
{
	int u,v;node d;
	while(!q.empty())
		q.pop();
	for(int i=1;i<=n;i++)
		dis[i]=inf,in[i]=false;
	dis[st]=0;q.push(make_pair(0,st));
	while(!q.empty())
	{
		do
		{
			d=q.top();q.pop();
			u=d.second;
		}while((dis[u]<d.first || in[u]) && !q.empty());
		in[u]=true;
		for(int i=ehead[u];i;i=e[i].nxt)
		{
			v=e[i].to;
			if(w[v]<=mid && dis[v]>dis[u]+e[i].l && dis[u]+e[i].l<=resl)
			{
				dis[v]=dis[u]+e[i].l;
				q.push(make_pair(dis[v],v));
			}
		}
	}
	if(dis[en]<=resl)
		return true;
	else
		return false;
}

void mainwork()
{
	int l=max(w[st],w[en]),r=maxw+5,mid;
	while(l+1<r)
	{
		mid=(l+r)>>1;
		if(dij(mid))
			r=mid;
		else
			l=mid;
	}
	if(l>maxw)
		ans=-1;
	else
		if(dij(l))
			ans=l;
		else
			ans=l+1;
}

void print()
{
	printf("%d\n",ans);
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
	Problem: 1989
	User: liufengwei
	Language: C++
	Result: AC
	Time:368 ms
	Memory:2904 kb
**********************************************************************/


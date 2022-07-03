#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxl 200010

using namespace std;

int n,m;
int ans[maxl],b[maxl];
struct num
{
	int ind,x;
}a[maxl];
struct node
{
	int l,r,sum,tag;
}tree[maxl<<2];
struct que
{
	int ind,l,r,x;
}q[maxl];

inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

bool cmp1(const num &x,const num &y)
{
	return x.x<y.x;
}

bool cmp2(const que &x,const que &y)
{
	return x.x<y.x;
}

void prework()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].ind=i,b[i]=0;
	sort(a+1,a+1+n,cmp1);
	for(int i=1;i<=m;i++)
	{
		q[i].l=read();q[i].r=read();
		q[i].x=read();q[i].ind=i;
	}
	sort(q+1,q+1+m,cmp2);
}

void add(int i,int x)
{
	while(i<=n)
	{
		b[i]+=x;
		i+=i&-i;
	}
}

int sum(int i)
{
	int s=0;
	while(i)
	{
		s+=b[i];
		i-=i&-i;
	}
	return s;
}

void mainwork()
{
	int at=0;
	for(int i=1;i<=m;i++)
	{
		while(at<n && a[at+1].x<q[i].x)
			at++,add(a[at].ind,1);
		ans[q[i].ind]=sum(q[i].r)-sum(q[i].l-1);
	}
}

void print()
{
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
}

int main()
{
	int t;
	t=read();
	for(int i=1;i<=t;i++)
	{
		prework();
		mainwork();
		print();
	}
	return 0;
}

/**********************************************************************
	Problem: 1981
	User: liufengwei
	Language: C++
	Result: AC
	Time:620 ms
	Memory:19872 kb
**********************************************************************/


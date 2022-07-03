#include<bits/stdc++.h>
#define maxl 100010
using namespace std;
 
int n,m,mxk;
int a[maxl],b[maxl],f[maxl],ans[maxl];
int bit[maxl];
int nxt[maxl],pre[maxl];
 
inline void add(int i,int x)
{
	while(i<=n)
	{
		bit[i]+=x;
		i+=i&-i;
	}
}
 
inline int sum(int i)
{
	int ret=0;
	while(i)
	{
		ret+=bit[i];
		i-=i&-i;
	}
	return ret;
}
 
inline void prework()
{
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),bit[i]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	mxk=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=b[n-i+1])
		{
			mxk=i-1;
			break;
		}
		else
			mxk=i;
	}
	int id=1;
	for(int i=1;i<=n;i++)
	{
		while(a[id]>=b[i] && id<=n)
			id++;
		if(id>n)
			f[i]=maxl-1;
		else
		{
			if(id>=i)
				f[i]=id-i+1;
			else
				f[i]=1;
			add(f[i],1);
		}
	}
	id=1;
	for(int i=1;i<=mxk;i++)
	{
		while(b[id]>=a[i] && id<=n)
			id++;
		nxt[i]=id;
	}
	id=n;
	for(int i=1;i<=mxk;i++)
	{
		while(a[i]<=b[n-i+1] && id>0)
			id--;
		pre[n-i+1]=id;
	}
}
 
inline void mainwork()
{
	ans[0]=sum(1);int l=1,r=n,lastl,lastr,num=1;
	for(int i=1;i<=mxk;i++)
	{
		lastl=l;lastr=r;
		l=nxt[i];r=pre[n-i+1]-i-i;
		if(l>r)
		{
			mxk=i-1;
			return;
		}
		for(int j=lastl;j<l;j++)
		{
			if(f[j]>0 && f[j]<maxl-1)
				add(f[j],-1);
		}
		for(int j=lastr;j>r;j--)
		{
			if(f[j]>=0 && f[j]<maxl-1)
				add(f[j],-1);
		}
		num+=2;
		ans[i]=n-(r-l+1)+sum(num);
	}
}
 
inline void print()
{
	int k;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&k);
		if(k>mxk)
			printf("%d\n",n);
		else
			printf("%d\n",ans[k]);
	}
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
	Problem: 2000
	User: liufengwei
	Language: C++
	Result: AC
	Time:532 ms
	Memory:4756 kb
**********************************************************************/

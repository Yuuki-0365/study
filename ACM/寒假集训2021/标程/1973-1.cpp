#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxl 101

using namespace std;

int n,r,ans;
int a[maxl],b[maxl];
bool yes;

bool cmp(const int &x,const int &y)
{
	return x>y;
}

void prework()
{
	ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
}

void dfs(int last,int k,int len)
{
	r=n-(len-k);
	for(int i=last+1;i<=r;i++)
	{
		if(k==1)
		{
			b[++b[0]]=a[i];
			dfs(i,k+1,len);
			b[b[0]--]=0;
		}
		else
		if(k==len)
		{
			if(b[k-1]-a[i]>len)
				ans++,yes=true;
		}
		else
		if(b[k-1]-a[i]>len)
		{
			b[++b[0]]=a[i];
			dfs(i,k+1,len);
			b[b[0]--]=0;
		}
	}
}

void mainwork()
{
	int rr;
	for(int i=2;i<=n;i++)
	{
		yes=false;rr=n-i+1;
		for(int j=1;j<=rr;j++)
		{
			memset(b,0,sizeof(b));
			b[1]=a[j];b[0]=1;
			dfs(j,2,i);
		}
		if(!yes)
			return;
	}	
}

void print()
{
	printf("%d\n",ans);
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		prework();
		mainwork();
		print();
	}
	return 0;
}
/**********************************************************************
	Problem: 1973
	User: liufengwei
	Language: C++
	Result: AC
	Time:228 ms
	Memory:1120 kb
**********************************************************************/


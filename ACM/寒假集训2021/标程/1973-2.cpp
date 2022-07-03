#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxl 101

using namespace std;

int n,ans;
int a[maxl];
int f[maxl][maxl][maxl];

void prework()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	memset(f,0,sizeof(f));
}

void mainwork()
{
	for(int i=1;i<=n;i++)
		for(int k=1;k<=n;k++)
			f[i][1][k]=1;
	for(int k=1;k<=n;k++)
		for(int j=2;j<=n;j++)
			for(int i=j;i<=n;i++)
				for(int l=i-1;l>=1;l--)
				if(a[i]-a[l]>k)
					f[i][j][k]+=f[l][j-1][k];
}

void print()
{
	ans=0;
	for(int i=1;i<=n;i++)
		for(int k=2;k<=n;k++)
			ans+=f[i][k][k];
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
	Time:32 ms
	Memory:5144 kb
**********************************************************************/


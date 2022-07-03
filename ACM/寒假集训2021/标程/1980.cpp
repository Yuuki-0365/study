#include<cstdio>
#include<cstring>
#define maxl 210

int n;
int a[maxl];
long long w[maxl],sum[maxl];
long long f[maxl][maxl];

void prework()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&w[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),sum[i]=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+w[a[i]];
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
		f[i][i]=w[a[i]];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			f[i][j]=-1;
}

void mainwork()
{
	int j;long long tmp;
	for(int len=1;len<=n-1;len++)
		for(int i=1;i<=n-len;i++)
		{
			j=i+len;
			for(int k=i;k<=j;k++)
			{
				tmp=f[i][k-1]+f[k+1][j]+sum[j]-sum[i-1];
				if(f[i][j]==-1)
					f[i][j]=tmp;
				else
					if(f[i][j]>tmp)
						f[i][j]=tmp;
			}
		}
}

void print()
{
	printf("%lld\n",f[1][n]);
}

int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		prework();
		mainwork();
		print();
	}
	return 0;
}
/**********************************************************************
	Problem: 1980
	User: liufengwei
	Language: C++
	Result: AC
	Time:196 ms
	Memory:1464 kb
**********************************************************************/


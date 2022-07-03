#include<cstdio>
#include<cstring>
#include<cmath>
#define maxl 110

using namespace std;

int n,maxf,ans,ansf;
int a[maxl],sum[maxl];
int f[maxl][maxl],dec[maxl][maxl];

inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

void prework()
{
	memset(f,127,sizeof(f));
	for(int i=1;i<=n;i++)
		a[i]=read();
	memset(dec,0,sizeof(dec));
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			sum[i]+=2*abs(a[j]-a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int l=i+1;l<=j-1;l++)
				dec[i][j]+=abs(2*a[l]-a[i]-a[j]);
}

inline int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}

void mainwork()
{
	for(int i=1;i<=n;i++)
	{
		f[1][i]=0;
		for(int j=1;j<i;j++)
			f[1][i]+=2*abs(a[i]-a[j]);
		for(int j=i+1;j<=n;j++)
			f[1][i]+=2*abs(a[i]-a[j]);
	}
	int minf,yf;
	for(int k=2;k<=n;k++)
	{
		minf=f[0][0];
		for(int i=k;i<=n;i++)
			for(int j=k-1;j<i;j++)
			{
				yf=f[k-1][j]-sum[j]+dec[j][i]+sum[i];
				/*for(int l=j+1;l<=n;l++)
					yf-=2*abs(a[l]-a[j]);
				for(int l=j+1;l<i;l++)
					yf+=abs(2*a[l]-a[i]-a[j]);
				for(int l=i+1;l<=n;l++)
					yf+=2*abs(a[l]-a[i]);*/
				if(yf<f[k][i])
					f[k][i]=yf;
				if(yf<minf)
					minf=yf;
			}
		if(minf<=maxf)
		{
			ans=k;ansf=minf;
			break;
		}
	}
}

void print()
{
	printf("%d %d\n",ans,ansf);
}

int main()
{
	while(~scanf("%d%d",&n,&maxf))
	{
		prework();
		mainwork();
		print();
	}
	return 0;
}
/**********************************************************************
	Problem: 1988
	User: liufengwei
	Language: C++
	Result: AC
	Time:148 ms
	Memory:1212 kb
**********************************************************************/


#include<cstdio>
#include<cstring>
#define maxl 50010

long long n;
long long f[maxl],dec[maxl];

int main()
{
	
	for(long long i=1;i<=50000;i++)
		dec[i]=dec[i-1]+i*(i-1);
	for(long long i=4;i<=50000;i++)
	{
		n=i-3;	
		f[i]=f[i-1]+(n+1)*n/2*n-dec[n];
	}
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%lld",&n);
		printf("%lld\n",f[n]);
	}
	return 0;
}
/**********************************************************************
	Problem: 1985
	User: liufengwei
	Language: C++
	Result: AC
	Time:100 ms
	Memory:1896 kb
**********************************************************************/


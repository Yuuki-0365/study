/*
 * NTT做多项式乘法 
 * By Yuekai Jia 
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn (1<<16)
#define P 1004535809 //P=C*2^k+1，P是质数
#define G 3 //P的原根
#define ll long long
using namespace std;

int N,na,nb,a[maxn*2],b[maxn*2],W[2][maxn*2],rev[maxn*2];

ll Pow(ll a,int b)
{
	ll c=1;
	for (;b; b>>=1,a=a*a%P) if (b&1) c=c*a%P;
	return c;
}

void FFT(int*a,int f)
{
	for (int i=0; i<N; i++) if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int i=1; i<N; i<<=1)
		for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
			for (int k=0,l=0,x,y; k<i; k++,l+=t) x=(ll)W[f][l]*a[j+k+i]%P,y=a[j+k],a[j+k]=(y+x)%P,a[j+k+i]=(y-x+P)%P;
	if (f) for (int i=0,x=Pow(N,P-2); i<N; i++) a[i]=(ll)a[i]*x%P;
}

void work()
{
	for (int i=0; i<N; i++)
	{
		int x=i,y=0;
		for (int k=1; k<N; x>>=1,k<<=1) (y<<=1)|=x&1;
		rev[i]=y;
	}
	W[0][0]=W[1][0]=1;
	for (int i=1,x=Pow(G,(P-1)/N),y=Pow(x,P-2); i<N; i++) W[0][i]=(ll)x*W[0][i-1]%P,W[1][i]=(ll)y*W[1][i-1]%P;
}

void init()
{
	scanf("%d",&na); for (int i=0; i<na; i++) scanf("%d",&a[i]);
	scanf("%d",&nb); for (int i=0; i<nb; i++) scanf("%d",&b[i]);
	for (N=1; N<na||N<nb; N<<=1); N<<=1;
}

void doit()
{
	work(),FFT(a,0),FFT(b,0);
	for (int i=0; i<N; i++) a[i]=(ll)a[i]*b[i]%P;
	FFT(a,1);
	for (int i=0; i<N; i++) printf("%d\n",a[i]);
}

int main()
{
	init();
	doit();
}

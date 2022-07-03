/*
 * FFT做多项式乘法 
 * By Yuekai Jia 
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn (1<<16)
#define pi 3.141592653589793238462643383
using namespace std;

struct complex
{
	double re,im;
	complex(double r=0.0,double i=0.0) {re=r,im=i;}
	void print() {printf("%lf %lf\n",re,im);}
} a[maxn*2],b[maxn*2],W[2][maxn*2];
int N,na,nb,rev[maxn*2];

complex operator +(const complex&A,const complex&B) {return complex(A.re+B.re,A.im+B.im);}
complex operator -(const complex&A,const complex&B) {return complex(A.re-B.re,A.im-B.im);}
complex operator *(const complex&A,const complex&B) {return complex(A.re*B.re-A.im*B.im,A.re*B.im+A.im*B.re);}

void FFT(complex*a,int f)
{
	complex x,y;
	for (int i=0; i<N; i++) if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int i=1; i<N; i<<=1)
		for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
			for (int k=0,l=0; k<i; k++,l+=t) x=W[f][l]*a[j+k+i],y=a[j+k],a[j+k]=y+x,a[j+k+i]=y-x;
	if (f) for (int i=0; i<N; i++) a[i].re/=N;
}

void work()
{
	for (int i=0; i<N; i++)
	{
		int x=i,y=0;
		for (int k=1; k<N; x>>=1,k<<=1) (y<<=1)|=x&1;
		rev[i]=y;
	}
	for (int i=0; i<N; i++) W[0][i]=W[1][i]=complex(cos(2*pi*i/N),sin(2*pi*i/N)),W[1][i].im=-W[0][i].im;
}

void init()
{
	scanf("%d",&na); for (int i=0; i<na; i++) scanf("%lf",&a[i].re);
	scanf("%d",&nb); for (int i=0; i<nb; i++) scanf("%lf",&b[i].re);
	for (N=1; N<na||N<nb; N<<=1); N<<=1;
}

void doit()
{
	work(),FFT(a,0),FFT(b,0);
	for (int i=0; i<N; i++) a[i]=a[i]*b[i];
	FFT(a,1);
	for (int i=0; i<N; i++) a[i].print();
}

int main()
{
	init();
	doit();
}

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int a[MAXN],b[MAXN],res[MAXN];
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int cnt=0,add=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++)
        {
            if(a[i]<b[i])add++;
            else a[++cnt]=a[i],b[cnt]=b[i];
        }
        n=cnt;
        for(int i=0;i<=n;i++)
            res[i]=0;
        for(int j=n,i=n;j>=1;j--)
        {
            while(i>=1 && a[j]>b[i])i--;
            res[(j-i+1)/2]++;
        }
        for(int i=1;i<=n;i++)
            res[i]+=res[i-1];
        for(int i=1;i<=m;i++)
        {
            int k;
            scanf("%d",&k);
            k=min(k,n);
            printf("%d\n",res[k]+add);
        }
    }
    return 0;
}

/**********************************************************************
	Problem: 2000
	User: quailty
	Language: C++
	Result: AC
	Time:488 ms
	Memory:3196 kb
**********************************************************************/


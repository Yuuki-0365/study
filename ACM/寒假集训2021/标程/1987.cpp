#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxl 10000010

using namespace std;

int n,sz,cas,cnt,ans;
int dis[maxl],val[maxl];
int ch[maxl][3];
char s[maxl];

void prework()
{
	memset(ch,0,sizeof(ch));
	memset(dis,0,sizeof(dis));
	memset(val,0,sizeof(val));
	scanf("%d",&n);
}

void insert()
{
	int len=strlen(s),u=0,v,c;
	for(int i=0;i<len;i++)
	{
		c=s[i]-'0';
		if(!ch[u][c])
		{
			sz++;ch[u][c]=sz;
			dis[sz]=dis[u]+1;
		}
		u=ch[u][c];
		val[u]++;
		if(val[u]*dis[u]>ans)
			ans=val[u]*dis[u];
	}
}

void mainwork()
{
	ans=0;sz=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		insert();
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
	Problem: 1987
	User: liufengwei
	Language: C++
	Result: AC
	Time:2420 ms
	Memory:206192 kb
**********************************************************************/


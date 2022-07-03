#include<cstdio>
#include<cstring>
#define maxl 1001

int ans;
int a[10],cnt[21];
int t[21][3]=
{{0,0,0},{1,1,2},{1,2,3},{1,3,4},{1,4,5},{1,5,6},{1,6,7},{1,7,8},{1,8,9}
 		,{2,2,4},{2,3,5},{2,4,6},{2,5,7},{2,6,8},{2,7,9}
 		,{3,3,6},{3,4,7},{3,5,8},{3,6,9}
 		,{4,4,8},{4,5,9}
};

void prework()
{
	for(int i=1;i<=9;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=20;i++)
	if(t[i][0]==t[i][1])
		cnt[i]=cnt[i-1]+1;
	else
		cnt[i]=cnt[i-1]+2;
}

inline bool jug(int k,int i)
{
	if(t[k][0]==t[k][1] && i>1)
		return false;
	if(t[k][0]!=t[k][1] && i>2)
		return false;
	if(t[k][0]==t[k][1] && a[t[k][0]]<2*i)
		return false;
	if(a[t[k][0]]<i || a[t[k][1]]<i || a[t[k][2]]<i)
		return false;
	return true;
}

void dfs(int k,int sum)
{
	int i=0;
	if(cnt[20]-cnt[k-1]+sum<=ans)
		return;
	while(jug(k,i))
	{
		a[t[k][0]]-=i;a[t[k][1]]-=i;a[t[k][2]]-=i;sum+=i;
		if(k==20)
			ans=sum>ans? sum:ans;
		else
			dfs(k+1,sum);
		a[t[k][0]]+=i;a[t[k][1]]+=i;a[t[k][2]]+=i;sum-=i;
		i++;
	}
}

void mainwork()
{
	ans=0;
	dfs(1,0);
}

void print(int cas)
{
	printf("Case #%d: %d\n",cas,ans);
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		prework();
		mainwork();
		print(i);
	}
	return 0;
}

/**********************************************************************
	Problem: 1343
	User: Scanf
	Language: C++
	Result: AC
	Time:124 ms
	Memory:1120 kb
**********************************************************************/


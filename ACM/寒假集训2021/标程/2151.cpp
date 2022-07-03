#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxl 100010

using namespace std;

int n,m,d,p;
int a[maxl];
struct node{int l,r;long long val,tag1,tag2;int flag1,flag2;} tree[maxl<<2];

inline int read()
{
  int x=0,f=1;char ch=getchar();
  while(ch<'0' || ch>'9') {if(ch=='-') f=-1;ch=getchar();}
  while(ch>='0' && ch<='9') {x=x*10+ch-'0';ch=getchar();}
  return x*f;
}

void build(int k,int l,int r)
{
  tree[k].l=l;tree[k].r=r;
  if(l==r)
    {
      tree[k].val=a[l];
      return;
    }
  int mid=(l+r)>>1;
  build(k<<1,l,mid);
  build(k<<1|1,mid+1,r);
  tree[k].val=tree[k<<1].val+tree[k<<1|1].val;
}

void prework()
{
  int v;
//  freopen("sparta.in","r",stdin);
//  freopen("sparta.out","w",stdout);
  n=read();m=read();v=read();
  for(int i=1;i<=n;i++)
    a[i]=v;
  build(1,1,n);
}

void change(int k)
{
	if(tree[k].flag1)
	{
		tree[k].val+=tree[k].tag1*(tree[k].r-tree[k].l+1);
		if(tree[k<<1].flag2) tree[k<<1].tag2+=tree[k].tag1;
		else tree[k<<1].tag1+=tree[k].tag1,tree[k<<1].flag1=true;
		if(tree[k<<1|1].flag2) tree[k<<1|1].tag2+=tree[k].tag1;
		else tree[k<<1|1].tag1+=tree[k].tag1,tree[k<<1|1].flag1=true;
		tree[k].tag1=0;tree[k].flag1=false;
	}
	if(tree[k].flag2)
	{
		tree[k].val=tree[k].tag2*(tree[k].r-tree[k].l+1);
		tree[k<<1].flag1=tree[k<<1|1].flag2=false;
		tree[k<<1].flag2=tree[k<<1|1].flag2=true;
		tree[k<<1].tag1=tree[k<<1|1].tag2=0;
		tree[k<<1].tag2=tree[k<<1|1].tag2=tree[k].tag2;
		tree[k].tag2=0;tree[k].flag2=false;
	}
}

void add(int k,int type,int l,int r,int x)
{
 	change(k);
	if(tree[k].l==l && r==tree[k].r)
    {
    	if(!type) tree[k].tag1+=x,tree[k].flag1=true;
    	else tree[k].tag2=x,tree[k].flag2=true;
      	return;
    }
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)
    {
    	if(r<=mid)
			add(k<<1,type,l,r,x);
      	else
			add(k<<1,type,l,mid,x),add(k<<1|1,type,mid+1,r,x);
    }
  	else
    	add(k<<1|1,type,l,r,x);
  	change(k<<1);change(k<<1|1);
  	tree[k].val=tree[k<<1].val+tree[k<<1|1].val;
}

long long sum(int k,int l,int r)
{
  	change(k);
	if(tree[k].l==l && r==tree[k].r)
    	return tree[k].val;
	int mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid)
	{
    	if(r<=mid)
			return sum(k<<1,l,r);
    	else
			return sum(k<<1,l,mid)+sum(k<<1|1,mid+1,r);
    }
  	else
    	return sum(k<<1|1,l,r);
}

void mainwork()
{
	int x,y,v;
	for(int i=1;i<=m;i++)
	{
		d=read();
		if(d<2)
			x=read(),y=read(),v=read(),add(1,d,x,y,v);
		else
			x=read(),y=read(),printf("%lld\n",sum(1,x,y));
	}
}

int main()
{
  prework();
  mainwork();
  return 0;
}
/**********************************************************************
	Problem: 1344
	User: Scanf
	Language: C++
	Result: AC
	Time:256 ms
	Memory:17136 kb
**********************************************************************/


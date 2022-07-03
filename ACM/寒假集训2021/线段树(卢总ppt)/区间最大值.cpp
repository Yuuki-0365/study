#include<cstdio>
#include<cstring>
#define maxl 200010

int n,m;
int a[maxl];
struct node{int l,r,maxnum;}
tree[maxl<<2];
char ch[2];

int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

void build(int k,int l,int r)
{
	tree[k].l=l;tree[k].r=r;
	if(l==r)
	{	
		tree[k].maxnum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	tree[k].maxnum=max(tree[k<<1].maxnum,tree[k<<1|1].maxnum);
}

void prework()
{
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(tree,0,sizeof(tree));
	build(1,1,n);
}

void change(int k,int d,int x)
{
	if(tree[k].l==tree[k].r && tree[k].r==d)
	{
		tree[k].maxnum=x;
		return;
	}
	int mid=(tree[k].l+tree[k].r)>>1;
	if(d>=tree[k].l && d<=mid)
		change(k<<1,d,x);
	else
		change(k<<1|1,d,x);
	tree[k].maxnum=max(tree[k<<1].maxnum,tree[k<<1|1].maxnum);
}

int query(int k,int l,int r)
{
	int maxnum;
	if(tree[k].l==l && tree[k].r==r)
		return tree[k].maxnum;
	int mid=(tree[k].l+tree[k].r)>>1;
	if(r<=mid)
		maxnum=query(k<<1,l,r);
	else
	if(l>=mid+1)
		maxnum=query(k<<1|1,l,r);
	else
		maxnum=max(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
	return maxnum;
}

void mainwork()
{
	int d,x;
	for(int i=1;i<=m;i++)
	{
		scanf("%s%d%d",ch,&d,&x);
		if(ch[0]=='Q')
			printf("%d\n",query(1,d,x));
		else
			change(1,d,x);
	}
}

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		prework();
		mainwork();
	}
	return 0;
}

#include<cstdio>
#include<cstring>
#define maxl 200001

long long n,q;
long long a[maxl];
struct node {long long l,r,sum,tag;};
node tree[maxl<<2];

void build(long long k,long long l,long long r)
{
	tree[k].l=l;tree[k].r=r;
	if(l==r)
	{	
		tree[k].sum=a[l];
		return;
	}
	long long mid=(tree[k].l+tree[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k].sum=tree[k<<1].sum+tree[k<<1|1].sum;
}

void prework()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	scanf("%lld",&q);
	build(1,1,n);
}

void change(long long k)
{
	if(tree[k].l==tree[k].r)
		tree[k].sum+=tree[k].tag;
	else
	{
		tree[k].sum+=(tree[k].r-tree[k].l+1)*tree[k].tag;
		tree[k<<1].tag+=tree[k].tag;
		tree[k<<1|1].tag+=tree[k].tag;
	}
	tree[k].tag=0;
}

void add(long long k,long long l,long long r,long long x)
{
	if(tree[k].tag)
		change(k);
	if(tree[k].l==l && tree[k].r==r)
	{
		tree[k].tag+=x;
		return;
	}
	tree[k].sum+=(r-l+1)*x;
	long long mid=(tree[k].l+tree[k].r)>>1;
	if(r<=mid)
		add(k<<1,l,r,x);
	else
		if(l>mid)
			add(k<<1|1,l,r,x);
		else
			add(k<<1,l,mid,x),add(k<<1|1,mid+1,r,x);
}

long long query(long long k,long long l,long long r)
{
	if(tree[k].tag)
		change(k);
	long long sum,mid=(tree[k].l+tree[k].r)>>1;
	if(tree[k].l==l && tree[k].r==r)
		return tree[k].sum;
	if(r<=mid)
		return query(k<<1,l,r);
	else
		if(l>mid)
			return query(k<<1|1,l,r);
		else
			return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}

void mainwork()
{
	long long l,r,d,x;
	for(long long i=1;i<=q;i++)
	{
		scanf("%lld",&d);
		if(d==1)
		{
			scanf("%lld%lld%lld",&l,&r,&x);
			add(1,l,r,x);
		}
		else
		{
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",query(1,l,r));
		}
	}
}

int main()
{
	prework();
	mainwork();
	return 0;
}

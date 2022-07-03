#include<iostream>
#include<stdio.h>
#include<vector>
#include<math.h>
using namespace std;
vector<int>g[30010];
//建树
int fa[30010],A[30010],val[30010],pos[30010],siz[30010],son[30010],h[30010],top[30010],cnt=0,n;
//fa-父亲节点，val-值，siz-子树大小，h-深度，son-重儿子，top-链顶，pos-dfs序，val-权值，A-
void dfs1(int u,int f){
//u-当前节点,f-父亲节点
    int i,v;
    siz[u]=1;
    son[u]=0;
    fa[u]=f;
    h[u]=h[f]+1;
    for(i=0;i<g[u].size();i++){
        //与当前节点相连的边
	v=g[u][i];
        if(v!=f){
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[son[u]]<siz[v]) son[u]=v;
        }
    }
}
void dfs2(int u,int f,int k){
//u-当前节点，f-父亲节点，k-链顶
    int i,v;
    top[u]=k;
    pos[u]=++cnt;
    A[cnt]=val[u];
    if(son[u]) dfs2(son[u],u,k);
    //优先遍历重儿子
    for(i=0;i<g[u].size();i++){
        v=g[u][i];
        if(v!=f&&v!=son[u]) dfs2(v,u,v);
        //这里因为把重儿子和父亲遍历过了，所以有条件
    }
}

int T[200010],ma[200010];
void update(int root,int l,int r,int k,int v){
     if(l==r){
           T[root]=ma[root]=v;
           return;
     }
     int mid=(l+r)/2;
     if(k<=mid) update(root*2,l,mid,k,v);
     else update(root*2+1,mid+1,r,k,v);
     T[root]=T[root*2]+T[root*2+1];
     ma[root]=max(ma[root*2],ma[root*2+1]);
}
//修改
int qsum(int root,int l,int r,int L,int R){
    if(L==l&&r==R) return T[root];
    int mid=(l+r)/2;
    if(R<=mid) return qsum(root*2,l,mid,L,R);
    else if(L>mid) return qsum(root*2+1,mid+1,r,L,R);
    else return qsum(root*2,l,mid,L,mid)+qsum(root*2+1,mid+1,r,mid+1,R);
}
//这个就是线段树模板求区间值（因为我们在把树链分时有个区间，所以把它放到线段树里面维护了）
int qmax(int root,int l,int r,int L,int R){
    if(L==l&&R==r) return ma[root];
    int mid=(l+r)/2;
    if(R<=mid) return qmax(root*2,l,mid,L,R);
    if(L>mid) return qmax(root*2+1,mid+1,r,L,R);
    else return max(qmax(root*2,l,mid,L,mid),qmax(root*2+1,mid+1,r,mid+1,R));
}
//这个就是线段树模板求区间最大值
int fsum(int u,int v){
    int ans=0;
    while(top[u]!=top[v]){
         if(h[top[u]]<h[top[v]]) swap(u,v);
         ans+=qsum(1,1,n,pos[top[u]],pos[u]);
         u=fa[top[u]];
    }
    if(h[u]<h[v]) swap(u,v);
    ans+=qsum(1,1,n,pos[v],pos[u]);
    return ans;
}
//这个就是求路径长度了
int fmax(int u,int v){
    int ans=-1e9;
    while(top[u]!=top[v]){
        if(h[top[u]]<h[top[v]]) swap(u,v);
        ans=max(ans,qmax(1,1,n,pos[top[u]],pos[u]));
        u=fa[top[u]];
    }
    if(h[u]<h[v]) swap(u,v);
    ans=max(ans,qmax(1,1,n,pos[v],pos[u]));
    return ans;
}
//这个就是求路径上的最大值了
int main(){
    int a,b,m,i;
    char s[10];
    scanf("%d",&n);
    for(i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(i=1;i<=n;i++) scanf("%d",&val[i]);
    dfs1(1,0);
    dfs2(1,0,1);
    for(i=1;i<=n;i++) update(1,1,n,i,A[i]);
    scanf("%d",&m);
    while(m--){
        scanf("%s%d%d",s,&a,&b);
        if(s[1]=='H') update(1,1,n,pos[a],b);
        else if(s[1]=='S') printf("%d\n",fsum(a,b));
        else printf("%d\n",fmax(a,b));
    }
    return 0;
}

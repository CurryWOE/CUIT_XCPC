#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 100005
int node_cnt,n,m;//现有节点数（动态开点），给定数列长度，询问次数
int root[MAXN],a[MAXN],b[MAXN];//每个历史版本的根，原数列，离散后的数列
struct Node
{
    int l,r,sum;//左右子树的下标，区间内有多少数字（即权值）
}tree[MAXN<<5];//主席树
//添加新的数据并建一颗新树
int modify(int pre,int l,int r,int pos)//新树的上一个历史版本，区间上下限，新的数据
{
    tree[++node_cnt]=tree[pre];//新树借用上一个历史版本的数据
    ++tree[node_cnt].sum;//新树的权值比上一个历史版本多一
    if(l==r)//搜索到叶节点
        return node_cnt;//返回该节点的下标
    int now=node_cnt,mid=(l+r)>>1;//保存该节点的下标（不然递归回来时不知道该节点的下标，也就不能修改该节点的l,r了）
    if(pos<=mid)//搜索左子树
        tree[now].l=modify(tree[now].l,l,mid,pos);
    else//搜索右子树
        tree[now].r=modify(tree[now].r,mid+1,r,pos);
    return now;//返回新树的下标
}
//查询区间[l,r]的第k小值
int query(int u,int v,int l,int r,int k)//旧树的下标，新树的下标，区间上下限
{
    if(l==r)//搜索到叶节点
        return l;//返回区间[l,r]的第k小值的下标
    int mid=(l+r)>>1,x=tree[tree[v].l].sum-tree[tree[u].l].sum;//左子树的权值
    if(x>=k)//搜索左子树
        return query(tree[u].l,tree[v].l,l,mid,k);
    else//搜索右子树
        return query(tree[u].r,tree[v].r,mid+1,r,k-x);
}
int main()
{
    int l,r,k,q,ans;//查询的区间上下限、k,离散后还有多少数字，答案的下标
    scanf("%d %d",&n,&m);
    for(register int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];//复制一份
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;//离散
    for(register int i=1;i<=n;++i)
        root[i]=modify(root[i-1],1,q,lower_bound(b+1,b+q+1,a[i])-b);//插入数据并建新树
    while(m--)
    {
        scanf("%d %d %d",&l,&r,&k);
        ans=query(root[l-1],root[r],1,q,k);
        printf("%d\n",b[ans]);
    }
    return 0;
}
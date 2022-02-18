#include<cstdio>
using namespace std;
#define MAXN 100005
struct ST
{
    int l,r,w;
}s[MAXN<<2];
void Build(int l,int r,int n)
{
    s[n].l=l,s[n].r=r,s[n].w=1;
    if(l==r)
        return;
    int temp=(l+r)>>1;
    Build(l,temp,n<<1);
    Build(temp+1,r,n<<1|1);
}
void Update(int l,int r,int n,int w)
{
    if(s[n].l==l && s[n].r==r)
    {
        s[n].w=w;
        return;
    }
    if(s[n].w!=-1)
    {
        s[n<<1].w=s[n<<1|1].w=s[n].w;
        s[n].w=-1;
    }
    int temp=(s[n].l+s[n].r)>>1;
    if(r<=temp)
        Update(l,r,n<<1,w);
    else if(l>temp)
        Update(l,r,n<<1|1,w);
    else
    {
        Update(l,temp,n<<1,w);
        Update(temp+1,r,n<<1|1,w);
    }
}
int Query(int x)
{
    if(s[x].w!=-1)
        return (s[x].r-s[x].l+1)*s[x].w;
    return Query(x<<1)+Query(x<<1|1);
}
int main()
{
    int t,n,q,x,y,op;
    scanf("%d",&t);
    for(int i=1;i<=t;++i)
    {
        scanf("%d%d",&n,&q);
        Build(1,n,1);
        while(q--)
        {
            scanf("%d%d%d",&x,&y,&op);
            Update(x,y,1,op);
        }
        printf("Case %d: The total value of the hook is %d.\n",i,Query(1));
    }
    return 0;
}
//区间变值，区间求和
//https://vjudge.net/contest/432093#status/CUIT2020051079/E/0/
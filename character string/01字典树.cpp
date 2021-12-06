hdu 4825
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=1e5+5;
int tot;
int trie[MAXN<<5][2];
int id[MAXN<<5];
int a[MAXN];
void insert_(int n,int identity)
{
    int rt=0,op;
    for(int i=31;i>=0;--i)
    {
        op=(n>>i)&1;
        if(!trie[rt][op])
            trie[rt][op]=++tot;
        rt=trie[rt][op];
    }
    id[rt]=identity;
}
int query(int n)
{
    int rt=0,op;
    for(int i=31;i>=0;--i)
    {
        op=(n>>i)&1;
        if(trie[rt][op^1])
            rt=trie[rt][op^1];
        else
            rt=trie[rt][op];
    }
    return a[id[rt]];
}
void init()
{
    for(int i=0;i<=tot;++i)
    {
        id[i]=0;
        trie[i][0]=trie[i][1]=0;
    }
    tot=0;
}
int main()
{
    int t,n,m,q;
    scanf("%d",&t);
    for(int kase=1;kase<=t;++kase)
    {
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            insert_(a[i],i);
        }
        printf("Case #%d:\n",kase);
        for(int i=0;i<m;++i)
        {
            scanf("%d",&q);
            printf("%d\n",query(q));
        }
    }
    return 0;
}
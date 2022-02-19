luogu p3376
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2e2+3;
const int MAXM=1e4+3;
int cnt=1,n,m,s,t;
struct EDGE
{
    int v,next;
    ll w;
}e[MAXM];
int head[MAXN];
int q[MAXN],dep[MAXN];
void add_edge(int u,int v,ll w)
{
    e[++cnt].v=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
bool bfs()
{//顺着残量网络，方法是 bfs；这是个bool型函数，返回是否搜到了汇点 
    memset(dep,0,sizeof(int)*(n+1));//记得开局先初始化 
    int l,r,u,v;
    l=r=1;
    q[1]=s;
    dep[s]=1;
    while(l<=r)
    {
        u=q[l++];
        for(int i=head[u];i;i=e[i].next)
        {
            v=e[i].v;
            if(e[i].w && !dep[v])
            {//按照有残量的边搜过去 
                dep[v]=dep[u]+1;
                q[++r]=v;
            }
        }
    }
    return dep[t];//dep[t] != 0，就是搜到了汇点 
}
ll dfs(int u,ll in)/*u收到的支持（不一定能真正用掉）*/
{//注意，return 的是真正输出的流量
    if(u==t)
        return in;//到达汇点是第一个有效return 
    ll out=0,res;
    int v;
    for(int i=head[u];i && in;i=e[i].next)
    {
        v=e[i].v;
        if(e[i].w && (dep[v]==dep[u]+1))//仅允许流向下一层 
        {
            res=dfs(v,min(in,e[i].w));/*受一路上最小流量限制*/
			//res是v真正输出到汇点的流量
            e[i].w-=res;
            e[i^1].w+=res;
            out+=res;
            in-=res;
        }
    }
    if(!out)//我与终点（顺着残量网络）不连通 
        dep[u]=0;//上一层的点请别再信任我，别试着给我流量
    return out;
}
int main()
{
    int u,v;
    ll w;
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i=0;i<m;++i)
    {
        scanf("%d %d %lld",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,0);
    }
    ll ans=0;
    while(bfs())
        ans+=dfs(s,1e18);
    printf("%lld\n",ans);
    return 0;
}
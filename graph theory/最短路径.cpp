DFS,BFS是基础,SPFA是BFS的变形,Floyd用于多源最短路,Dijkstra用于没有负权的图,SPFA用于有负权的图
void DFS(int cur,int dst)//深度优先搜索
{
    if(minPath < dst) return;//当前走过路径大于之前最短路径，没必要再走下去
    if(cur == n)//临界条件
    {
        if(minPath > dst) minPath = dst;
        return;
    }
    else
    {
        int i;
        for(i = 1; i <= n; i++)
        {
            if(edge[cur][i] != inf && edge[cur][i] != 0 && mark[i] == 0)
            {
                mark[i] = 1;
                dfs(i, dst+edge[cur][i]);
                mark[i] = 0;//需要在深度遍历返回时将访问标志置0
            }
        }
        return;
    }
}
void BFS(int root,int N)//广度优先搜索 // N个点的图，从root点开始搜索。
{
    queue <int> que;

    memset(vis,0,sizeof(vis));// 初始化。
    vis[root]=1;
    que.push(root);

    int u,len;

    while(!que.empty())
    {
        u=que.front();
        que.pop();

        len=E[u].size();
        for(int i=0;i<len;++i)// 找到和u相连的所有点，存在一个vector里面。
            if(vis[E[u][i]]==0)
            {
                vis[E[u][i]]=1;
                que.push(E[u][i]);
            }
    }
}
void Floyd()
{
    for(k = 1; k <= n; k++)
    {
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
            {
                if(Floyd[i][k] < inf && Floyd[k][j] < inf && Floyd[i][j] > Floyd[i][k] + Floyd[k][j])
                    Floyd[i][j] = Floyd[i][k] + Floyd[k][j];
            }
        }
    }
}
//POJ 2387
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
const int MAXN=1005;
const int INF=0x3f3f3f3f;
const int MAXM=4005;
typedef pair<int,int> PII;
int n,m;
int dis[MAXN],vis[MAXN],head[MAXN];
priority_queue <PII,vector<PII>,greater<PII> > q;
struct edge
{
    int to,w,next;
};
edge e[MAXM];
void add_edge(int u,int v,int w,int pos)
{
    e[pos].to=v;
    e[pos].w=w;
    e[pos].next=head[u];
    head[u]=pos;
}
int dij(int begin,int end)
{
    memset(dis,0x3f,sizeof(dis));
    dis[begin]=0;
    memset(vis,0,sizeof(vis));
    q.push(PII{0,begin});
    while(q.size())
    {
        int u=q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(int i=head[u];~i;i=e[i].next)
        {
            int v=e[i].to;
            dis[v]=min(dis[v],dis[u]+e[i].w);
            q.push({dis[v],v});
        }
    }
    return dis[end];
}
int main()
{
    int u,v,w,cnt=-1;
    scanf("%d %d",&m,&n);
    memset(head,-1,sizeof(head));
    for(int i=0;i<m;++i)
    {
        scanf("%d %d %d",&u,&v,&w);
        add_edge(u,v,w,++cnt);
        add_edge(v,u,w,++cnt);
    }
    printf("%d\n",dij(n,1));
    return 0;
}
//luogu p3385
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXM=6e3+3;
const int MAXN=2e3+3;
struct edge
{
    int v,w,next;
}e[MAXM];
int head[MAXN];
int tot=1;
int n,m;

int dis[MAXN],cnt[MAXN],vis[MAXN];
queue<int> q;

void add_edge(int u,int v,int w)
{
    e[++tot]=edge{v,w,head[u]};
    head[u]=tot;
}
bool spfa(int begin)
{
    dis[begin]=0;
    q.push(begin);
    int u,v;
    while(!q.empty())
    {
        u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].next)
        {
            v=e[i].v;
            if(dis[v]>dis[u]+e[i].w)
            {
                dis[v]=dis[u]+e[i].w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n)
                    return 1;
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return 0;
}
void init()
{
    tot=1;
    memset(head,0,sizeof(int)*(n+1));
    memset(vis,0,sizeof(int)*(n+1));
    memset(dis,0x3f,sizeof(int)*(n+1));
    memset(cnt,0,sizeof(int)*(n+1));
    while(!q.empty())
        q.pop();
}
int main()
{
    int kase;
    int u,v,c;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d %d",&n,&m);
        init();
        for(int i=0;i<m;++i)
        {
            scanf("%d %d %d",&u,&v,&c);
            add_edge(u,v,c);
            if(c>=0)
                add_edge(v,u,c);
        }
        printf("%s\n",spfa(1) ? "YES" : "NO");
    }
    return 0;
}
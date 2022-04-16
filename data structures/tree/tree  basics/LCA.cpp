//最近公共祖先
const int N=5e5+3;
const int M=20;
struct EDGE
{
    int to,nxt;
};
struct LCA
{
    EDGE e[N<<1];
    int fa[N][M],dep[N],head[N],lg[N];
    int tot;
    queue<int> q;
    void init(int n)
    {
        tot=0;
        for(int i=1;i<n;++i)
            lg[i]=lg[i-1]+(1<<lg[i-1]==i);
    }
    void AddEdge(int u,int v)
    {
        e[++tot]={u,head[v]};
        head[v]=tot;
        e[++tot]={v,head[u]};
        head[u]=tot;
    }
    void bfs(int root)
    {
        q.push(root);
        dep[root]=1;
        int u,v,DEP;
        while(!q.empty())
        {
            u=q.front();
            q.pop();
            for(int i=head[u];i;i=e[i].nxt)
            {
                v=e[i].to;
                if(dep[v])
                    continue;
                q.push(v);
                dep[v]=dep[u]+1;
                fa[v][0]=u;
                DEP=lg[dep[u]];
                for(int j=1;j<=DEP;++j)
                {
                    fa[v][j]=fa[fa[v][j-1]][j-1];
                }
            }
        }
    }
    int lca(int x,int y)
    {
        if(dep[x]>dep[y])
            swap(x,y);
        for(int i=0,dif=dep[y]-dep[x];dif;++i,dif>>=1)
        {
            if(dif&1)
                y=fa[y][i];
        }
        if(x==y)
            return x;
        for(int i=lg[dep[x]];i>=0;--i)
        {
            if(fa[x][i]==fa[y][i])
                continue;
            x=fa[x][i];
            y=fa[y][i];
        }
        return fa[x][0];
    }
};
typedef long long ll;
const int N=4e4+3;
const int M=20;
struct EDGE
{
    int to,nxt;
    ll w;
};
struct LCA
{
    EDGE e[N<<1];
    int fa[N][M],dep[N],head[N],lg[N];
    ll cost[N][M];
    int tot;
    queue<int> q;
    void init0()
    {
        lg[0]=0;
        for(int i=1;i<N;++i)
            lg[i]=lg[i-1]+(1<<(lg[i-1])==i);
    }
    void init(int n)
    {
        tot=0;
        memset(head,0,sizeof(int)*(n+1));
        memset(dep,0,sizeof(int)*(n+1));
    }
    void AddEdge(int u,int v,ll w)
    {
        e[++tot]={u,head[v],w};
        head[v]=tot;
        e[++tot]={v,head[u],w};
        head[u]=tot;
    }
    void bfs(int root)
    {
        q.push(root);
        dep[root]=1;
        int u,v,DEP;
        while(!q.empty())
        {
            u=q.front();
            q.pop();
            for(int i=head[u];i;i=e[i].nxt)
            {
                v=e[i].to;
                if(dep[v])
                    continue;
                q.push(v);
                dep[v]=dep[u]+1;
                fa[v][0]=u;
                cost[v][0]=e[i].w;
                DEP=lg[dep[u]];
                for(int j=1;j<=DEP;++j)
                {
                    fa[v][j]=fa[fa[v][j-1]][j-1];
                    cost[v][j]=cost[fa[v][j-1]][j-1]+cost[v][j-1];
                }
            }
        }
    }
    int lca(int x,int y)
    {
        if(dep[x]>dep[y])
            swap(x,y);
        ll ans=0;
        for(int i=0,dif=dep[y]-dep[x];dif;++i,dif>>=1)
        {
            if(dif&1)
            {
                ans+=cost[y][i];
                y=fa[y][i];
            }
        }
        if(x==y)
            return ans;
        for(int i=lg[dep[x]];i>=0;--i)
        {
            if(fa[x][i]==fa[y][i])
                continue;
            ans+=cost[x][i]+cost[y][i];
            x=fa[x][i];
            y=fa[y][i];
        }
        return ans+cost[x][0]+cost[y][0];
    }
};
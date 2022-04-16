const int N=1e4+3;
const int M=5e4+3;
const int K=20;
struct EDGE
{
    int u,v,w;
    bool operator<(const EDGE b) const
    {
        return w>b.w;
    }
};
struct ed
{
    int to,nxt;
};
struct kru
{
    ed e[N<<1];
    EDGE ee[M];
    int fa[N<<1][K],dep[N<<1],head[N<<1],lg[N<<1],val[N];
    int f[N<<1];
    int tot,edgetot;
    queue<int> q;
    void init(int n)
    {
        lg[0]=0;
        int limit=n<<1;
        for(int i=1;i<=limit;++i)
            lg[i]=lg[i-1]+(1<<(lg[i-1])==i);
        memset(f,-1,sizeof(int)*(limit));
        tot=0;
        edgetot=-1;
        memset(head,0,sizeof(int)*(limit));
        memset(dep,0,sizeof(int)*(limit));
    }
    int find(int x)
    {
        return f[x]==-1?x:(f[x]=find(f[x]));
    }
    void addedge(int u,int v,int w)
    {
        ee[++edgetot]={u,v,w};
    }
    void AddEdge(int u,int v)
    {
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
                    fa[v][j]=fa[fa[v][j-1]][j-1];
            }
        }
    }
    void kruskal(int n,int m)
    {
        sort(ee,ee+m);
        int f1,f2;
        int cnt=n;
        for(int i=0;i<m;++i)
        {
            f1=find(ee[i].u);
            f2=find(ee[i].v);
            if(f1==f2)
                continue;
            ++cnt;
            f[f1]=f[f2]=cnt;
            val[cnt-n]=ee[i].w;
            AddEdge(cnt,f1);
            AddEdge(cnt,f2);
            if(cnt==2*n-1)
                break;
        }
        for(int i=cnt;i>n;--i)
        {
            if(!dep[i])
                bfs(i);
        }
    }
    int lca(int x,int y)
    {
        if(find(x)!=find(y))
            return -1;
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
}ans;
ans.init(n);
ans.addedge(u,v,w);
ans.kruskal(n,m);
point=ans.lca(u,v);
if(point==-1)
    cout<<"-1\n";
else
    cout<<ans.val[point-n]<<"\n";
# 网络流DINIC
```c++
const int N=2e2+5;
const int M=1e6+3;
const ll INF=1e18;
struct Edge
{
    int v,nxt;
    ll cap;
};
struct Dinic
{
    int n,s,t,tot;
    int head[N],dep[N];
    Edge e[M];
    queue<int> q;
    void init(int nn,int ss,int tt)
    {
        n=nn;
        s=ss;
        t=tt;
        memset(head,0,sizeof(int)*(n+1));
        head[s]=head[t]=0;
        tot=1;
    }
    void addEdge(int x,int y,ll cap)
    {
        e[++tot]={y,head[x],cap};
        head[x]=tot;
        e[++tot]={x,head[y],0};
        head[y]=tot;
    }
    bool level()
    {
        memset(dep,0,sizeof(int)*(n+1));
        dep[t]=0;
        dep[s]=1;
        int u,v;
        q.push(s);
        while(!q.empty())
        {
            u=q.front();
            q.pop();
            for(int i=head[u];i;i=e[i].nxt)
            {
                v=e[i].v;
                if(e[i].cap && !dep[v])
                {
                    dep[v]=dep[u]+1;
                    q.push(v);
                }
            }
        }
        return dep[t];
    }
    ll findpath(int u,ll in)
    {
        if(u==t)
            return in;
        ll out=0,res;
        int v;
        for(int i=head[u];i && in;i=e[i].nxt)
        {
            v=e[i].v;
            if(e[i].cap && dep[v]==dep[u]+1)
            {
                res=findpath(v,min(in,e[i].cap));
                e[i].cap-=res;
                e[i^1].cap+=res;
                out+=res;
                in-=res;
            }
        }
        if(!out)
            dep[u]=0;
        return out;
    }
    ll dinic()
    {
        ll res=0;
        while(level())
            res+=findpath(s,INF);
        return res;
    }
}di;
di.init(n,s,t);
di.addEdge(u,v,w);
di.dinic();
```
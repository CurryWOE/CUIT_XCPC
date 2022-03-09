```c++
const int N=2e2+3;
const int M=1e5+3;
struct Edge
{
    int v,nxt;//next是stl函数，所以用nxt
    ll cap;
};
struct Dinic
{
    int n,s,t,tot;
    int head[N],dep[N];
    Edge e[M];
    queue<int> q;
    void init(int n,int s,int t)
    {
        this->n=n;
        this->s=s;
        this->t=t;
        memset(head,0,sizeof(int)*(n+1));
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
        while(!q.empty())
            q.pop();
        int u,v;
        q.push(s);
        dep[s]=1;
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
            res+=findpath(s,1e18);
        return res;
    }
}ans;
ans.init(n,s,t);
ans.addEdge(u,v,w);
ans.dinic()
```
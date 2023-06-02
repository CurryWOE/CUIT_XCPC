#! https://zhuanlan.zhihu.com/p/625097784
# 网络流DINIC
$O(V^2E)$，如果用在二分图，是 $O(V\sqrt E)$

最大流：假设源点流量够多，求汇点最大流量

最小割：去掉一部分边，使得剩下两个包含源点和汇点的图，割的大小是边容量之和，最小的割就是最小割

最大权闭合子图：子图上的点，其所有出边指向的点，都在该子图中，则为闭合子图，点权和最大的闭合子图为最大权闭合子图。源点和正权点连容量为点权的边，汇点和负权点连容量为点权绝对值的边，如果选了正权点必须选某些负权点，则正权点和负权点连容量为无限大的边。最大点权和=正点权和-最小割

最大独立集：n-最大流，每个点只能分配到一边，通常和奇偶性有关
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
di.addEdge(u,v,w);//边的顺序一定是源点-中间点-汇点
di.dinic();
```
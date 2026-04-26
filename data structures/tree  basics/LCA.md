#! https://zhuanlan.zhihu.com/p/2031730090690745372
# 最近公共祖先(Lowest Common Ancestor)
## 倍增(Binary Lifting)
```cpp
const uint32_t N=5e5+1,M=bit_width(N);
namespace BinaryLiftingLCA
{
    uint32_t fa[N][M],dep[N];
    queue<uint32_t> q;
    void init(uint32_t n,uint32_t root)
    {
        fill(dep+1,dep+n+1,0);
        fill(&fa[1][0], &fa[1][0] + n * M, 0);
        q.push(root);
        while(!q.empty())
        {
            uint32_t u=q.front();
            q.pop();
            uint32_t depth=bit_width(dep[u]);
            for(auto v:e[u])
            {
                if(dep[v])
                    continue;
                dep[v]=dep[u]+1;
                fa[v][0]=u;
                for(uint32_t j=1;j<depth;++j)
                    fa[v][j]=fa[fa[v][j-1]][j-1];
                q.push(v);
            }
        }
    }
    uint32_t lca(uint32_t x,uint32_t y)
    {
        if(dep[x]>dep[y])
            swap(x,y);
        for(uint32_t dif = dep[y] - dep[x];dif;dif&=(dif-1))
            y = fa[y][countr_zero(dif)];
        if(x==y)
            return x;
        for(int j=bit_width(dep[x])-1;j>=0;--j)
        {
            if(fa[x][j]==fa[y][j])
                continue;
            x=fa[x][j];
            y=fa[y][j];
        }
        return fa[x][0];
    }
}
```
## 重链剖分(Heavy Path Decomposition)
```cpp
const uint32_t N=5e5+1;
namespace HeavyPathDecompositionLCA
{
    int dep[N],fa[N],siz[N],son[N],top[N];
    void dfs1(int u)
    {
        for(auto v:e[u])
        {
            if(v==fa[u])
                continue;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
    void dfs2(int u, int Top)
    {
        top[u] = Top;
        if (son[u] == 0)
            return;
        dfs2(son[u], Top);
        for(auto v:e[u])
            if (v!=son[u] && v!=fa[u])
                dfs2(v,v);
    }
    void init(int n,int root)
    {
        dep[root]=1;
        fa[root]=0;
        fill(siz+1,siz+n+1,1);
        fill(son+1,son+n+1,0);
        dfs1(root);
        dfs2(root,root);
    }
    int lca(int u,int v)
    {
        for(;top[u]!=top[v];u=fa[top[u]])
            if(dep[top[u]]<dep[top[v]])
                swap(u,v);
        return (dep[u]>dep[v]?v:u);
    }
}
```
## 欧拉序+RMQ
```cpp
const uint32_t N=5e5+1,M=bit_width(N);
namespace EulerOrderRMQLCA
{
    uint32_t st[M][N],dfn[N],path[N],ret[N],tot;
    void dfs(uint32_t u,uint32_t fa)
    {
        dfn[u]=++tot;
        for(auto v:e[u])
        {
            if(v==fa)
                continue;
            path[tot]=u;
            ret[tot]=dfn[u];
            dfs(v,u);
        }
    }
    void init(uint32_t n,uint32_t root)
    {
        --n;
        tot=0;
        dfs(root,0);
        for(uint32_t i=1;i<=n;++i)
            st[0][i]=ret[i];
        for (uint32_t i = 1; i < bit_width(n); ++i)
            for (uint32_t j = 1; j + (1 << i) - 1 <= n; ++j)
                st[i][j] = min(st[i-1][j],st[i-1][j + (1 << (i - 1))]);
    }
    uint32_t lca(uint32_t l, uint32_t r)
    {
        if(l==r)
            return l;
        l = dfn[l],r = dfn[r];
        if(l>r)
            swap(l,r);
        uint32_t s = bit_width(r - l)-1;
        return path[min(st[s][l], st[s][r - (1 << s)])];
    }
}
```
## Farach-Colton and Bender
将数组 A 划分为大小为 K 的块，块内计算最值，并存入数组 B，B 的大小为 $\frac NK$，在数组 B 上构建ST表，时空复杂度为 $O(\frac NK\log_2\frac NK)$

如果数组 A 相邻元素总是相差 1，去掉每个块的第一个元素，然后将该元素从块内所有其他元素中减去，那么每个块可以由一个长度为 K−1 的序列来标识，不同序列个数 $2^{K-1}$

对每个序列暴力处理所有区间最值，时间复杂度 $O(2^{K-2}K(K-1))$

总复杂度为 $O(\frac NK\log_2\frac NK+2^{K-2}K(K-1))$

考虑到计算机的物理特性，K一般取16，此时总复杂度约为 $$\frac{N \log_2 N}{16} - \frac{N}{4}+4e6$$，再考虑到竞争性编程中的N的范围，上式近似为 $O(N)$

在树上DFS，递归或回溯时遇到的点构造的序列，相邻两点高度差总是为1，因此可以使用上述分块算法求出欧拉序的高度数组区间最值，而LCA就是高度最小值的点
```cpp
```
## tarjan
```cpp
const uint32_t N=5e5+1;
namespace tarjanLCA
{
    vector<array<uint32_t,2>> q[N];
    uint32_t f[N],ans[N];
    bool vis[N];
    int find(int x)
    {
        return f[x] == 0 ? x : f[x] = find(f[x]);
    }
    void tarjan(int u,int fa)
    {
        vis[u] = true;
        for(auto v:e[u])
        {
            if(v==fa)
                continue;
            tarjan(v,u);
            f[v] = u;
        }
        for (auto [v,id]:q[u])
            if (vis[v])
                ans[id] = find(v);
    }
    void addQuery(int u,int v,int id)
    {
        q[u].push_back{{v,id}};
        q[v].push_back{{u,id}};
    }
    void init(int n)
    {
        for(int i=1;i<=n;++i)
            q[i].clear();
        fill(f+1,f+n+1,0);
        fill(vis+1,vis+n+1,false);
    }
    void run(int root)
    {
        tarjan(root,0);
    }
}
```
## 各个算法的优缺点对比
根据[测试网站1](https://judge.yosupo.jp/problem/lca)，[倍增](https://judge.yosupo.jp/submission/368670)372ms，[重链剖分](https://judge.yosupo.jp/submission/368668)255ms，[欧拉序+RMQ](https://judge.yosupo.jp/submission/368671)77ms，[tarjan](https://judge.yosupo.jp/submission/368676)93ms

根据[测试网站2](https://www.luogu.com.cn/problem/P3379)，[倍增](https://www.luogu.com.cn/record/275582721)1.15s，[重链剖分](https://www.luogu.com.cn/record/275584773)953ms，[欧拉序+RMQ](https://www.luogu.com.cn/record/275585904)489ms，[tarjan](https://www.luogu.com.cn/record/275717894)487ms

倍增可以动态加叶子，重链剖分可以配合线段树，欧拉序是最快在线，如果同时卡时间空间且离线，则选择tarjan
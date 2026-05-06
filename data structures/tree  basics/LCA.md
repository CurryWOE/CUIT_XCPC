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
## 欧拉序列+RMQ
树上DFS，递归或回溯时遇到的点构成的序列，这个序列被称为欧拉序列，长度为 2|V|-1

两个节点 u 和 v 的 LCA，一定是欧拉序列中从 u 第一次出现到 v 第一次出现之间，深度最小的那个节点

因此在欧拉序列的深度数组上构建RMQ数据结构，维护区间最小值，以及取得最小值的位置。查询区间最小值的位置，再通过“欧拉序列上的位置-树上点”的映射得到LCA

RMQ使用稀疏表，还是和分块结合的稀疏表，还是通过欧拉序列，相邻两点深度差总是为1，使用+-1RMQ（又名Farach-Colton and Bender），其时间空间代码量不如 KACTL's LCA，因此这里不写出例程

根据[测试网站](https://www.luogu.com.cn/problem/P3379)，[FCB](https://www.luogu.com.cn/record/275974429)648ms，[稀疏表+欧拉序列](https://www.luogu.com.cn/record/275984152)628ms，[块内暴力+块间稀疏表+块前后缀+欧拉序列](https://www.luogu.com.cn/record/275978207)534ms，[KACTL's LCA](https://www.luogu.com.cn/record/275585904)489ms
## KACTL's LCA(DFS序LCA)
树上DFS，遇到一个点，记录其父节点DFS序，（根的父节点DFS序不重要，因为具体实现会丢掉这个数据），组成一个序列，长度为 |V|

对于u等于v的情况特殊处理，下面考虑u不等于v的情况，这里假设 u 的dfs序小于 v 的DFS序，如果不满足假设就交换 u 和 v

LCA在序列上的 [u的DFS序+1，v的DFS序] 区间内（1-indexed），且LCA是这个区间内父节点DFS序最小的

这里区间左端点+1，是因为如果 u 就是 v 的祖先，u的父节点不可能是LCA，所以+1。顺便解释了为什么要特殊处理u等于v的情况

因此在根据DFS序顺序构成的父节点DFS序数组上构建ST表，查询区间最小值，由于DFS序唯一，不需要通过“序列位置-树上点”的映射，而是通过“DFS序-树上点”的映射得到LCA

在下面的具体实现中，由于[u的DFS序+1，v的DFS序]会导致位置1永远用不上，所以整体前移一个位置，也就是--n和查询区间改为[u的DFS序，v的DFS序-1]
```cpp
const uint32_t N=5e5+1,M=bit_width(N);
namespace KACTLLCA
{
    uint32_t st[M][N],dfn[N],path[N],ret[N],tot;
    void dfs(uint32_t u,uint32_t fa)
    {
        dfn[u]=++tot;
        path[tot]=u;
        for(auto v:e[u])
        {
            if(v==fa)
                continue;
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
## 块内暴力+块间猫树+块前后缀+DFS序
```cpp
const uint32_t N=5e5+1,K=16;
namespace BlockCatTree
{
    uint32_t a[N],prefixInBlock[N],suffixInBlock[N],blockMin[N/K],ct[bit_width(N/K)][N/K];
    inline void init(uint32_t n)
    {
        memcpy(prefixInBlock,a,sizeof(uint32_t)*n);
        for(uint32_t l=0;l<n;l+=K)
            for(uint32_t i=l+1,r=min(n,l+K)-1;i<=r;++i)
                prefixInBlock[i]=min(prefixInBlock[i-1],prefixInBlock[i]);
        memcpy(suffixInBlock,a,sizeof(uint32_t)*n);
        for(uint32_t l=0;l<n;l+=K)
            for(uint32_t i=min(n,l+K);i>l;--i)
                suffixInBlock[i-1]=min(suffixInBlock[i],suffixInBlock[i-1]);
        uint32_t block = n / K;
        for(uint32_t i=0;i<block;++i)
            blockMin[i]=suffixInBlock[i*K];
        for(uint32_t i=0;i<bit_width(block);++i)
            memcpy(ct[i],blockMin,sizeof(uint32_t)*block);
        for (uint32_t dep = 1, len = 2; len<block; ++dep, len <<= 1)
            for (uint32_t l = 0; l < block; l += (len<<1))
            {
                uint32_t mid = l + len;
                for(uint32_t i = mid-1; i > l; --i)
                    ct[dep][i-1] = min(ct[dep][i], ct[dep][i-1]);
                for(uint32_t i = mid ,r=min(mid+len, block)-1; i < r; ++i)
                    ct[dep][i+1] = min(ct[dep][i], ct[dep][i+1]);
            }
    }
    inline uint32_t query(uint32_t l, uint32_t r)
    {
        uint32_t bl = l/K, br = r/K;
        if (bl == br)
            return *min_element(a+l,a+r+1);
        uint32_t res = min(suffixInBlock[l], prefixInBlock[r]);
        if(bl+1==br)
            return res;
        ++bl,--br;
        if(bl==br)
            return min(res,blockMin[bl]);
        uint32_t dep=bit_width(bl^br)-1;
        return min({res,ct[dep][bl],ct[dep][br]});
    }
}
namespace DFNLCA
{
    uint32_t path[N],dfn[N],tot;
    void dfs(int u, int fa)
    {
        dfn[u] = ++tot;
        path[tot] = u;
        for(auto v:e[u])
        {
            if (v == fa)
                continue;
            BlockCatTree::a[tot]=dfn[u];
            dfs(v, u);
        }
    }
    inline void init(int root)
    {
        tot = -1;
        dfs(root, 0);
        BlockCatTree::init(tot+1);
    }
    inline int lca(int u, int v)
    {
        if(u==v)
            return u;
        int l = dfn[u], r = dfn[v];
        if (l > r)
            swap(l, r);
        return path[BlockCatTree::query(l, r-1)];
    }
}
```
## 各个算法的优缺点对比
根据[测试网站1](https://judge.yosupo.jp/problem/lca)，[倍增](https://judge.yosupo.jp/submission/368670)372ms，[重链剖分](https://judge.yosupo.jp/submission/368668)255ms，[KACTL](https://judge.yosupo.jp/submission/370725)47ms，[tarjan](https://judge.yosupo.jp/submission/368676)93ms，[块内暴力+块间猫树+块前后缀+DFS序](https://judge.yosupo.jp/submission/370701)28ms

根据[测试网站2](https://www.luogu.com.cn/problem/P3379)，[倍增](https://www.luogu.com.cn/record/276088452)1.05s，[重链剖分](https://www.luogu.com.cn/record/276088680)843ms，[稀疏表+DFS序](https://www.luogu.com.cn/record/275585904)489ms，[tarjan](https://www.luogu.com.cn/record/275717894)487ms，[块内暴力+块间稀疏表+块前后缀+DFS序](https://www.luogu.com.cn/record/275981113)374ms,[块内暴力+块间猫树+块前后缀+DFS序](https://www.luogu.com.cn/record/276105276)333ms

倍增可以动态加叶子，维护不可减信息（比如链上max），重链剖分可以配合线段树，KACTL是在线最短代码且速度不差，tarjan比KACTL省空间，但是要离线。块内暴力+块间猫树+块前后缀+DFS序最快
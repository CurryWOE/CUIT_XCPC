#! https://zhuanlan.zhihu.com/p/625094210
# 树上启发式合并
对于区间元素种类数，区间出现次数大于k的元素，这样不能高效合并，但是高效单点修改的信息，需要用dsu on tree，离线，如果是每个子树都要查这样的信息，那就更得用了

重链剖分做一遍，利用根节点到树上任意节点的轻边数不超过 $\log n$ 条
## 做法
统计答案时，先遍历轻儿子，算完一个儿子就要撤销其贡献（如果需要撤销的话）

再扫重儿子，不撤销重儿子贡献

遍历轻儿子，加入其贡献，即可得到 u 的答案

有关答案的信息作为全局变量，所有节点共用

del时不必考虑中间答案的正确性，有关答案的信息可以放在外面重置
## 时间复杂度
$O(nlog n)$
```cpp
vector<int> e[N];
int siz[N],hson[N];
int ans[N];
void dfs(int u,int fa)
{
    siz[u]=1;
    int mxsz=0;
    for(auto &v:e[u])
    {
        if(v==fa)
            continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>mxsz)
        {
            mxsz=siz[v];
            hson[u]=v;
        }
    }
}
void add(int u)
{

}
void del(int u)
{

}
void addsubtree(int u,int fa)
{
    add(u);
    for(auto v:e[u])
    {
        if (v!=fa)
            addsubtree(v,u);
    }
}
void delsubtree(int u,int fa)
{
    del(u);
    for(auto v:e[u])
    {
        if(v!=fa)
            delsubtree(v,u);
    }
}
void dsu(int u,int fa)
{
    for(auto v:e[u])
    {
        if(v==fa || v==hson[u])
            continue;
        dsu(v,u);
        delsubtree(v,u);
        //重置有关答案的信息
    }
    if(hson[u])
        dsu(hson[u],u);
    add(u);
    for(auto v:e[u])
    {
        if(v!=fa && v!=hson[u])
            addsubtree(v,u);
    }
    ans[u] = 114514;
}
```
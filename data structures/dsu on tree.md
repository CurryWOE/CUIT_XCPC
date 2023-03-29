# 树上启发式合并
解决“树上每个节点，询问其子树的信息，离线”，利用重链剖分的思想

dfs维护重儿子

统计答案时，先遍历轻儿子，算完一个儿子就要撤销其贡献（如果需要撤销的话）

再扫重儿子，不撤销重儿子贡献

遍历轻儿子，加入其贡献，即可得到 u 的答案

有关答案的信息通常作为全局变量，所有节点共用

del时不必考虑中间答案的正确性，有关答案的信息可以放在外面重置
```cpp
vector<int> e[N];
int siz[N],hson[N];
int ans[N];
void dfs0(int u,int fa)
{
    siz[u]=1;
    int mxsz=0;
    for(auto &v:e[u])
    {
        if(v==fa)
            continue;
        dfs0(v,u);
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
void dfs(int u,int fa)
{
    for(auto v:e[u])
    {
        if(v==fa || v==hson[u])
            continue;
        dfs(v,u);
        delsubtree(v,u);
        //重置有关答案的信息
    }
    if(hson[u])
        dfs(hson[u],u);
    add(u);
    for(auto v:e[u])
    {
        if(v!=fa && v!=hson[u])
            addsubtree(v,u);
    }
    ans[u] = 114514;
}
```
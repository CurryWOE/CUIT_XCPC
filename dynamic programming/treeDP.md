# 树形DP
```cpp
void dfs(int u,int fa)
{
    for(auto v:e[u])
    {
        if(v==fa)
            continue;
        /*----*/
        dfs(v,u);
        /*----*/
    }
}
```
# 树上背包
$f(u,i,j)$ 表示 $u$ 号点的前 $i$ 棵子树，选了 $j$ 个节点的最大分数

$f(u,i,j)=\max_{k\le j,k\le v_{size}}f(u,i-1,j-k)+f(v,v_{son-num},k)$
---

第二维倒序滚掉

sz优化使得复杂度为 $O(n^2)$
```cpp
void dfs(int u,int fa)
{
    int Usz=1,Vsz;
    for(auto v:e[u])
    {
        if(v==fa)
            continue;
        Vsz=dfs(v,u);
        for(int i=Usz;i;--i)
        {
            for(int j=1;j<=Vsz;++j)
                f[u][i+j]=max(f[u][i+j],f[u][i]+f[v][j]);
        }
        Usz+=Vsz;
    }
    reutrn Usz;
}
```
# 换根
无根树选择一个点作为根，使结果最优，设$f_u$为以$u$为根的结果

dfs第一遍处理$f_{start}$，dfs第二遍处理$f_u\rightarrow f_v$，即以$u$为根转移到以$v$为根的信息
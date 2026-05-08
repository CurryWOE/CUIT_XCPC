# 图论导读
## 存图
裸数组，邻接矩阵，std::vector数组实现的邻接表，数组模拟链表实现的邻接表（中文社区称之为链式前向星），静态邻接表
### 有根树给出父节点，且父节点编号小于当前点
上述性质隐含了“编号是拓扑序”的约束，正序遍历父节点会先于所有子节点被遍历，逆序遍历则反之

求子树大小逆序遍历即可。利用子树大小正序遍历求DFS序是比较精妙的做法，原理是，树内点DFS序连续，且区间长度等于子树大小，通过记录父节点的DFS序区间右端点的值，即可推出子节点的DFS序区间右端点的值。对于叶子节点，其区间长度为1，所以最后的值就是叶子的DFS序。对于非叶子节点，右端点减去所有子树大小，即为该点的DFS序

该写法主要是优化常数，相比于DFS优化几十毫秒
```cpp
int fa[N],dfn[N],siz[N];//父节点，DFS序，子树大小
void init(int n)
{
    fill(siz+1,siz+n+1,1);
    for(int i=n;i>1;--i)
        siz[fa[i]]+=siz[i];
    memcpy(dfn+1,siz+1,sizeof(int)*n);
    for(int i=2;i<=n;++i)
    {
        int t=dfn[i];
        dfn[i]=dfn[fa[i]];
        dfn[fa[i]]-=t;
    }
}
```
### 静态邻接表
邻接表加边慢，链式前向星遍历边慢，利用出度前缀和重新排布出边，即为静态邻接表
```cpp
array<int,2> oriEdge[E];//原始顺序存储的边
int deg[V],degTmp[V],e[E*2];//度数，新顺序存储的边
void build(int n,int m)
{
    for(int i=0;i<m;++i)
    {
        ++deg[oriEdge[i][0]];
        ++deg[oriEdge[i][1]];//无向边加这一行
    }
    for(int i=1;i<=n;++i)
        deg[i]+=deg[i-1];
    memcpy(degTmp, deg, sizeof(deg[0])*(n+1));
    for(int i=0;i<m;++i)
    {
        e[--degTmp[oriEdge[i][0]]]=oriEdge[i][1];
        e[--degTmp[oriEdge[i][1]]]=oriEdge[i][0];//无向边加这一行
    }
}
void getEdge(int u)
{
    for(int i=deg[u-1];i<deg[u];++i)
        cout<<e[i]<<' ';
}
```
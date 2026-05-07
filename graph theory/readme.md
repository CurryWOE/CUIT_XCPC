# 图论导读
## 存图
裸数组，邻接矩阵，邻接表，链式前向星，静态邻接表
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
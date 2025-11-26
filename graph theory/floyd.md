# floyd
全源最短路，可以用在有向图/无向图，正边权/负边权，但不能有负环

定义数组dis[k][x][y]表示x到y，除去起点终点，只允许经过节点1到k（x和y不一定在1到k），的最短路长度

dis[0][x][y]就是原图，要么为直接相连的边的边权，要么为0（x==y），要么为正无穷（不存在直接相连的边）

第一维可以滚动数组滚掉
```c++
namespace floyd
{
    int n;
    ll dis[N][N];
    void init(int m)
    {
        n=m;
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                dis[i][j]=(i==j?0:INF);
    }
    void flo()
    {
        for(int k = 1; k <= n; ++k)
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
};
```
## 无向图无负环找最小环
考虑环上最大编号点k，与点k相邻的两点x，y，当更新到点k前，dix[x][y]+originalEdge[x][k]+originalEdge[k][y]等于环长度

假如当前枚举的x，y和k没有直接相连的边，那么originalEdge[x][k]，originalEdge[k][y]为正无穷，三数之和为正无穷，不会影响答案

假如当前枚举的x，y没有不经过k的路径，那么dis[x][y]为正无穷，三数之和为正无穷，不会影响答案

所以x-k-y-x组成的路径，三数之和小于正无穷时，一定是简单环

因此在更新点u前，记录三数之和最小值即为答案
```cpp
namespace floyd
{
    int n,dis[N][N],originalEdge[N][N];//originalEdge表示原始边
    void init(int nn)
    {
        n=nn;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                dis[i][j]=(i==j?0:INF);//INF*3不能溢出
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                originalEdge[i][j]=(i==j?0:INF);
    }
    void addEdge(int u,int v,int w)
    {
        dis[u][v]=dis[v][u]=originalEdge[u][v]=originalEdge[v][u]=min(originalEdge[u][v],w);
    }
    int run()
    {
        int ans=INF;
        for(int k = 1; k <= n; ++k)
        {
            for(int i = 1; i < k; ++i)
                for(int j = i+1; j < k; ++j)
                    ans=min(ans,dis[i][j]+originalEdge[i][k]+originalEdge[k][j]);
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
        return ans;
    }
};
```
## 有向图已知任意两点是否有连边，判断任意两点是否连通
如果x可以到达k，那么当k可以到达y，则x可以到达y
```cpp
bitset<N> f[N];
for (k = 1; k <= n; k++)
  for (i = 1; i <= n; i++)
    if (f[i][k]) f[i] = f[i] | f[k];
```

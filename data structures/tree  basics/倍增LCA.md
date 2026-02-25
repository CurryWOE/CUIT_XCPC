#! https://zhuanlan.zhihu.com/p/557878869
# 倍增LCA
倍增与其他求LCA的方法相比，优点是可以维护动态加叶子的树，缺点是不能修改
```cpp
const int N = 5e5 + 3;
const int M = 20;
struct EDGE
{
    int to, nxt;
};
struct LCA
{
    EDGE e[N << 1];
    int fa[N][M], dep[N], head[N];
    int tot;
    queue<int> q;
    void init(int n)
    {
        tot = 0;
        memset(head, 0, sizeof(int) * (n + 1));
        memset(dep, 0, sizeof(int) * (n + 1));
    }
    void AddEdge(int u, int v)
    {
        e[++tot] = {u, head[v]};
        head[v] = tot;
        e[++tot] = {v, head[u]};
        head[u] = tot;
    }
    void bfs(int root)
    {
        q.push(root);
        dep[root] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            int depth=bit_width((unsigned int)dep[u]);
            
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if (dep[v])
                    continue;
                q.push(v);
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                for(int j=1;j<depth;++j)
                    fa[v][j]=fa[fa[v][j-1]][j-1];
            }
        }
    }
    int lca(int x, int y)
    {
        if (dep[x] > dep[y])
            swap(x, y);
        for (int i = 0, dif = dep[y] - dep[x]; dif; ++i, dif >>= 1)
            if (dif & 1)
                y = fa[y][i];
        if (x == y)
            return x;
        for (int i = bit_width((unsigned int)dep[u])-1; i >= 0; --i)
        {
            if (fa[x][i] == fa[y][i])
                continue;
            x = fa[x][i];
            y = fa[y][i];
        }
        return fa[x][0];
    }
};
```
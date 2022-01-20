//按秩合并+路径压缩
inline void init(int n)
{
    memset(fa,-1,sizeof(int)*(n+1));
    for (int i = 1; i <= n; ++i)
        rank[i] = 1;
}
int find(int x)
{
    return fa[x] == -1 ? x : (fa[x] = find(fa[x]));
}
inline void merge(int i, int j)
{
    int x = find(i), y = find(j);
    if (rank[x] <= rank[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (rank[x] == rank[y] && x != y)
        rank[y]++;
}
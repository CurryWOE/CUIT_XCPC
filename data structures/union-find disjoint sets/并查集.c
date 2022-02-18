//按秩合并+路径压缩
/*
并查集加上按秩压缩和路径压缩的时间复杂度是O(log * n)
O(log * n)等于5时，n的范围是65536~2^65536，就是是说可以当作常数5来用
*/
int fa[MAXN],ran[MAXN];
inline void init(int n)
{
    memset(fa,-1,sizeof(int)*(n+1));
    memset(ran,0,sizeof(int)*(n+1));
}
int find(int x)
{
    return fa[x] == -1 ? x : (fa[x] = find(fa[x]));
}
inline void merge(int i, int j)
{
    int x = find(i), y = find(j);
    if (ran[x] <= ran[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (ran[x] == ran[y] && x != y)
        ran[y]++;
}
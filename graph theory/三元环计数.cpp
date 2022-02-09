/*
给定一张无重边、无自环的无向图

点数为n，边数为m，且n,m同阶

问有多少个无序三元组(i,j,k)，使得存在：

有一条连接i,j的边
有一条连接j,k的边
有一条连接k,i的边
首先要对所有的无向边进行定向，

对于任何一条边，从度数大的点连向度数小的点，如果度数相同，从编号小的点连向编号大的点

此时这张图是一个有向无环图

之后枚举每一个点u，然后将u的所有相邻的点都标记上“被u访问了”，

然后再枚举u的相邻的点v，然后再枚举v的相邻的点w，

如果w存在“被u访问了”的标记，那么(u,v,w)就是一个三元环了

而且每个三元环只会被计算一次
时间复杂度是O(n+m(1+\sqrt m))=O(m\sqrt m)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
int deg[N], vis[N], n, m, ans;
struct E { int u, v; } e[N * 3];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &e[i].u, &e[i].v);
        ++ deg[e[i].u], ++ deg[e[i].v];
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u, v = e[i].v;
        if(deg[u] < deg[v] || (deg[u] == deg[v] && u > v)) swap(u, v);
        g[u].push_back(v);
    }
    for(int x = 1 ; x <= n ; ++ x) {
        for(auto y: g[x]) vis[y] = x;
        for(auto y: g[x])
            for(auto z: g[y])
                if(vis[z] == x)
                    ++ ans;
    }
    printf("%d\n", ans);
}
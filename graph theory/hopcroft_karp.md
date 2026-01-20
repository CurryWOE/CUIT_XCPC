#! https://zhuanlan.zhihu.com/p/648828661
# Hopcroft-Karp
求二分图最大匹配的最快算法， $O(\sqrt V E)$
```cpp
struct HopcroftKarp
{
    std::vector<int> g, l, r;
    int ans;
    HopcroftKarp(int n, int m, const std::vector<array<int,2>> &e)
        : g(e.size()), l(n, -1), r(m, -1), ans(0)
    {
        std::vector<int> deg(n + 1);
        for (auto &[x, y] : e)
            deg[x]++;
        for (int i = 1; i <= n; i++)
            deg[i] += deg[i - 1];
        for (auto &[x, y] : e)
            g[--deg[x]] = y;

        std::vector<int> a, p, q(n);
        for (;;)
        {
            a.assign(n, -1), p.assign(n, -1);
            int t = 0;
            for (int i = 0; i < n; i++)
                if (l[i] == -1)
                    q[t++] = a[i] = p[i] = i;

            bool match = false;
            for (int i = 0; i < t; i++)
            {
                int x = q[i];
                if (~l[a[x]])
                    continue;
                for (int j = deg[x]; j < deg[x + 1]; j++)
                {
                    int y = g[j];
                    if (r[y] == -1)
                    {
                        while (~y)
                            r[y] = x, std::swap(l[x], y), x = p[x];
                        match = true, ans++;
                        break;
                    }

                    if (p[r[y]] == -1)
                        q[t++] = y = r[y], p[y] = x, a[y] = a[x];
                }
            }

            if (!match)
                break;
        }
    }
};
vector<array<int,2>> e;
e.push_back({i,j});
HopcroftKarp hk(n+1,m+1,e);//左部点是[0-n]，右部点是[0-m]，边是e
cout<<hk.ans;
```
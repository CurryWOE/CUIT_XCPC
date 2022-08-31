#! https://zhuanlan.zhihu.com/p/559793518
# ST表
符合结合律且可重复贡献的信息查询

可重复贡献：交集不为空的区间合并，不影响结果

倍增思想
# 时间复杂度
$O(nlogn)$ 预处理

$O(1)$ 查询
# 空间复杂度
$O(nlogn)$

# 板子
```cpp
const int N = 5e4 + 3;
const int M = log2(N) + 1;
struct SparseTable
{
    int st[N][M];
    int merge(int x, int y)
    {
        return min(x, y);
    }
    void init(int n)
    {
        int m=log2(n)+1;
        for (int i = 1; i <= n; ++i)
            st[i][0] = a[i];
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                st[j][i] = merge(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
    int query(int l, int r)
    {
        int s = __lg(r - l + 1);
        return merge(st[l][s], st[r - (1 << s) + 1][s]);
    }
}st;
```
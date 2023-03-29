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
const int M = __lg(N) + 1;
namespace SparseTable
{
    int st[M][N];
    void init(int n)
    {
        int m=__lg(n);
        memcpy(st[0],a,sizeof(int)*(n+1));
        for (int i = 1; i <=m; ++i)
        {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                st[i][j] = min(st[i-1][j], st[i-1][j + (1 << (i - 1))]);
        }
    }
    int query(int l, int r)
    {
        int s = __lg(r - l + 1);
        return min(st[s][l], st[s][r - (1 << s) + 1]);
    }
};
```
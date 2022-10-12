#! https://zhuanlan.zhihu.com/p/557880407

# LIS\&LCS

# 最长上升子序列 LIS

## 时间复杂度

$O(nlogn)$

```cpp
int arr[N],dp[N];
int lis(int n)
{
    int k = 1;
    dp[k] = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (dp[k] < arr[i])
            dp[++k] = arr[i];
        else
            *(upper_bound(dp + 1, dp + 1 + k, arr[i])) = arr[i];
    }
    return k;
}
```

dp[i] 表示长度 $i$ 的 LIS 的末尾最小元素

# 最长公共子序列 LCS

转化为 f 数组的 LIS 复杂度更低

## 时间复杂度

$O(nlogn)$

```cpp
unordered_map<int, vector<int>> d;
vector<int> f;
d.clear();
f.clear();
for (int i = 1; i <= n; ++i)
{
    if (d.count(a[i]) == 0)
        d[a[i]].push_back(-1);
}
for (int i = 1; i <= m; ++i)
{
    if (d.count(b[i]))
        d[b[i]].push_back(i);
}
for (int i = 1; i <= n; ++i)
{
    if (d[a[i]].size() > 1)
    {
        for (int j = d[a[i]].size() - 1; j > 0; --j)
            f.push_back(d[a[i]][j]);
    }
}
```

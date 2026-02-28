#! https://zhuanlan.zhihu.com/p/625095263
# 数位DP
从高位往低位，枚举每一位选什么，记忆化搜索，搜索时需要参数记录高位相关的信息

对于limit，要看情况选择是否记忆化，如果limit=1的状态数远小于limit=0的状态数，那就只记忆化limit=0的状态

区间 [l,r] 统计合法数个数的，通常用前缀和思想，即 ans[1,r]-ans[1,l-1]
## 常见参数
pos: int,表示当前枚举的位置，一般从高到低

limit: bool,表示枚举的第 pos 位是否受到限制（上限或下限）

last: int,表示上一位填写的值

lead0: bool,表示是否有前导零

sum: int,表示高位的数位和

rem: int,表示高位取模的余数

st: int,表示高位的一些信息（状态压缩）
```cpp
ll dp[MAXD][...];
ll dfs(int pos, ..., bool limit)
{
    if (!pos)
        return ...;
    ll &d = dp[pos][...];
    if (!limit && d != -1) return d;
    ll ans = 0;
    for (int v = (limit ? A[pos] : 9); v >=0 ; --v)
        ans += dfs(pos - 1, ..., limit && A[pos] == v);
    if (!limit) d = ans;
    return ans;
}
ll f(ll x)
{
    int len = 0;
    while (x) A[++len] = x % 10, x /= 10;
    return dfs(len, ..., true);
}
```
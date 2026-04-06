#! https://zhuanlan.zhihu.com/p/557879795
# 区间DP
对于删除中间区间会导致两边区间合并的（两边区间可以一起删的），状态(l,r,k)表示考虑区间l，r，l的左边有k个元素可以和l一起被删除

dfs序可以把子树信息转换为区间信息，反过来启示区间信息可以表示子树信息，区间DP可以判断一个区间能否表示一个满足题目限制的树

---
下面写法相比于 for len l,r mid ，代码短，缓存友好
```cpp
for(int l=n-1;l;--l)
    for(int r=l+1;r<=n;++r)
        for(int k=l;k<r;++k)
            dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
```
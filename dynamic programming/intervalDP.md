#! https://zhuanlan.zhihu.com/p/557879795
# 区间DP
对于删除中间区间会导致两边区间合并的（两边区间可以一起删的），状态(l,r,k)表示考虑区间l，r，l的左边有k个元素可以和l一起被删除
## 形式1
```cpp
for(int len=2;len<=n;++len)
    for(int l=1,r=len;r<=n;++l,++r)
        for(int k=l;k<r;++k)
            dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
```
## 形式2
```cpp
for(int l=n-1;l;--l)
    for(int r=l+1;r<=n;++r)
        for(int k=l;k<r;++k)
            dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
```
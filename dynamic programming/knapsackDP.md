#! https://zhuanlan.zhihu.com/p/557880236
# 背包DP
目前只有01的板子
```cpp
for(int i=0;i<n;++i)
{
    for(int j=W;j>=weight[i];--j)
        dp[j]=max(dp[j],dp[j-weight[i]]+value[i]);
}
```
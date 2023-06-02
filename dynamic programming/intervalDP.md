#! https://zhuanlan.zhihu.com/p/557879795
# 区间DP
对于删除中间区间会导致两边区间合并的（两边区间可以一起删的），可以记录区间l，r，（l左边，包括l），还有多少个可以和l这个点一起删除的元素
## 形式1
```cpp
for(int len=2;len<=n;++len)
{
    for(int l=1,r=len;r<=n;++l,++r)
    {
        for(int k=l;k<r;++k)
            dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
    }
}
```
## 形式2
```cpp
for(int l=n-1;l;--l)
{
    for(int r=l+1;r<=n;++r)
    {
        for(int k=l;k<r;++k)
            dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
    }
}
```
# 四边形不等式优化
$f_{l,r}=\min_{k=l}^{r-1}{f_{l,k}+f_{k+1,r}}+w(l,r)$
## 区间包含单调性
$\forall l_1\le l_2 \le r_1 \le r_2$，$w(l_2,r_1)\le w(l_1,r_2)$
## 四边形不等式
$\forall l_1\le l_2 \le r_1 \le r_2$，$w(l_1,r_1)+w(l_2,r_2)\le w(l_1,r_2)+w(l_2,r_1)$
## 定理
如果$w(l,r)$满足区间包含单调性和四边形不等式，记$H_{l,r}$表示最优决策点，有$H_{l,r-1}\le H_{l,r}\le H_{l+1,r}$

## 应用
```cpp
for(int len=2;len<=n;++len)
{
    for(int l=1,r=len;r<=n;++l,++r)
    {
        for(int k=H[l][r-1];k<=H[l+1][r];++k)
        {
            if(dp[l][r]>dp[l][k]+dp[k+1][r])
            {
                dp[l][r]=dp[l][k]+dp[k+1][r];
                H[l][r]=k;
            }
        }
    }
}
```
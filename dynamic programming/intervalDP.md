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
# 四边形不等式优化
## 四边形不等式
$\forall l_1\le l_2 \le r_1 \le r_2$，$w(l_1,r_1)+w(l_2,r_2)\le w(l_1,r_2)+w(l_2,r_1)$
## 问题形式
### 问题形式4(n个长度为1的区间两两合并，直到得到区间[1,n])与决策单调性3

$$f(l,r)=\min\limits_{mid=l}^{r-1}f(l,mid)+f(mid+1,r)+w(l,r)$$

$$\forall l+1<r, opt(l,r-1)\le opt(l,r)\le opt(l+1,r)$$

暴力复杂度为 $O(n^3)$。若 $w$ 满足四边形不等式和区间包含单调性，则问题形式4满足决策单调性3，复杂度为 $O(n^2)$
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
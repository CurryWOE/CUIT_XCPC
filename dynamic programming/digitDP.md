#! https://zhuanlan.zhihu.com/p/625095263
# 数位DP
从高位往低位，枚举每一位选什么，记忆化搜索，搜索需要参数记录前缀相关的信息

只记忆化不贴着上界没有前导0的情况

区间 [l,r] 统计合法数个数的，通常用前缀和思想，即 ans[1,r]-ans[1,l-1]
## 前缀相关信息
区间限制：高位选择是否贴着区间上限，如果不贴着，该位可以随便选，否则不能超过区间上限

前导0：当该位及高位都是0，那么该位是前导0，如果统计的是digit，不计入答案

hdu2089不要62：上一位选的什么

洛谷P2602：当前要计算的数字，在高位选择了多少个
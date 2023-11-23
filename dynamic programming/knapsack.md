#! https://zhuanlan.zhihu.com/p/625095842
# 背包问题
a,b互质，不能表示的最大体积是ab-a-b
# 01背包
```cpp
struct obj
{
    int w,v;
}a[N];
for(int i=0;i<n;++i)
{
    for(int j=W;j>=a[i].w;--j)
        dp[j]=max(dp[j],dp[j-a[i].w]+a[i].v);
}
```
# 完全背包
```cpp
for(int i=0;i<n;++i)
{
    for(int j=a[i].w;j<=W;++j)
        dp[j]=max(dp[j],dp[j-a[i].w]+a[i].v);
}
```
# 多重背包
## 二进制优化
```cpp
struct originalObj
{
    int w,v,num;
}a[N];
vector<obj> b;//对b做01背包
for(int i=0;i<n;++i)
{
    for(int j=1;a[i].num>j;j*=2)
    {
        a[i].num-=j;
        b.push_back({a[i].w*j,a[i].v*j});
    }
    b.push_back({a[i].w*a[i].num,a[i].v*a[i].num});
}
```
## 单调队列优化
$dp[j]$ 由 $dp[j-k*v[i]],v\in cnt[i]$ 转移而来。尝试将 j 改变一，看看它决策集合的变化。发现和原来决策集合没有交集，仅仅是平移了一位。所以模 $v[i]$ 余数相同的 j 才会影响转移，不同的不会。
```cpp
for (int i = 1; i <= n; ++i)
{
    memcpy(g,f,sizeof(f));
    for (int rem = 0; rem < v[i]; ++rem)
    {
        deque<int> q;
        for (int j = rem; j <= W; j += v[i])
        {
            if (!q.empty() && q.front() < j - cnt[i] * v[i])
                q.pop_front();
            if(!q.empty())
                f[j]=max(g[j],g[q.front()]+(j-q.front())/v[i]*w[i]);
            while (!q.empty() && g[q.back()] +(j- q.back()) / v[i] * w[i] <= g[j])
                q.pop_back();
            q.push_back(j);
        }
    }
}
```
# 混合背包
```cpp
for (循环物品种类) {
  if (是 0 - 1 背包)
    套用 0 - 1 背包代码;
  else if (是完全背包)
    套用完全背包代码;
  else if (是多重背包)
    套用多重背包代码;
}
```
# 超大背包小重量物品，无限背包
只需做容量 $min(背包原始容量,全部种类物品重量的LCM)$ 的背包，剩下全部贪心选性价比最高的

如果其他种类物品总共用了LCM的倍数的体积，就可以换成性价比最高的
# 回退背包
背包本身不考虑顺序，可以当作要消除的物品是最后一个物品，逆向转移回去即可消除一个物品的影响（加号变减号，转移顺序相反）
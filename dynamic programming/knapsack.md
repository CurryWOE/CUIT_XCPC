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
```cpp
struct originalObj
{
    int w,v,num;
}a[N];
vector<obj> b;
for(int i=0;i<n;++i)
{
    for(int j=1;a[i].num>j;j*=2)
    {
        a[i].num-=j;
        b.push_back({a[i].w*j,a[i].v*j});
    }
    b.push_back({a[i].w*a[i].num,a[i].v*a[i].num});
}
//对b做01背包
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
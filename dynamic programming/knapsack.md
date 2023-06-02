#! https://zhuanlan.zhihu.com/p/625095842
# 背包问题
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
# 大背包小重量物品
设w=背包原始容量，L=物品重量的LCM，W=物品重量的种类*L

特别地，如果全部装得下，就直接输出答案

做法是第 $i$ 个物品留下 $min(cnt_i,\frac Li)$ 个，用来背包

没留下的物品贪心放容量 $max(0,w-L)$ 的背包，设占据了ans容量

留下的物品做 W 容量的背包，最后在容量 [0,w-ans] 取答案
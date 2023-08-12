#! https://zhuanlan.zhihu.com/p/579077838
# 判断质数
# 试除法
```c++
bool isprime(int i)
{
    if(i<2 || i%2==0 && i!=2)
        return 0;
    int sq=sqrt(i);
    for(int k=3;k<=sq;k+=2)
    {
        if(i%k==0)
            return false;
    }
    return true;
}
```
# 米勒-拉宾素性检验
[原理](https://zhuanlan.zhihu.com/p/220203643)

这是一种概率算法，但是固定底数可以确保一定范围内正确

$2^{32}$ 以内，$2,7,61$

$2^{64}$ 以内，$2,325,9375,28178,450775,9780504,1795265022$

$2^{78}$ 以内，$2,3,5,7,11,13,17,19,23,29,31,37$
## 时间复杂度
$O(klog n)$

但因为我们使用了固定的一组数，所以 $k=7$
```c++
typedef unsigned long long ll;
ll fastPower(ll a, ll n, ll p)
{
    ll ans = 1;
    for(;n;n>>=1)
    {
        if (n & 1)
            ans = (__int128)ans * a % p; // 注意！中间结果可能溢出，需要使用__int128过渡
        a = (__int128)a * a % p;
    }
    return ans;
}
bool Miller_Rabin(ll x)
{
    if (x < 3)
        return x == 2;
    if ((x&1) == 0)
        return false;
    ll v,r=__builtin_ctz(x-1),d=x>>r;
    for (ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
    {
        v = fastPower(a, d, x);
        if (v <= 1 || v == x - 1)
            continue;
        for (int i = 0; i < r; ++i)
        {
            v = (__int128)v * v % x; // 同样使用__int128过渡
            if (v == x - 1 && i != r - 1)
            {
                v = 1;
                break;
            }
            if (v == 1)
                return false;
        }
        if (v != 1)
            return false;
    }
    return true;
}
```
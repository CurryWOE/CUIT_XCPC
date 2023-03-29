#! https://zhuanlan.zhihu.com/p/579072505
# pollard-rho
$O(n^{\frac 14})$ 得找到 $x$ 的一个非1非本身的因子
```cpp
ll fastPower(ll x, ll n, ll p)
{
    ll s = 1;
    for (; n; n >>= 1)
    {
        if (n & 1)
            s = (__int128)s*x%p;
        x=(__in128)x*x%p;
    }
    return s;
}
ll pollardRho(ll n)
{
    auto f = [&](ll x) { return (__int128)x*x%n + 1; };
    ll p = 2, q;
    for (ll i = 1, x = 0, y = 0, t = 0; t++ % 255 || __gcd(p, n) == 1; x = f(x), y = f(f(y)))
    {
        if (x == y)
        {
            x = i++;
            y = f(x);
        }
        q = (__int128)p*abs(x - y)%n;
        if (q)
            p = q;
    }
    return __gcd(p, n);
}
bool millerRabin(ll x)
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
ll ans=2;
void maxfactor(ll n)
{
    if (n<ans)
        return;
    if (millerRabin(n))
    {
        ans=n;
        return;
    }
    ll t = pollardRho(n);
    maxfactor(t);
    maxfactor(n / t);
}
ll ans=INF;
void minfactor(ll n)
{
    if (millerRabin(n))
    {
        ans=min(ans,n);
        return;
    }
    ll t = pollardRho(n);
    maxfactor(t);
    maxfactor(n / t);
}
vector<ll> factor;
void allfactor(ll n)
{
    if (millerRabin(n))
    {
        factor.push_back(n);
        return;
    }
    ll t = pollardRho(n);
    maxfactor(t);
    maxfactor(n / t);
}
```
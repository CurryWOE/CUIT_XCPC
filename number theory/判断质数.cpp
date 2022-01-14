/*
part 1
试除法：
判断素数
时间复杂度O(sqrt(n))
*/
int isprime(int i)
{
    if((i&1)==0 && i!=2 || i<2)
        return 0;
    int sq=sqrt(i),k;
    for(k=3;k<=sq;k+=2)
    {
        if(i%k==0)
            return 0;
    }
    return 1;
}
/*
part 2
米勒-拉宾素性检验（Miller–Rabin primality test）:
原理见
https://zhuanlan.zhihu.com/p/220203643
这是一种概率算法，
但是，Jim Sinclair发现了一组数：2, 325, 9375, 28178, 450775, 9780504, 1795265022。
用它们做 a ， 2^64 以内不会出错，我们使用这组数，就不用担心运气太差了。
时间复杂度O(klog n)
但因为我们使用了固定的一组数，所以 k=7
*/
typedef unsigned long long ll;
ll qpow(ll a, ll n, ll p) // 快速幂
{
    ll ans = 1;
    while (n)
    {
        if (n & 1)
            ans = (__int128)ans * a % p; // 注意！中间结果可能溢出，需要使用__int128过渡
        a = (__int128)a * a % p;
        n >>= 1;
    }
    return ans;
}
bool Miller_Rabin(ll x)
{
    if (x < 3) // 特判1，2
        return x == 2;
    if (x % 2 == 0) // 特判偶数
        return false;
    ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d = x - 1, r = 0;
    while (d % 2 == 0) // 算出d, r 
        d /= 2, ++r;
    // 或：r = __builtin_ctz(d), d >>= r;
    for (auto a : A)
    {
        ll v = qpow(a, d, x); // a^d
        // 如果a^d≡0，说明是a是x的倍数；如果a^d≡1或-1，说明这串数接下来一定都是1，不用继续计算
        if (v <= 1 || v == x - 1) 
            continue;
        for (int i = 0; i < r; ++i)
        {
            v = (__int128)v * v % x; // 同样使用__int128过渡
            if (v == x - 1 && i != r - 1) // 得到-1，说明接下来都是1，可以退出了
            {
                v = 1;
                break;
            }
            // 在中途而非开头得到1，却没有经过-1，说明存在其他数字y≠-1满足y^2≡1，则x一定不是奇素数
            if (v == 1)  
                return false;
        }
        if (v != 1) // 查看是不是以1结尾
            return false;
    }
    return true;
}
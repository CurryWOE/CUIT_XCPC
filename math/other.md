#! https://zhuanlan.zhihu.com/p/563147047

# 数论杂

# 线性回归

一堆点 $(x_i,y_i)$ ，求一条直线 $F(x):y=Ax+B$ ，使得 $\sum\limits_{i=1}^n (y_i-F(x_i))^2$ 最小

设 $\overline{x}=\frac{\sum\limits_{i=1}^n x_i}n$ ， $\overline{y}=\frac{\sum\limits_{i=1}^n y_i}n$

$A=\frac{\sum\limits_{i=1}^n x_iy_i-n\overline{x} \overline{y}}{\sum\limits_{i=1}^n x_i^2-n\overline{x}^2}$

$B=\overline{y}-A\overline{x}$

# 自然数幂和
$\sum\limits_{i=1}^n i=n(n+1)/2$

$\sum\limits_{i=1}^n i^2=n(n+1)(2n+1)/6$

$\sum\limits_{i=1}^n i^3=n^2(n+1)^2/4$

$\sum\limits_{i=1}^n i^4=n(n+1)(6n^3+9n^2+n-1)/30$

$\sum\limits_{i=1}^n i^5=n^2(n+1)(2n^3+4n^2+n-1)/12$

## 递推式推导

设 $f_n^p=\sum\limits_{i=1}^n i^{p}$

$(n+1)^p-n^p=C_p^1n^{p-1}+C_p^2n^{p-2}+...+1$

$\sum\limits_{n=1}^m(n+1)^p-n^p=\sum\limits_{n=1}^mC_p^1n^{p-1}+C_p^2n^{p-2}+...+1$

$(m+1)^p-1=C_p^1f_m^{p-1}+C_p^2f_m^{p-2}+...+m$

$f_m^{p-1}=((m+1)^p-1-(C_p^2f_m^{p-2}+...+m))/C_p^1$

$f_m^{p}=((m+1)^{p+1}-1-(C_{p+1}^2f_m^{p-1}+...+m))/(p+1)$
## 求法
### 拉格朗日插值
如果有取模，那么模数必须质数

自然数k次幂和是k+1次函数，求前k+2个点的点值，插就完了
```cpp
const int N=1e6+3;
const ll mod=1e9+7;
long long fac[N],inv[N];
long long fast_power(long long base, long long exponent)
{
    long long result = 1;
    for (; exponent > 0; exponent >>= 1)
    {
        if (exponent & 1)
            result = result * base % mod;
        base = base * base % mod;
    }
    return result;
}
void getC()
{
    fac[0]=1;
    for(int i=1;i<N;++i)
        fac[i]=fac[i-1]*i%mod;
    inv[N-1]=fast_power(fac[N-1],mod-2);
    for(int i=N-1;i;--i)
        inv[i-1]=inv[i]*i%mod;
}
struct lagrange
{
    ll y[N],pre[N],suf[N];
    ll lag(ll m,int k)//g(m)，k个点
    {
        if(m<=k)
            return y[m];
        pre[0]=suf[k+1]=1;
        for(int i=1;i<k;++i)
            pre[i]=pre[i-1]*(m-i)%mod;
        for(int i=k;i>1;--i)
            suf[i]=suf[i+1]*(m-i)%mod;
        ll ans=0;
        for(int i=1;i<=k;++i)
            ans=(ans+y[i]*inv[i-1]%mod*inv[k-i]%mod*pre[i-1]%mod*suf[i+1]%mod*((k-i)&1?-1:1))%mod;
        return (ans+mod)%mod;
    }
}la;
getC();
for(int i=1;i<=k+2;++i)
    la.y[i]=(la.y[i-1]+fast_power(i,k))%mod;
cout<<la.lag(n,k+2);
```
### 第2类斯特林数
不需要逆元

$\sum\limits_{i=1}^ni^k=\sum\limits_{j=0}^{k}S_2(k,j)\frac{(n+1)^{\underline{j+1}}}{j+1}$
```cpp
struct powersum
{
    int k;
    ll s[K][K];
    void init(int kk)
    {
        k=kk;
	    s[0][0]=1;
	    for(int i=1;i<=k;++i)
		    for(ll j=1;j<=i;++j)
			    s[i][j]=s[i-1][j-1]+j*s[i-1][j];
    }
    ll cal(ll n)
    {
        ll res,ans=0;
        for(ll i=0;i<=k;++i)
        {
            res=s[k][i];
            for(ll j=0;j<=i;++j)
            {
                if((n+1-j)%(i+1))
                    res=res*(n+1-j);
                else
                    res=res*((n+1-j)/(i+1));
            }
            ans=ans+res;
        }
        return ans;
    }
};
```
# 调和级数近似公式

n 很大时

$f_n\approx \ln n+0.5772156649+\frac 1{2n}$

```cpp
log(n)+0.5772156649+1.0/(2*n)
```
# 狄利克雷前后缀
$O(n\log\log n)$

原缀已知 $a$，求 $b$

逆缀已知 $b$，求 $a$

答案保存在原数组上
## 狄利克雷前缀
$b_n=\sum\limits_{d|n}a_d$
```cpp
for(int i=1;i<=cnt && primes[i]<=n;++i)
{
    for(int j=1;j*primes[i]<=n;++j)
        a[j*primes[i]]+=a[j];
}
```
## 狄利克雷后缀
$b_d=\sum\limits_{d|n}a_n$
```cpp
for(int i=1;i<=cnt && primes[i]<=n;++i)
{
    for(int j=n/primes[i];j;--j)
        a[j]+=a[j*primes[i]];
}
```
## 逆狄利克雷前缀
$b_n=\sum\limits_{d|n}a_d$
```cpp
for(int i=cnt;i;--i)
{
    for(int j=n/primes[i];j;--j)
        a[j*primes[i]]-=a[j];
}
```
## 逆狄利克雷后缀
$b_d=\sum\limits_{d|n}a_n$
```cpp
for(int i=cnt;i;--i)
{
    for(int j=1;j*primes[i]<=n;++j)
        a[j]-=a[j*primes[i]];
}
```

---
```cpp
const long long N=1e18+1;
const long long N=1e18+(long double)1;
```
上面这个会丢精度，需要改成下面那个

---
n以内两点互质连边，连到m条边停止，可以两层循环，复杂度是 $O(min(n^2,m) log n)$ ，因为互质的还蛮多的

# 最大质因子个数和最大因子个数
$n\le$|$10^1$|$10^2$|$10^3$|$10^4$|$10^5$|$10^6$|$10^7$|$10^8$|$10^9$|
---|---|---|---|---|---|---|---|---|---
$max\{w(n)\}$|2|3|4|5|6|7|8|8|9
$max\{d(n)\}$|4|12|32|64|128|240|448|768|1344

$n\le$|$10^{10}$|$10^{11}$|$10^{12}$|$10^{13}$|$10^{14}$|$10^{15}$|$10^{16}$|$10^{17}$|$10^{18}$|
---|---|---|---|---|---|---|---|---|---
$max\{w(n)\}$|10|10|11|12|12|13|13|14|15
$max\{d(n)\}$|2304|4032|6720|10752|17280|26880|41472|64512|103680
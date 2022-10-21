#! https://zhuanlan.zhihu.com/p/573279411
# min_25筛
求积性函数 $f(n)$ 前缀和 $\sum\limits_{i=1}^nf(i)$

>以下p表示质数
## 限制
$f(p)$ 是一个最高次数低，关于 $p$ 的多项式，即 $f(p)=\sum\limits_{j=0}^{\infty}coe_jp^j$

$f(p^k)$ 可以快速计算
# 第1部分
自己设一个完全积性函数 $f'$，要求 $f'(p)=f(p)$

>以下$p_j$表示第 $j$ 个质数，$p_1=2$，特别地，$p_0=1$  
>以下 $minp(i)$ 表示 $i$ 的最小质因子，特别地，$minp(1)=0$

min25想了一个关于 $f'$ 的函数 $g(n,j)=\sum\limits_{i=1}^n[i\in prime 或者 p_j<minp(i)]f'(i)$

考虑DP求解这个函数，从 $g(n,j-1)\rightarrow g(n,j)$ 的转移过程中，少了 $p_j=minp(i)$ 的合数的贡献，即

$\sum\limits_{i=p_j^2}^n[p_j=minp(i)]f'(i)$

当 $p_j^2>n$ 上式为0，即 $g(n,j)=g(n,j-1)$

考虑 $p_j\le\lfloor\sqrt n\rfloor$ 的情况

$i$ 分解成 $p_j$ 和另一个数的乘积，上式变成

$\sum\limits_{k=p_j}^{\lfloor\frac n{p_j}\rfloor}[p_j\le minp(k)]f'(p_jk)$

由于 $f'$ 是完全积性函数，所以把 $f'(p_jk)$ 拆开，即

$f'(p_j)\sum\limits_{k=p_j}^{\lfloor\frac n{p_j}\rfloor}[p_j\le minp(k)]f'(k)$

上式的后半部分和 $g(\frac n{p_j},j-1)$ 相比，产生贡献的合数一样，质数计算了大于等于 $p_j$ 的，即，少了 $\sum\limits_{i=1}^{j-1}f'(p_i)$

所以上式改写成

$f'(p_j)(g(\frac n{p_j},j-1)-\sum\limits_{i=1}^{j-1}f'(p_i))$

整理一下

$g(n,j)=\begin{cases}g(n,j-1)&p_j^2>n\\g(n,j-1)-f'(p_j)(g(\frac n{p_j},j-1)-\sum\limits_{i=1}^{j-1}f'(p_i))&otherwise\end{cases}$

由上式知，需要所有的 $g(\frac n{p_j},j-1)$，而且还需要递归处理子问题

但是有一个重要结论 $\lfloor\frac{\lfloor\frac na\rfloor}{b}\rfloor=\lfloor\frac n{ab}\rfloor$，所以子问题个数是 $O(\sqrt n)$的
## 证明
$\lfloor\frac nx\rfloor$最多 $2\sqrt n$个

当 $x\le \sqrt n$ ，因为 $x$ 最多 $\sqrt n$ 个，所以$\lfloor\frac nx\rfloor$最多 $\sqrt n$个

当 $x> \sqrt n$ ，因为 $\lfloor\frac nx\rfloor\le\sqrt n$，所以$\lfloor\frac nx\rfloor$最多 $\sqrt n$个

# 第2部分
min25又想了一个关于 $f$ 的函数 $S(n,j)=\sum\limits_{i=1}^n[p_j<minp(i)]f(i)$

把 $i$ 分成质数和合数讨论（1的贡献最后加上）

质数的贡献：

$\sum\limits_{p}^nf(p)-\sum\limits_{i=1}^jf(p_i)$

由于 $f(p)=f'(p)$，所以上式等于

$g(n,+\infty)-\sum\limits_{i=1}^jf(p_i)$

合数的贡献：

合数 $x$ 可以唯一表示为 $minp(x)^k\times i$

要求 $minp(i)>p$

如果 $minp(i)<p$，$p$ 就不是 $x$ 的最小质因子

如果 $minp(i)=p$，$x$ 就不能唯一表示

$\sum\limits_{p}^{\lfloor\sqrt n\rfloor}\sum\limits_{k=1}^{\lfloor log_pn\rfloor}[k>1]f(p^k)+\sum\limits_{i=p+1}^{\lfloor\frac{n}{p^k}\rfloor}[minp(i)>p]f(p^k\times i)$

因为 $f$ 是积性函数，所以把 $p^k*i$ 拆开来

$\sum\limits_{p}^{\lfloor\sqrt n\rfloor}\sum\limits_{k=1}^{\lfloor log_pn\rfloor}[k>1]f(p^k)+f(p^k)\sum\limits_{i=p+1}^{\lfloor\frac{n}{p^k}\rfloor}[minp(i)>p]f(i)$

$\sum\limits_{j=1}^{+\infty}\sum\limits_{k=1}^{\lfloor log_{p_j}n\rfloor}[k>1]f(p_j^k)+f(p_j^k)\sum\limits_{i=p_j+1}^{\lfloor\frac{n}{p_j^k}\rfloor}[minp(i)>p_j]f(i)$

$\sum\limits_{j=1}^{+\infty}\sum\limits_{k=1}^{\lfloor log_{p_j}n\rfloor}f(p_j^k)(S(\frac n{p_j^k},j)+[k>1])$

整理一下

$S(n,j)=g(n,+\infty)-\sum\limits_{i=1}^jf(p_i)+\sum\limits_{k>j}^{+\infty}\sum\limits_{i=1}^{\lfloor log_{p_k}n\rfloor}f(p_k^i)(S(\frac n{p_k^i},k)+[i>1])$

---
$\sum\limits_{i=1}^nf(i)=S(n,0)+1$
# 实现
把 $f(p)$ 的多项式拆成单项式 $f_1(p),f_2(p),...$，有几个单项式就有几个要预处理的数组

线性筛预处理 $\lfloor\sqrt n\rfloor$ 内的质数，预处理 $sum_j=\sum\limits_{i=1}^{p_i\le\lfloor\sqrt n\rfloor}f_j(p_i)$

预处理所有需要的 $g_j(m,0)$，根据对 $g_j(m,0)$ 的个数的证明，开两个数组分别记录 $m>\sqrt n$，和 $m\le\sqrt n$ 的 $g_j(m,0)$

预处理 $g_j(m,0)=\sum\limits_{i=2}^mf_j'(i)$，整除分块来顺序求出所有的 $m$

需要 $g(m,+\infty)$,知道 $g(m,0)$，按照第1部分DP去转移

根据最后那个式子递归处理，记得+1
```cpp
const int N=1e5+3;
const int M=1e4;//N以内质数个数
const ll mod=1e9+7;
const ll inv2=500000004;
const ll inv6=166666668;
bitset<N> v;
int cnt;
ll p[M];
void seive()
{
	cnt=0;
	for(int i=2;i<N;++i)
	{
		if(!v[i])
			p[++cnt]=i;
		for(int j=1;j<=cnt && i*p[j]<N;++j)
		{
			v[i*p[j]]=true;
			if(i%p[j]==0)
				break;
		}
	}
}
struct min25
{
    ll n,sum1[M],sum2[M];
    ll w[N<<1],g1[N<<1],g2[N<<1];
    int id1[N],id2[N],tot,sq;
    int getid(ll x)
    {
        if(x<=sq)
            return id1[x];
        return id2[n/x];
    }
    ll f1(ll x)//f_1'(p)
    {
        return x;
    }
    ll f2(ll x)//f_2'(p)
    {
        return x*x%mod;
    }
    ll presumff1(ll x)//\sum\limits_{i=2}^xf_1'(i)
    {
        x%=mod;
        return x*(x+1)%mod*inv2%mod-1;
    }
    ll presumff2(ll x)//\sum\limits_{i=2}^xf_2'(i)
    {
        x%=mod;
        return x*(x+1)%mod*(2ll*x%mod+1)%mod*inv6%mod-1;
    }
    ll pk(ll x)//f(p^k)
    {
        x%=mod;
        return x*(x-1)%mod;
    }
    ll func(ll x1,ll x2)//单项式组合成多项式
    {
        return (x2-x1)%mod;
    }
    ll S(ll x,int j)
    {
        if(p[j]>x)
            return 0;
        ll sp,ans=(func(g1[getid(x)],g2[getid(x)])-func(sum1[j],sum2[j]))%mod;
        for(int i=j+1;i<=cnt && p[i]*p[i]<=x;++i)
        {
            sp=p[i];
            for(int e=1;sp<=x;sp*=p[i],++e)
                ans=(ans+pk(sp)*(S(x/sp,i)+(e>1))%mod)%mod;
        }
        return (ans+mod)%mod;
    }
    void init()
    {
        for(int i=1;i<=cnt;++i)
        {
            sum1[i]=(sum1[i-1]+f1(p[i]))%mod;
            sum2[i]=(sum2[i-1]+f2(p[i]))%mod;
        }
    }
    ll cal(ll nn)
    {
        tot=0;
        n=nn;
        sq=sqrt(n);
        for(ll r,m,l=1;l<=n;l=r+1)
        {
            r=n/(n/l);
            w[tot]=m=n/l;
            g1[tot]=presumff1(m);
            g2[tot]=presumff2(m);
            if(m<=sq)
                id1[m]=tot;
            else
                id2[n/m]=tot;
            ++tot;
        }
        for(int i=1;i<=cnt;++i)
        {
            for(int j=0;j<tot && p[i]*p[i]<=w[j];++j)
            {
                g1[j]=(g1[j]-f1(p[i])*(g1[getid(w[j]/p[i])]-sum1[i-1])%mod)%mod;
                g2[j]=(g2[j]-f2(p[i])*(g2[getid(w[j]/p[i])]-sum2[i-1])%mod)%mod;
            }
        }
        return (S(n,0)+1)%mod;
    }
}m2;
seive();
m2.init();
m2.cal();
```
修改6个注释的函数

---
下面是一个可能会用到的板子，求 $n$ 以内素数个数，要求预处理 $\sqrt n$ 以内的素数，9e10需要0.5s
```cpp
const int N=1e5;
const int M=1e4;//N以内质数个数
bitset<N> v;
int cnt;
ll p[M];
void seive()
{
	cnt=0;
	for(int i=2;i<N;++i)
	{
		if(!v[i])
			p[++cnt]=i;
		for(int j=1;j<=cnt && i*p[j]<N;++j)
		{
			v[i*p[j]]=true;
			if(i%p[j]==0)
				break;
		}
	}
}
struct min25
{
    ll n;
    ll w[N<<1],g[N<<1];
    int id1[N],id2[N],tot,sq;
    int getid(ll x)
    {
        if(x<=sq)
            return id1[x];
        return id2[n/x];
    }
    ll cal(ll nn)
    {
        if(nn<2)
            return 0;
        n=nn;
        tot=0;
        sq=sqrt(n);
        for(ll r,m,l=1;l<=n;l=r+1)
        {
            r=n/(n/l);
            w[tot]=m=n/l;
            g[tot]=m-1;
            if(m<=sq)
                id1[m]=tot;
            else
                id2[n/m]=tot;
            ++tot;
        }
        for(int i=1;i<=cnt;++i)
        {
            for(int j=0;j<tot && p[i]*p[i]<=w[j];++j)
                g[j]=g[j]-(g[getid(w[j]/p[i])]-i+1);
        }
        return g[0];
    }
}m2;
```
# trick
对于 $f(p)$ 的单项式去掉常数是完全积性函数，可以取去掉常数的单项式作为 $f'(p)$，计算完 $g(n,+\infty)$ 和 $sum$ 之后给这两个再乘上常数（因为只计算质数的贡献），例如 $f(p)=3$，取 $f'(p)=1$，这样就凑出完全积性函数常数函数了
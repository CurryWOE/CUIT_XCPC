#! https://zhuanlan.zhihu.com/p/573279411
# min_25筛
>此篇为 $O(\frac {n^{\frac 34}}{\log n})$ 的版本，$O(n^{\frac 23})$ 的见[这里](https://zhuanlan.zhihu.com/p/60378354)

求积性函数 $f(n)$ 前缀和 $\sum\limits_{i=1}^nf(i)$

>以下p表示质数
## 限制
$f(p)$ 是一个最高次数低，关于 $p$ 的多项式，即 $f(p)=\sum\limits_{j=0}^{\infty}coe_jp^j$

$f(p^k)$ 可以快速计算
## 第1部分
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
### 证明
$\lfloor\frac nx\rfloor$最多 $2\sqrt n$个

当 $x\le \sqrt n$ ，因为 $x$ 最多 $\sqrt n$ 个，所以$\lfloor\frac nx\rfloor$最多 $\sqrt n$个

当 $x> \sqrt n$ ，因为 $\lfloor\frac nx\rfloor\le\sqrt n$，所以$\lfloor\frac nx\rfloor$最多 $\sqrt n$个

## 第2部分
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

$\sum\limits_{p}^{\lfloor\sqrt n\rfloor}\sum\limits_{k=1}^{\lfloor log_pn\rfloor}\left([k>1]f(p^k)+\sum\limits_{i=p+1}^{\lfloor\frac{n}{p^k}\rfloor}[minp(i)>p]f(p^k\times i)\right)$

因为 $f$ 是积性函数，所以把 $p^k*i$ 拆开来

$\sum\limits_{p}^{\lfloor\sqrt n\rfloor}\sum\limits_{k=1}^{\lfloor log_pn\rfloor}\left([k>1]f(p^k)+f(p^k)\sum\limits_{i=p+1}^{\lfloor\frac{n}{p^k}\rfloor}[minp(i)>p]f(i)\right)$

$\sum\limits_{j=1}^{+\infty}\sum\limits_{k=1}^{\lfloor log_{p_j}n\rfloor}f(p_j^k)\left([k>1]+\sum\limits_{i=p_j+1}^{\lfloor\frac{n}{p_j^k}\rfloor}[minp(i)>p_j]f(i)\right)$

$\sum\limits_{j=1}^{+\infty}\sum\limits_{k=1}^{\lfloor log_{p_j}n\rfloor}f(p_j^k)(S(\frac n{p_j^k},j)+[k>1])$

整理一下

$S(n,j)=g(n,+\infty)-\sum\limits_{i=1}^jf(p_i)+\sum\limits_{k>j}^{+\infty}\sum\limits_{i=1}^{\lfloor log_{p_k}n\rfloor}f(p_k^i)(S(\frac n{p_k^i},k)+[i>1])$

$k>j$ 是因为 $minp(x)>p_j$

---
$\sum\limits_{i=1}^nf(i)=S(n,0)+1$
## 实现
把 $f(p)$ 的多项式拆成单项式 $f_1(p),f_2(p),...$，有几个单项式就有几个要预处理的数组

线性筛预处理 $\lfloor\sqrt n\rfloor$ 内的质数，预处理 $sum_j=\sum\limits_{i=1}^{p_i\le\lfloor\sqrt n\rfloor}f_j(p_i)$

预处理 $g_j(m,0)=\sum\limits_{i=2}^mf_j'(i)$，整除分块来顺序求出所有的 $m$

根据对 $g_j(m,0)$ 的个数的证明，开两个数组分别记录 $m>\sqrt n$，和 $m\le\sqrt n$ 的 $g_j(m,0)$

需要 $g(m,+\infty)$,知道 $g(m,0)$，按照第1部分去转移,此时计算了各个 $\frac nx$ 内质数的贡献

计算和数的贡献，按照第2部分去转移

如果1有贡献，记得加上

使用时修改带注释的函数，f1(x),f2(x)只在x是质数时调用
```cpp
const int N=1e5+3;//根号n
const int M=1e4;//根号n以内质数个数
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
## 拆常数
对于 $f(p)$ 的单项式去掉常数是完全积性函数，可以取去掉常数的单项式作为 $f'(p)$，计算完 $g(n,+\infty)$ 和 $sum$ 之后，给这两个再乘上常数（因为只计算质数的贡献），例如 $f(p)=3$，取 $f'(p)=1$，这样就凑出完全积性函数常数函数了

>一定要记得两个乘回去

## 拆条件
对于 $f(x)=[条件]F(x)$，$F(x)$ 是积性函数的，可以取去掉条件的单项式作为 $f'(p)$，在计算第2部分的时候，对于质数的贡献，质数幂的贡献乘上条件，即

$S(n,j)=[条件]\left(g(n,+\infty)-\sum\limits_{i=1}^jf(p_i)\right)+\sum\limits_{k>j}^{+\infty}\sum\limits_{i=1}^{\lfloor log_{p_k}n\rfloor}f(p_k^i)(S(\frac n{p_k^i},k)+[条件][i>1])$

## 例题选讲
[n以内素数个数](https://vjudge.net/problem/LibreOJ-6235)

[洛谷的同一题目](https://www.luogu.com.cn/problem/P1835)

因为 $f(p)=1$ ，所以 $f'(i)=1$，$\sum\limits_{i=2}^n f'(i)=n-1$

代码部分：

f1(x)=1，presumff1(x)=x-1

因为只有一个单项式，所以f2(x)和presumff2(x)和func(x1,x2)不需要

因为只计算质数的贡献，所以S(n,j)和pk(x)不需要

---
[n以内素数和](https://vjudge.net/problem/LibreOJ-6202)

因为 $f(p)=p$，所以 $f'(i)=i$，$\sum\limits_{i=2}^n f'(i)=(1+n)*n/2-1$

代码部分：

f1(x)=x，presumff1(x)=x*(x+1)/2-1

因为只有一个单项式，所以f2(x)和presumff2(x)和func(x1,x2)不需要

因为只计算质数的贡献，所以S(n,j)和pk(x)不需要

---
[质数前缀统计](https://www.luogu.com.cn/problem/P5493)

>此题需要求自然数幂和，可以拿[这里](https://zhuanlan.zhihu.com/p/563147047)的板子

因为 $f(p)=p^k$，所以 $f'(i)=i^k$，$\sum\limits_{i=2}^n f'(i)$用板子求

代码部分：

$f1(x)=x^k$，presumff1(x)用板子求

因为只有一个单项式，所以f2(x)和presumff2(x)和func(x1,x2)不需要

因为只计算质数的贡献，所以S(n,j)和pk(x)不需要

---
[洛谷模板题](https://www.luogu.com.cn/problem/P5325)

$f_1(p)=p$，$f_2(p)=p^2$，所以 $f_1'(i)=i$，$f_2'(i)=i^2$，$\sum\limits_{i=2}^n f_1'(i)=n(n+1)/2-1$，$\sum\limits_{i=2}^n f_2'(i)=n(n+1)(2n+1)/6-1$

$f(p^k)=p^k(p^k-1)=p^{2k}-p^k$

代码部分：

$f1(x)=x$，$f2(x)=x^2$，$presumff1(x)=x(x+1)/2-1$，$presumff2(x)=x(x+1)(2x+1)/6-1$，$pk(x)=x(x-1)$，$func(x1,x2)=x2-x1$

---
[Counting Divisors (square) ](https://vjudge.net/problem/SPOJ-DIVCNT2)

$f(p)=3$，根据拆常数技巧，$f'(i)=1$，$\sum\limits_{i=2}^n f_1'(i)=n-1$

$f(p^k)=2k+1$

代码部分：

$f1(x)=1$，$presumff1(x)=x-1$

因为只有一个单项式，所以f2(x)和presumff2(x)和func(x1,x2)不需要

记得给 g1,sum1 乘3

$pk(p^k)=2k+1$

---
[Counting Divisors (cube)](https://vjudge.net/problem/SPOJ-DIVCNT3)

和上题类似

$f(p)=4$，$f(p^k)=3k+1$

---
[Counting Divisors (general)](https://vjudge.net/problem/SPOJ-DIVCNTK)

和上题类似

$f(p)=k$，$f(p^e)=ke+1$

---
[奇怪的数学题](https://vjudge.net/problem/51Nod-1847)

>略难，考察对第1部分的理解

根据直觉，$sgcd(i,j)=\frac{gcd(i,j)}{minp(gcd(i,j))}$

设 $f(x)=\begin{cases}0&x=1\\\frac x{minp(x)}&otherwise\end{cases}$

$\sum\limits_{i=1}^n\sum\limits_{j=1}^nf(gcd(i,j))^k$

接下来按照[套路](https://zhuanlan.zhihu.com/p/557832253)推式子，这里就跳过一部分

$\sum\limits_{d=2}^nf(d)^k\sum\limits_{i=1}^{\frac nd}\sum\limits_{j=1}^{\frac nd}[gcd(i,j)=1]$

$\sum\limits_{d=2}^nf(d)^k(-1+2\sum\limits_{i=1}^{\frac nd}\phi(i))$

$\sum\limits_{i=1}^{m}\phi(i)$ 可以杜教筛求，[板子](https://zhuanlan.zhihu.com/p/576131237)

形如 $\sum\limits_{i=1}^nf(i)g(\left\lfloor\dfrac ni\right\rfloor)$ 可以[数论分块](https://zhuanlan.zhihu.com/p/557857835)

剩下需要求 $S(m)=\sum\limits_{i=1}^mf(i)^k$

分成质数，合数分别考虑

$f(p)^k=1$，因此质数的贡献等于m以内的质数个数

>从这里开始考察对第1部分的理解

从 $g(n,j-1)\rightarrow g(n,j)$ 的转移过程中，少了 $p_j=minp(i)$ 的合数的贡献，即

$\sum\limits_{i=p_j^2}^n[p_j=minp(i)]f'(i)$

发现这里有需要的 $minp(i)$，拆一下

$\sum\limits_{i=p_j^2}^n[p_j=minp(i)](\frac i{p_j})^k$

$\frac 1{p_j}^k\sum\limits_{i=p_j^2}^n[p_j=minp(i)]i^k$

$i$ 分解成 $p_j$ 和另一个数的乘积，上式变成

$\frac 1{p_j}^k\sum\limits_{d=p_j}^{\lfloor\frac n{p_j}\rfloor}[p_j\le minp(d)](p_jd)^k$

$\sum\limits_{d=p_j}^{\lfloor\frac n{p_j}\rfloor}[p_j\le minp(d)]d^k$

此时 $d^k$ 是完全积性函数幂函数

取 $f'(i)=i^k$，按照第一部分去维护这个 $f'(i)$ 的 $g$

转移的式子是 $g(n,j)=\begin{cases}g(n,j-1)&p_j^2>n\\g(n,j-1)-f'(p_j)(g(\frac n{p_j},j-1)-\sum\limits_{i=1}^{j-1}f'(p_i))&otherwise\end{cases}$

求 $g(n,0)$ 需要自然数幂和，还是抄[板子](https://zhuanlan.zhihu.com/p/563147047)

而需要的合数的贡献是$\sum\limits_{d=p_j}^{\lfloor\frac n{p_j}\rfloor}[p_j\le minp(d)]d^k$，即 $g(\frac n{p_j},j-1)-\sum\limits_{i=1}^{j-1}f'(p_i)$ 这一部分

---
[2022四川省赛E](https://ac.nowcoder.com/acm/contest/42105/E)

$\sum\limits_{p_1p_2p_3\le n，p_1<p_2<p_3}(p_1+p_2+p_3)^3$

对求和号下面的条件转化为更具体的

$\sum\limits_{p_1}^{\lfloor\sqrt[3] n\rfloor}\sum\limits_{p_2>p_1}^{\lfloor\sqrt\frac n{p_1}\rfloor}\sum\limits_{p_3>p_2}^{\lfloor\frac n{p_1p_2}\rfloor}(p_1+p_2+p_3)^3$

发现前两个求和号的上限之积不大，估算一下就是2.2e3*1e5=2.2e8

而题目给了8s，所以考虑枚举 $p_1,p_2$，求满足条件的 $p_3$ 的贡献

拆一下贡献的式子

$(p_1+p_2+p_3)^3$

$=p_1^3+p_2^3+p_3^3+3p_1p_2^2+3p_1p_3^2+3p_1^2p_2+3p_1^2p_3+3p_2p_3^2+3p_2^2p_3+6p_1p_2p_3$

$=(p_1^3+p_2^3+3p_1p_2^2+3p_1^2p_2)+3(2p_1p_2+p_1^2+p_2^2)p_3+3(p_1+p_2)p_3^2+p_3^3$

$=(p_1+p_2)^3p_3^0+3(p_1+p_2)^2p_3+3(p_1+p_2)p_3^2+p_3^3$

产生贡献的 $p_3$ 范围是 $(p_2,\frac n{p_1p_2}]$

所以需要筛 $p_3^0,p_3,p_3^2,p_3^3$ 的前缀和，而这个事min25筛可以做到

---
[2022ICPC网络赛1F](https://pintia.cn/market/item/1571156622976593920)

设 $f(x)$ 为 $a_k=x$ 的方案数

手算小数据会发现 $f(p)=k$ ，$f(p^2)=k(k+1)/2$

然后发现这是同球不同盒有空箱的[球盒问题](https://zhuanlan.zhihu.com/p/557873619)

推出 $f(p^e)=\dbinom{e+k-1}{e}$

另外发现不同质因子相互不干扰，所以 $f(x)$ 是积性函数

用min25筛求其前缀和，$f_1'(x)=1，presumff1(x)=x-1$

---
[2022牛客多校6D](https://ac.nowcoder.com/acm/contest/33191/D)

$ans=\sum\limits_{i=1}^nf(i)$

对于 $f(i)$，可以先想想如何暴力判断，质因数分解，然后每次取两个相异的，指数最高的，质因子，如果能取光，那 $f(i)=1$，否则 $f(i)=0$

因为每次取两个，所以总指数和是偶数

有一个经典结论，一堆元素分成多组，每次从不同的两组各拿一个，那么能拿完的条件是，元素个数最多的一组，的元素个数，小于等于全部元素数/2

因此，$x=\prod\limits_{i=1}^kp_i^{e_i}$

$f(x)=[\left(\sum\limits_{i=1}^k e_i\right)\%2=0][2\max e_i\le \sum\limits_{i=1}^ke_i]$

根据拆条件技巧，$f'(x)=1$，也就是第一部分处理质数个数，然后第二部分多传两个参数，表示指数和，最大指数

然后递归子问题时，指数和，和当前枚举指数，取和；最大指数，和当前枚举指数，取max

---
[2022杭电多校7I](http://acm.hdu.edu.cn/showproblem.php?pid=7217)

数组 $a$ 长度 $n(n\le N)$，$a_n\le M$，$f(n,m)$ 为数组长度为 $n$，$a_n=m$ 的方案数

考虑暴力求解 $f(n,m)$，$m=\prod\limits_{i=1}^kp_i^{e_i}$，每种质因数可以放在 $n$ 个位置，转化为同球不同盒有空箱的[球盒问题](https://zhuanlan.zhihu.com/p/557873619)

$f(n,m)=\prod\limits_{i=1}^k\dbinom{e_i+n-1}{e_i}$

$ans=\sum\limits_{i=1}^N\sum\limits_{j=1}^Mf(i,j)$

当 $n$ 固定，$f(n,m)$ 是积性函数，$\sum\limits_{i=1}^mf(n,i)$ 是积性函数前缀和，可以用 min25求

当 $m$ 固定，$\dbinom{e_i+n-1}{e_i}$ 是关于 $n$ 的 $e_i$ 次多项式

设 $E=\sum\limits_{i=1}^ke_i$，$f(n,m)$ 是关于 $n$ 的 $E$ 次多项式，$E\le min(n-1,log_2m)$

$\sum\limits_{j=1}^Mf(n,j)$，也是关于 $n$ 的 $E$ 次多项式

所以可以min25求 $g(i)=\sum\limits_{j=1}^Mf(i,j)$，然后对 $g(i)$ 的前缀和，插值求出 $ans$

min25 求 $g(i)=\sum\limits_{j=1}^Mf(i,j)$，和2022ICPC网络赛1F是一模一样的
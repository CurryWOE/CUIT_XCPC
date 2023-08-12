#! https://zhuanlan.zhihu.com/p/648824880
# 群论入门与polya定理
Burnside引理不方便计算，这里仅介绍polya定理
# 群
设 $G$ 是一个集合，$*$ 是 $G$ 上的二元运算，如果 $(G,*)$ 满足下面 4 个条件,则称 $(G,*)$ 为一个群。

>一个元素参与运算是一元运算，比如按位非；加减乘除等等是二元运算  
>这里 $*$ 拿来当符号用，不是乘法符号

1. 封闭性：$\forall a,b∈G$ ,有 $a*b∈G$;

>在集合中的任意两个元素进行运算，结果还在集合内

2. 结合律：$\forall a,b,c∈G$，有 $(a*b)*c=a*(b*c)$;

>和加法结合律，乘法结合律类似

3. 单位元：存在 $e∈G$ ,使得 $\forall a∈G$,都有$a*e=e*a=a$;

4. 逆元：$\forall a∈G,\exists x∈G$,使得 $a*x=x*a=e$,这个时候记 $x$ 为 $a^{-1}$，称为 $a$ 的逆元

当群的集合的元素的个数有限，称为有限群，且其中元素的个数称为阶，记为 $|G|$
## 例子
$G=\{0,1,2,3,......,n-1\}$

定义 $a*b=(a+b)\pmod n$

>$\pmod n$，所以结果肯定还在集合内  
>加法结合律  
>单位元是 $0$，$a*0=0*a=a$  
>$0$ 的逆元是 $0$，其他数逆元是$n-a,a*(n-a)=(n-a)*a=0$

所以 $(G,*)$ 是一个群
# 置换
一个集合到它自己本身的双射称为置换，下面均用 $\pi_i$ 表示一种置换

下面例子上面一行是原集合，下面一行是映射
## 例子
$\{1,2,3\}$ 的所有置换是

$\pi_1=\begin{matrix}1&2&3\\1&2&3\end{matrix}$

$\pi_2=\begin{matrix}1&2&3\\1&3&2\end{matrix}$

$\pi_3=\begin{matrix}1&2&3\\2&1&3\end{matrix}$

$\pi_4=\begin{matrix}1&2&3\\2&3&1\end{matrix}$

$\pi_5=\begin{matrix}1&2&3\\3&1&2\end{matrix}$

$\pi_6=\begin{matrix}1&2&3\\3&2&1\end{matrix}$

## 轮换表达式
上面写法过于麻烦，通常用轮换表达式表示，$i$ 向 $f(i)$ 连边，置换就是多个环形成的图

$\pi=\begin{matrix}1&2&3&4&5&6\\2&4&5&1&3&6\end{matrix}$

可以表示为 $(124)(35)(6)$ ,轮换个数记为 $C(\pi)=3$，即环的个数
## 置换群
对自身的双射显然满足群对运算符的要求，因此 $(所有置换组成的集合,对自身的双射)$ 是一个群，称为置换群
# Polya 定理
设 $G=\{\pi_1,\pi_2,\pi_3,...,\pi_k\}$是 $X=\{a_1,a_2,a_3,...,a_n\}$ 上一个置换群，

用 $m$ 种颜色对 $X$ 中的元素进行染色，那么不同的染色方案数为：

$\frac{1}{|G|} * \sum\limits_{i=1}^{k} m^{C(\pi_i)}$

在xcpc中的置换主要是旋转(rotate)和翻转(reflection to the axis of symmetry)
## 旋转
设环有 $n$ 个元素，群阶等于 $n$ 。因为旋转n次等于旋转0次

当旋转 $i$ 个位置，轮换个数为 $gcd(n,i)$，且每个轮换的长度为 $L=n/gcd(n,i)$。可以手动模拟理解一下

应用polya定理：

$\frac 1n\sum\limits_{i=1}^n m^{gcd(n,i)}$

优化上述式子：

$\frac 1n\sum\limits_{d|n}m^d\sum\limits_{i=1}^n[gcd(i,n)=d]$

$\frac 1n\sum\limits_{d|n}m^d\sum\limits_{i=1}^{\frac nd}[gcd(i,\frac nd)=1]$

$\frac 1n\sum\limits_{d|n}m^d\phi(\frac nd)$

### 例题
黑白两种颜色对下面的 $2\times 2$ 方格进行染色,

如果允许方格可以绕中心点旋转, 问有多少种不同的着色方案数?

$\begin{matrix}1&2\\3&4\end{matrix}$

---
方格可以旋转 $0°,90°,180°,270°$ 。 $G$ 中所有的置换是

$\pi_1 = (1)(2)(3)(4)$

$\pi_2 = (1234)$

$\pi_3 = (14)(23)$

$\pi_4 = (1432)$

$C(\pi_1) = 4 , C(\pi_2) = 1  , C(\pi_3) = 2 , C(\pi_4) = 1$

带入 Polya 定理

$ans = \frac{1}{4}*(2^4+2^1+2^2+2^1) = 6$

## 翻转
- 当 $n$ 为奇数时，只有一种形式，以顶点 $i$ 与中心的连线为轴的翻转  
$\pi_i=\begin{matrix}...&i-1&i&i+1&...\\...&i+1&i&i-1&...\end{matrix}$  
群阶等于 $n$，因为总共就n个元素。每个置换的轮换个数都等于 $(n+1)/2$ ，对照上式理解一下
- 当 n 为偶数时，有两种形式：
    - 以顶点 $i$ 与中心的连线为轴的翻转  
$\pi_i=\begin{matrix}...&i-1&i&i+1&...\\...&i+1&i&i-1&...\end{matrix}$  
群阶等于 $\frac n2$，因为对称性。每个置换的轮换个数都等于 $\frac n2+1$，对照上式理解一下
    - 以顶点 $i$ 和 $i+1$ 的中点与中心的连线为轴翻转  
$\pi_i=\begin{matrix}...&i-1&i&i+1&i+2&...\\...&i+2&i+1&i&i-1&...\end{matrix}$  
群阶等于 $\frac n2$，因为对称性。每个置换的轮换个数都等于 $\frac n2$，对照上式理解一下

应用polya定理：

$\begin{cases}m^{\frac{n+1}2}&n\ is\ odd\\\frac{m+1}2m^{\frac n2}&n\ is\ even\end{cases}$

## 板子
当同时考虑旋转和翻转：

$\frac{\sum\limits_{d|n}m^d\phi(\frac nd)+\begin{cases}nm^{\frac{n+1}2}&n\ is\ odd\\\frac{n(m+1)}2m^{\frac n2}&n\ is\ even\end{cases}}{2n}$

```c++
typedef long long ll;
ll fast_power(ll base,ll exponent)
{
    ll result=1;
    while(exponent>0)
    {
        if(exponent&1)
            result=result*base;
        base=base*base;
        exponent>>=1;
    }
    return result;
}
ll polya(ll n,ll m)
{
    if(!n)
        return 0;
    ll sum=0;
    for(ll i=0;i<n;++i)
        sum+=fast_power(m,__gcd(n,i));
    if(n&1)
        sum+=n*fast_power(m,(n+1)/2);
    else
        sum+=n/2*(1ll+m)*fast_power(m,n/2);
    sum/=(2*n);
    return sum;
}
```
## 例题
poj 1286 考虑旋转和翻转

poj 2409 考虑旋转和翻转

poj 2154 考虑旋转
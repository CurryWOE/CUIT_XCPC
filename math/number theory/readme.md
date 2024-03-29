#! https://zhuanlan.zhihu.com/p/594282753
# 数论导读
数论主要研究整数的整除问题

一个专题的内容较多时会写成单篇，导读不涉及代码实现
# 整除性

整数$a$和$b$，$a$整除$b$指$b$是$a$的倍数，$a$是$b$的约数（因数、因子），记为$a\mid b$。

## 整除性质

1.  任意性，若$a\mid b$，则对于任意非零整数$m$，有$am\mid bm$

2.  传递性，若$a\mid b$，且$b\mid c$，则$a\mid c$

3.  可消性，若$a\mid bc$，且$a$和$c$互素(互素的概念下文会讲到)，则$a\mid b$

4.  组合性，若$c\mid a$，且$c\mid b$，则对于任意整数$m$、$n$，有$c\mid (ma+nb)$。

$\lfloor\frac ki\rfloor$ 只在 $k\%i==0$ 变换，可以利用这个性质和差分加快求和。

# 素数与合数

素数（又称质数）

大于等于$2$，并且除了$1$和它本身外，不能被其它任何自然数整除；

其它的数称为合数；

注意：$1$既非素数也非合数。

# 素数判定
如何判定一个数是否为素数？

1. 预处理素数再试除

如果$n$是合数，那么它必然有一个小于等于$\sqrt n$的素因子，

2. Miller-Rabin

判别大数素性，会抄板子即可

# 素数分布定理

当$x$很大时，小于$x$的素数的个数近似等于$x/ln(x)$

1e9范围内，相邻素数之差最多178

1e18范围内，相邻素数之差最多320

# 素数筛选法
查找出范围内所有素数，并标记范围内所有数是否素数  

包括埃氏筛和欧拉筛（又叫线性筛）

埃氏筛的思想是素数的倍数一定不是素数，所以每找到一个素数，就把它的倍数标记  
如果前面没标记当前数是合数，那么这个数就是素数  
埃氏筛的缺陷是会重复筛一些数，比如$20=2*10=5*4$

对埃氏筛稍微改一下就变成狄利克雷前后缀

线性筛在埃氏筛上更进一步，让每个合数只被它的最小质因子筛选一次，减少了重复  

可以用线性筛求一些积性函数

> 积性函数：数论函数中,若$p$,$q$互质，满足$f(pq)=f(p)*f(q)$,则 f 为积性函数
>
> > 数论函数(又称算术函数):在数论上，指定义域为正整数、陪域为复数的函数
> >
> > > 陪域：在映射$f：X→Y$ 中，X 称为定义域，Y 称为陪域。对于某个映射来说，它的值域一定为陪域的子集

如约数个数，约数和，欧拉，莫比乌斯都是积性函数  
若任意$p$,$q$，满足$f(pq)=f(p)*f(q)$，则 f 为完全积性函数  
如$1$函数，即$f(x)=1$

积性函数性质可知，$f(1)=1$  
# 因数分解
## 算术基本定理
每个整数$n$，都可以唯一分解成素数的乘积，即
$n=\prod\limits_{i=1}^sp_i^{k_i}$

这里$p_i$是各不相同的素数，$k_i$是指数
## 质因数分解
1. 试除

试除$[2, \sqrt n]$的素数，大于 $\sqrt n$ 的素因子最多一个

2. Pollard-Rho

分解大数因子，配合Miller-Rabin使用，会抄板子即可

## 求所有因数
dfs枚举每个质数的指数

## 因子个数

1. 公式法

$\prod\limits_{i=1}^s (1+k_i)$

2.  线性筛筛选

会抄板子即可

## 因子和

1. 公式法

$\prod\limits_{i=1}^s \frac{p_i^{k_i+1}-1}{p_i-1}$

2. 线性筛筛选  

会抄板子即可

## 最大质因子个数和最大因子个数
$n\le$|$10^1$|$10^2$|$10^3$|$10^4$|$10^5$|$10^6$|$10^7$|$10^8$|$10^9$|
---|---|---|---|---|---|---|---|---|---
$max\{w(n)\}$|2|3|4|5|6|7|8|8|9
$max\{d(n)\}$|4|12|32|64|128|240|448|768|1344

$n\le$|$10^{10}$|$10^{11}$|$10^{12}$|$10^{13}$|$10^{14}$|$10^{15}$|$10^{16}$|$10^{17}$|$10^{18}$|
---|---|---|---|---|---|---|---|---|---
$max\{w(n)\}$|10|10|11|12|12|13|13|14|15
$max\{d(n)\}$|2304|4032|6720|10752|17280|26880|41472|64512|103680
# 最大公约数和最小公倍数
两个数$a$和$b$的最大公约数(Greatest Common Divisor)是指

同时整除$a$和$b$的最大因数，记为$gcd(a, b)$

当$gcd(a, b) = 1$，我们称$a$和$b$互素(又称互质)

两个数$a$和$b$的最小公倍数(Leatest Common Multiple)是指

同时被$a$和$b$整除的最小倍数，记为$lcm(a, b)$

求解$gcd$一般采用欧几里得算法

而求$lcm$通过$lcm(a, b) = ab / gcd(a, b)$求解
## $gcd$性质
$gcd(a,b)=gcd(a-b,b)$

$gcd(a,b)=gcd(a,a-b)$

$gcd(a,b)=gcd(b,a\%b)$

为了求解，人为规定$gcd(a,0)=a$

# 欧拉函数

一个重要的函数，表示小于$n$且与$n$互素的正整数的个数

符号为$φ(n)$，希腊字母$phi$

性质 $1$：质数$p$，$φ(p^n)=(p-1)*p^{n-1}$

性质 $2$：$a\mid x$，$φ(ax)=a*φ(x)$

性质 $3$：$gcd(a,b)=1$，$φ(a)*φ(b)=φ(ab)$

拓展：小于等于$n$且与$n$互素的正整数的和

$\sum\limits_{i=1}^{n} i*[gcd(i,n)==1]=n*φ(n)/2$

特例：$n=1,result=1$

证明：

因为$gcd(i,n)=gcd(n-i,n)$

所以每个和 $n$ 互质的数都有一个互补的数，和 $n$ 互质的数总共有 $φ(n)$ 个，所以总和为 $n*φ(n)/2$

---

质因数分解，$x=\prod\limits_{i=1}^sp_i^{k_i}$

根据性质 $1$和性质 $3$，可得

$φ(x)=\prod\limits_{i=1}^s p_i^{k_i-1}*(p_i-1)$

$=x*\prod\limits_{i=1}^s (p_i-1)/p_i$
# 快速幂
严格来说不算数论，但之后知识会用到  
（数论是研究整数的整除问题，不是数学都算数论）  

二进制表示指数  
$5=101,3^5=3^{2^0+2^2}=3^{2^0} * 3^{2^2}$  
通过上式可以发现，只有指数二进制当前位为 1，才对答案有贡献  
# 模运算
给定一个正整数$p$，任意一个整数$n$，一定存在等式$n = kp + r$；  
其中$k$、$r$是整数，且满足$0 \le r < p$，  
称$k$为$n$除以$p$的商， $r$为$n$除以$p$的余数，记为$n \% p = r$ ($\%$表示取模运算)  
对于正整数和整数$a$, $b$, 定义如下运算：  
取模运算：$a \% p$，表示$a$除以$p$的余数。  
模$p$加法：$(a + b) \% p = (a\%p + b\%p) \% p$  
模$p$减法：$(a - b) \% p = (a\%p - b\%p) \% p$  
模$p$乘法：$(a * b) \% p = ((a \% p) * (b \% p)) \% p$  
模$p$除法：$(a / b) \% p = ((a \% p) * (inv(b) \% p)) \% p$  
$inv()$表示逆元，之后学习  
幂模$p$ ：$(a ^ b) \% p = ((a \% p) ^ b) \% p$  
幂模可以用快速幂加速  
模运算满足结合律、交换律和分配律。  

>特别地，当n是mod的倍数，n*inv(n)，如果处处取模会被算成0，但实际上式子结果是1，所以要么全程int128，要么找其他方法解决，总之不能直接取模

>(mod-x)+x=mod，当mod是奇数，x和-x在模意义下一定一奇一偶。当 $|x|\%mod=x\%mod$ ，x是正数，否则是负数
## 快速取模(Barrett 模乘)
取模比加减慢很多，如需卡常，使用此算法
```cpp
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b;
        return r >= b ? r - b : r;
    }
};
```
## 同余
$a\equiv b \pmod n$ 表示$a$和$b$模$n$同余，即$a$和$b$除以$n$的余数相等。  
$\equiv$ 是恒等于符号，表示绝对成立，无论变量取什么值  
（$=$是条件成立，要求变量满足条件才成立）  
在模运算方程中，通常使用$\equiv$，约定俗成的习惯

# 欧拉定理&费马小定理
在模意义下，降低幂的指数。亦可用于求逆元
# 逆元
用于模运算的除法运算
# 裴蜀定理
判断二元一次方程有没有解，多元一次方程可以转化为二元一次方程组
# 线性同余方程
形如 $ax\equiv b \pmod n$，其中$a$、$b$、$n$都为常量，x 是未知数，

这个方程可以转为二元一次方程
# 二元一次方程
拓展欧几里得求解

# 线性同余方程组
和线性方程组相似，不过是模意义

CRT与ExCRT求解
# 原根
转乘法为加法
# 离散对数
BSGS和ExBSGS求解



> 下面三个大知识点一起用的，请全部学习后再开始写题

# 狄利克雷卷积&莫比乌斯反演
把一大坨求和号变成能快速求的式子
# 数论分块
快速计算一些含有除法取整的式子，形如

$\sum\limits_{i=1}^nf(i)g(\left\lfloor\dfrac ni\right\rfloor)$ 或 $\sum\limits_{i=1}^nf(i)g(\left\lceil\dfrac ni\right\rceil)$
# 卷积&莫反例题

> 一个常识：$d\mid i,d\mid j⇔d\mid gcd(i,j)$

# 杜教筛
求部分数论函数前缀和
# min25筛
求部分积性函数前缀和
# 类欧几里得
类欧用于求形如下式的问题：$f(a,b,c,n)=\sum\limits_{i=0}^n\lfloor \frac{ai+b}{c}\rfloor$
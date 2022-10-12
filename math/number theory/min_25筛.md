# min_25筛
求积性函数 $f(n)$ 前缀和 $S(n)=\sum\limits_{i=1}^nf(i)$

>p表示质数

限制：$f(p^k)=g(p,k)$

$g(p,1)$ 是一个最高次数低的多项式，即 $g(p,1)=\sum\limits_{j=0}^{\infty}coe_jp^j$

$g(p,k)$ 可以 $O(1)$ 算出来

计算不同的正整数 $x=\lfloor\frac nk\rfloor$，的 $S(x)$

>$x$ 最多 $2\sqrt n$ 个

## 证明
$k\le\sqrt n$，因为 $k$ 最多 $\sqrt n$个，所以 $x$ 最多有 $\sqrt n$ 个

$k\ge\sqrt n$，因为 $x\le\sqrt n$，所以 $x$ 最多 $\sqrt n$个 

---
迭代 $g(p,k)$ 的 $k$，用 $\sum\limits_{}
# 证明
设 $S(n)=\sum\limits_{i=1}^nf(i)$

拆分成质数的贡献，和数的贡献

$S(n)=\sum\limits_{i=1}^n[i\in P]f(i)+\sum\limits_{i=1}^n[i\notin P]f(i)$

此时先对后半部分求和

此时再对前半部分求和，设 $g(n)=\sum\limits_{i=1}^{P_i\le n}f(P_i)$

把 $f(p)$ 代换成多项式

$g(n)=\sum\limits_{i=1}^{P_i\le n}\sum\limits_{j=0}^{\infty}coefficient_j*P_i^j$

把系数提到前面

$=\sum\limits_{j=0}^{\infty}coefficient_j\sum\limits_{i=1}^{P_i\le n}P_i^j$

设 $h(n,j)=\sum\limits_{i=1}^{P_i\le n}P_i^j$
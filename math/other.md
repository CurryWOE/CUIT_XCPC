#! https://zhuanlan.zhihu.com/p/563147047

# 数论杂

# 线性回归

一堆点 $(x_i,y_i)$ ，求一条直线 $F(x):y=Ax+B$ ，使得 $\sum\limits_{i=1}^n (y_i-F(x_i))^2$ 最小

设 $\overline{x}=\frac{\sum\limits_{i=1}^n x_i}n$ ， $\overline{y}=\frac{\sum\limits_{i=1}^n y_i}n$

$A=\frac{\sum\limits_{i=1}^n x_iy_i-n\overline{x} \overline{y}}{\sum\limits_{i=1}^n x_i^2-n\overline{x}^2}$

$B=\overline{y}-A\overline{x}$

# 自然数前 n 项 p 次方求和

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

# 调和级数近似公式

n 很大时

$f_n\approx \ln n+0.5772156649+\frac 1{2n}$

```cpp
log(n)+0.5772156649+1.0/(2*n)
```

# 广义斐波那契数列求循环节

$f_n=af_{n-1}+bf_{n-2}$

## $f_n\pmod p$的最小循环节长度

1. 分解$p$为素因子幂的形式，即$p=\prod p_i^{a_i}$
2. 计算数列模$p_i^{a_i}$的循环节长度，设长度为$x_i$

$x_i=G(p_i)*p^{a_i-1}$

$G(p)$ 表示模$p$的最小循环节长度

求$G(p)$,设$c=a^2+4b$

$p=2$要特判（具体怎么判待研究）

## 欧拉准则

若 p 是奇质数且$p\nmid d$，

d 是模 p 的二次剩余当且仅当：

$d^{(p-1)/2}=1 \pmod p$

否则，d 是模 p 的二次非剩余

---

若$c$是$p$的二次剩余,枚举$p-1$的因子

若$c$是$p$的二次非剩余,枚举$(p-1)(p+1)$的因子

找到$G(p)$满足

$\begin{bmatrix}a&b\\1&0\end{bmatrix}^{G(p)} =\begin{bmatrix}1&0\\0&1\end{bmatrix} \pmod {p}$

3. 循环节长度$L=lcm(x_i)$

## 求较小循环节

注意到 $G(p)$一定是$(p-1)(p+1)$的因子

所以$x_i$一定是$(p_i-1)(p_i+1)*p_i^{a_i-1}$的因子

循环节长度$L=\prod (p_i-1)(p_i+1)*p_i^{a_i-1} \pmod p$

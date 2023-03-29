# 多项式入门（1）
对于[原文](https://cp-algorithms.com/algebra/polynomial.html)的翻译和个人理解的笔记，略有删减

# 基础概念和事实
$A(x)=a_0+a_1x+...+a_nx^n$ 是一元多项式

为了简化描述，用 $A$ 表示 $A(x)$，保证 $a_n\ne 0$ 并且 $ A(x)\ne 0$

$A$ 的度 $deg$ $A=n$，特别地，$A=0$ 时，$deg$ $A=-\infty$

在这个概念里，$deg$ $AB=deg$ $A+deg$ $B$，对任意多项式 $A$ 和 $B$ 成立

## 多项式性质
多项式有很多和整数相似的性质

1. 对于任意多项式 $A$ 和 $B\ne 0$，可以唯一表达 $A$，即  
$A=DB+R,deg$ $R< deg$ $B$  
$R$ 是余数，$D$ 是商
2. 如果 $A$ 和 $B$ 求余 $C$ 有相同余数，则称同余，即 $A\equiv B\mod C$
3. 当且仅当 $A\equiv 0 \mod B$，$A$ 是 $B$ 的倍数
4. 当且仅当 $A-B$ 是 $C$ 的倍数，$A\equiv B \mod C$
5. 特别地，$A\equiv B \mod {CD}$ 表明 $A\equiv B \mod C$
6. 对于任意度数为1的多项式 $x-r$，$A(x)=A(r) \mod {x-r}$
7. 当且仅当 $A(r)=0$，$A$ 是 $x-r$ 的倍数
8. 对于模数是 $x^k$，有 $A\equiv a_0+a_1x+...+a_{k-1}x^{k-1} \mod {x^k}$

# 基础工具
[板子](https://github.com/e-maxx-eng/e-maxx-eng-aux/blob/master/src/polynomial.cpp)

# 算术
## 乘法
其他算术的基础

$A=a_0+a_1x+...+a_nx^n$

$B=b_0+b_1x+...+a_mx^m$

计算 $C=AB$，定义为

$C=\sum\limits_{i=0}^n\sum\limits_{j=0}^ma_ib_jx^{i+j}=c_0+c_1x+...+c_{n+m}x^{n+m}$

可以用 FFT $O(nlogn)$ 计算
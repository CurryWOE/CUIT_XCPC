>常识：线性代数的”线性“表示未知数的次数都是一次
# 矩阵快速幂
给出底矩阵和指数，快速求出幂矩阵

也就是把对整数的操作移植到矩阵上来

一般会复合一些dp
## 时间复杂度
$O(t^3*log n)$,$t$ 是矩阵边长，$t^3$ 表示矩阵乘法

## 应用

给出多项式定义，满足递推关系，可以用矩阵快速幂快速求出第n项

1. 从题目抽象出底矩阵和指数

2. 抽象出第一项矩阵

3. 用矩阵快速幂求幂

4. 幂和第一项矩阵相乘得目标矩阵

5. 输出答案

## 常见多项式抽象

1. $f(n) = a * f(n-1) + b * f(n-2) +c$

$\begin{pmatrix}a&b&1\\1&0&0\\0&0&1\end{pmatrix}*
\begin{pmatrix}f(n-1)\\f(n-2)\\c\end{pmatrix}=
\begin{pmatrix}f(n)\\f(n-1)\\c\end{pmatrix}$

2. $f(n) = f(n-1) + c^n$

$\begin{pmatrix}1&c\\0&c\end{pmatrix}*
\begin{pmatrix}f(n-1)\\c^{n-1}\end{pmatrix}=
\begin{pmatrix}f(n)\\c^{n}\end{pmatrix}$

3. $f(n)= f(n-1) + n^3$

因为

$n^3$

$= (n - 1 + 1)^3$

$= C(0,3)*(n-1)^3 + C(1,3)*(n-1)^2 + C(2,3)*(n-1)^1 + C(3,3)*(n-1)^0$

所以

$\begin{pmatrix}1&C(0,3)&C(1,3)&C(2,3)&C(3,3)\\
0&C(0,3)&C(1,3)&C(2,3)&C(3,3)\\
0&0&C(0,2)&C(1,2)&C(2,2)\\
0&0&0&C(0,1)&C(1,1)\\
0&0&0&0&C(0,0)\end{pmatrix}*
\begin{pmatrix}f(n-1)\\(n-1)^3\\(n-1)^2\\(n-1)^1\\(n-1)^0\end{pmatrix}=
\begin{pmatrix}f(n)\\n^3\\n^2\\n^1\\n^0\end{pmatrix}$

请学习 $\color{powderblue}矩阵快速幂.md$   
# 高斯消元
可以求解线性方程组，求矩阵的秩，求矩阵的逆

这里介绍求解线性方程组，用的是高斯约旦消元法，比普通高斯消元法精度更高，代码更简洁
## 时间复杂度
$O(n^3)$
## 线性方程组
形式如下
$$\begin{cases}a_{11}x_1+a_{12}x_2+...+a_{1n}x_n=b_1\\ a_{21}x_1+a_{22}x_2+...+a_{2n}x_n=b_2\\...\\a_{n1}x_1+a_{n2}x_2+...+a_{nn}x_n=b_n\end{cases}$$
写成矩阵形式，AX=B
$$A=\begin{vmatrix}a_{11}&a_{12}&...&a_{1n}\\a_{21}&a_{22}&...&a_{2n}\\...\\a_{n1}&a_{n2}&...&a_{nn}\end{vmatrix},X=\begin{vmatrix}x_1\\x_2\\...\\x_n\end{vmatrix},B=\begin{vmatrix}b_1\\b_2\\...\\b_n\end{vmatrix}$$
笔算如何求解在”线性代数“这门课里已经讲过了，不再叙述

程序求解就是把AB化成下式
$$\begin{vmatrix}1&0&...&0&c_1\\0&1&...&0&c_2\\...\\0&0&...&1&c_n\end{vmatrix}$$
这样 $X$ 就等于
$$\begin{vmatrix}c_1\\c_2\\...\\c_n\end{vmatrix}$$
## 算法流程
1. 选择一个尚未被选过的未知数作为主元，选择一个包含这个主元的方程。
2. 将这个方程主元的系数化为1。
3. 通过加减消元，消掉其它方程中的这个未知数。
4. 重复以上步骤，直到把每一行都变成只有一项有系数。

请学习 $\color{powderblue}高斯消元.md$ 
# 行列式
# 线性基
# 矩阵求逆
# 常系数线性递推
# 矩阵树定理
# BM
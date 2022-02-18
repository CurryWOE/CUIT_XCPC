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
# 行列式
# 线性基
# 矩阵求逆
# 常系数线性递推
# 矩阵树定理
# BM
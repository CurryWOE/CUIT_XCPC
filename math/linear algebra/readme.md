#! https://zhuanlan.zhihu.com/p/557871981
# 线性代数导读
>常识：线性代数的”线性“表示未知数的次数都是一次
# 矩阵快速幂
给出底矩阵和指数，快速求出幂矩阵

也就是把对整数的操作移植到矩阵上来

一般会复合一些dp
## 时间复杂度
$O(t^3*log n)$,$t$ 是矩阵边长，$t^3$ 表示矩阵乘法

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
# 高斯消元
求解线性方程组和异或方程组，求矩阵的逆

用的是高斯约旦消元法，比普通高斯消元法精度更高，代码更简洁
## 时间复杂度
$O(n^3)$

稀疏矩阵可以观察稀疏的地方并优化
## 线性方程组
形式如下
$$\begin{cases}a_{11}x_1+a_{12}x_2+...+a_{1n}x_n=b_1\\ a_{21}x_1+a_{22}x_2+...+a_{2n}x_n=b_2\\...\\a_{n1}x_1+a_{n2}x_2+...+a_{nn}x_n=b_n\end{cases}$$
写成矩阵形式，AX=B
$$A=\begin{vmatrix}a_{11}&a_{12}&...&a_{1n}\\a_{21}&a_{22}&...&a_{2n}\\...\\a_{n1}&a_{n2}&...&a_{nn}\end{vmatrix},X=\begin{vmatrix}x_1\\x_2\\...\\x_n\end{vmatrix},B=\begin{vmatrix}b_1\\b_2\\...\\b_n\end{vmatrix}$$
笔算如何求解在”线性代数“这门课里已经讲过了，不再叙述

程序求解就是增广矩阵行初等行变换为行最简形：
$$\begin{vmatrix}a_{11}&a_{12}&...&a_{1n}&b_1\\a_{21}&a_{22}&...&a_{2n}&b_2\\...\\a_{n1}&a_{n2}&...&a_{nn}&b_n\end{vmatrix}\rightarrow\begin{vmatrix}1&0&...&0&c_1\\0&1&...&0&c_2\\...\\0&0&...&1&c_n\end{vmatrix}$$
这样 $X$ 就等于
$$\begin{vmatrix}c_1\\c_2\\...\\c_n\end{vmatrix}$$
## 矩阵求逆
逆矩阵在“线性代数”已讲过，不再叙述

对 $n$ 阶矩阵 $A$，构造 $n\times 2n$ 的矩阵 $(A,I_n)$

高斯消元化成 $(I_n,A^{-1})$

如果左半部分不能化成单位矩阵，则矩阵 $A$ 不可逆
## 异或方程组
异或运算满足交换律和结合律，所以可以使用类似高斯消元的方法解决方程组

形式如下,且所有系数（即a和b）均为0或1
$$\begin{cases}a_{11}x_1\oplus a_{12}x_2\oplus ...\oplus a_{1n}x_n=b_1\\ a_{21}x_1\oplus a_{22}x_2\oplus ...\oplus a_{2n}x_n=b_2\\...\\a_{n1}x_1\oplus a_{n2}x_2\oplus ...\oplus a_{nn}x_n=b_n\end{cases}$$
应使用“异或消元”而非“加减消元”，且不需要进行乘除改变系数（因为系数均为0和1）。

注意到异或方程组的增广矩阵是01矩阵，可以用bitset优化
# 行列式
矩阵应用高斯消元，得到一个对角线矩阵，此矩阵的行列式由对角线元素之积所决定。其符号可由交换行的数量来确定（如果为奇数，则行列式的符号应颠倒）
# 线性基
求向量空间的基向量，解决异或相关的问题
# 常系数线性递推
# 矩阵树定理
# BM
# 杂
向量各分量元素值为 $[0,p-1]$ 的整数，一个已经确定的，秩为 $j$ 的 $n$ 维向量组，能线性组合成的两两不同的向量，有 $p^j$ 个
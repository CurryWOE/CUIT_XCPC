#! https://zhuanlan.zhihu.com/p/557875113

# 组合数学导读

# 排列组合

排列就是指从给定个数的元素中取出指定个数的元素进行排序

组合则是指从给定个数的元素中仅仅取出指定个数的元素，不考虑排序

排列组合的中心问题是研究给定要求的排列和组合可能出现的情况总数。

# 加法原理&乘法原理

## 加法原理

做一件事情，完成它有$n$类办法，$a_i$ 表示第$i$类方法的数目，那么完成这件事共有$\sum\limits_{i=1}^n a_i$ 种不同的方法

## 乘法原理

做一件事情，完成它有$n$个步骤，$a_i$ 表示第$i$个步骤的方法数目，那么完成这件共事有$\prod\limits_{i=1}^n a_i$种不同的方法。

# 排列数&组合数

## 排列数

$n$ 个数选 $m$ 个排列，情况总数=$A_n^m=\frac{n!}{(n-m)!}$

全排列，指 $n$ 个数选 $n$ 个排列，情况总数=$A_n^n=n!$

## 组合数

$n$ 个数选 $m$ 个组合，情况总数=$C_n^m=\frac{n!}{m!(n-m)!}$

组合数也常用$\displaystyle\binom{n}{m}$表示

组合数也被称为“二项式系数”

# 二项式定理

$$(a+b)^n=\sum\limits_{i=0}^n \displaystyle\binom{n}{i} a^ib^{n-i}$$

# 多重集

## 多重集

包含重复元素的广义集合。

设 $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$

表示由 $n_1$ 个 $a_1$，$n_2$ 个 $a_2$，…，$n_k$ 个 $a_k$ 组成的多重集

## 多重集的排列数

从 $S$ 中选择 $r$ 个元素排列

$$\frac{n!}{\prod_{i=1}^k(n_i!)}$$

相当于把相同元素的排列数除掉了

## 多重集的组合数

从 $S$ 中选择 $r$ 个元素组合

这个问题等价于 $x_1+x_2+\cdots+x_k=r$ 的非负整数解的数目，可以用插板法解决，答案为

$$\binom{r+k-1}{k-1}$$

# 不相邻的排列

$1 \sim n$ 这 $n$ 个自然数中选 $k$ 个，这 $k$ 个数中任何两个数都不相邻的组合有 $\displaystyle \binom {n-k+1}{k}$ 种。

# 圆排列

$n$ 个人全部来围成一圈，所有的排列数记为 $\mathrm Q_n^n$。考虑其中已经排好的一圈，从不同位置断开，又变成不同的队列。
所以有

$$\mathrm Q_n^n \times n = \mathrm A_n^n \Longrightarrow \mathrm Q_n = \frac{\mathrm A_n^n}{n} = (n-1)!$$

由此可知部分圆排列的公式：

$$\mathrm Q_n^r = \frac{\mathrm A_n^r}{r} = \frac{n!}{r \times (n-r)!}$$

# 组合数性质

$$\binom{n}{m}=\binom{n}{n-m}\tag{1}$$

相当于将选出的集合对全集取补集，故数值不变。（对称性）

$$\binom{n}{k} = \frac{n}{k} \binom{n-1}{k-1}\tag{2}$$

由定义导出的递推式。

$$\binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}\tag{3}$$

组合数的递推式（杨辉三角的公式表达）

$$\binom{n}{0}+\binom{n}{1}+\cdots+\binom{n}{n}=\sum_{i=0}^n\binom{n}{i}=2^n\tag{4}$$

这是二项式定理的特殊情况。取 $a=b=1$ 就得到上式。

$$\sum_{i=0}^m \binom{n}{i}\binom{m}{m-i} = \binom{m+n}{m}\ \ \ (n \geq m)\tag{5}$$

拆组合数的式子，在处理某些数据结构题时会用到。

$$\sum_{i=0}^n\binom{n}{i}^2=\binom{2n}{n}\tag{6}$$

这是 $(5)$ 的特殊情况，取 $n=m$ 即可。

$$\sum_{i=0}^ni\binom{n}{i}=n2^{n-1}\tag{7}$$

带权和的一个式子，通过对 $(3)$ 对应的多项式函数求导可以得证。

$$\sum_{i=0}^ni^2\binom{n}{i}=n(n+1)2^{n-2}\tag{8}$$

与上式类似，可以通过对多项式函数求导证明。

$$\sum_{l=0}^n\binom{l}{k} = \binom{n+1}{k+1}\tag{9}$$

在恒等式证明中较常用。

$$\binom{n}{r}\binom{r}{k} = \binom{n}{k}\binom{n-k}{r-k}\tag{10}$$

通过定义可以证明。

$$\sum_{i=0}^n\binom{n-i}{i}=F_{n+1}\tag{11}$$

其中 $F$ 是斐波那契数列。

# 容斥原理

求集合的并

设 U 中元素有 n 种不同的属性，而第 i 种属性称为 $P_i$，拥有属性 $P_i$ 的元素构成集合 $S_i$，那么

$$\left|\bigcup_{i=1}^{n}S_i\right|=\sum_{m=1}^n(-1)^{m-1}\sum_{a_i<a_{i+1} }\left|\bigcap_{i=1}^mS_{a_i}\right|$$

例如
$$|A\cup B\cup C|=|A|+|B|+|C|-|A\cap B|-|B\cap C|-|C\cap A|+|A\cap B\cap C|$$

## min-max 容斥
详见概率论
## 二项式反演
详见二项式反演
# 常见数列

## 斐波那契数列

$f(n)=\begin{cases}0&n=0\\1&n=1\\f(n-1)+f(n-2)&n\ge 2\end{cases}$

$gcd(F_n,F_m)=F_{gcd(n,m)}$

$\sum\limits_{i=0}^n F_i=F_{n+2}-1$

模m意义下，循环节长度小于等于6m
## 错排问题

我们把错位排列问题具体化，考虑这样一个问题：

$n$ 封不同的信，编号分别是 $1,2,3,4,5$，现在要把这五封信放在编号 $1,2,3,4,5$ 的信封中，要求信封的编号与信的编号不一样。问有多少种不同的放置方法？

假设我们考虑到第 $n$ 个信封，初始时我们暂时把第 $n$ 封信放在第 $n$ 个信封中，然后考虑两种情况的递推：

- 前面 $n-1$ 个信封全部错位；
- 前面 $n-1$ 个信封有一个没有错位其余全部错位。

对于第一种情况，前面 $n-1$ 个信封全部错位：因为前面 $n-1$ 个已经全部错位了，所以第 $n$ 封只需要与前面任一一个位置交换即可，总共有 $f(n-1)\times (n-1)$ 种情况。

对于第二种情况，前面 $n-1$ 个信封有一个没有错位其余全部错位：考虑这种情况的目的在于，若 $n-1$ 个信封中如果有一个没错位，那么我们把那个没错位的与 $n$ 交换，即可得到一个全错位排列情况。没错位的可以有 $n-1$ 个位置

其他情况，我们不可能通过一次操作来把它变成一个长度为 $n$ 的错排。

于是可得错位排列的递推式为 $f_n=(n-1)(f_{n-1}+f_{n-2})$。

错位排列数列的前几项为 $0,1,2,9$。

## 卡特兰数

### 经典题：进出栈序列

n 个元素进栈序列为：1，2，3，4，...，n，则有多少种出栈序列

我们将进栈表示为 +1，出栈表示为 -1

出栈序列的所有前缀和必然大于等于 0，并且序列 +1 的数量 等于 -1 的数量

接下来让我们观察一下 n = 3 的一种出栈序列：+1 -1 -1 +1 -1 +1。序列前三项和小于 0，显然这是个非法的序列。

如果将 第一个 前缀和小于 0 的前缀，即前三项元素都进行取反，就会得到：-1 +1 +1 +1 -1 +1。此时有 3 + 1 个 +1 以及 3 - 1 个 -1。

因为这个小于 0 的前缀和必然是 -1，且 -1 比 +1 多一个，取反后，-1 比 +1 少一个，则 +1 变为 n + 1 个，且 -1 变为 n - 1 个。进一步推广，对于 n 元素的每种非法出栈序列，都会对应一个含有 n + 1 个 +1 以及 n - 1 个 -1 的序列。

如何证明这两种序列是一一对应的？

假设非法序列为 A，对应的序列为 B。每个 A 只有一个"第一个前缀和小于 0 的前缀"，所以每个 A 只能产生一个 B。而每个 B 想要还原到 A，就需要找到"第一个前缀和大于 0 的前缀"，显然 B 也只能产生一个 A。

每个 B 都有 n + 1 个 +1 以及 n - 1 个 -1，因此 B 的数量为 $\dbinom {2n}{n+1}$ ，相当于在长度为 2n 的序列中找到 n + 1 个位置存放 +1。相应的，非法序列的数量也就等于 $\dbinom {2n}{n+1}$ 。

出栈序列的总数量共有 $\dbinom {2n}{n}$ ，因此，合法的出栈序列的数量为 $\dbinom {2n}{n}-\dbinom {2n}{n+1}$ 。

此时我们就得到了卡特兰数的通项 $\dbinom {2n}{n}-\dbinom {2n}{n+1}=\dbinom{2n}{n}/(n+1)$

### 例题

n 对括号，则有多少种 “括号匹配” 的括号序列

左括号+1，有括号-1

n + 1 个叶子节点能够构成多少种形状不同的满二叉树

> 如果一棵二叉树的结点要么是叶子结点，要么它有两个子结点，这样的树就是满二叉树。

非叶节点，左子树+1，右子树-1

电影票一张 50 coin，且售票厅没有 coin。m 个人各自持有 50 coin，n 个人各自持有 100 coin。则有多少种排队方式，可以让每个人都买到电影票。

50+1，100-1

公式不同，$\dbinom {n+m}n-\dbinom{n+m}{m+1}$

节点数为 $i$ 时二叉树构造的方案数

> 写题就是寻找满足下列公式的特点

### 公式

$C_n=\dbinom{2n}{n}/(n+1)$

$C_1=1,C_n=C_{n-1}\times\frac{4n-2}{n+1}$

$C_n=\begin{cases}1&n=0,1\\\sum\limits_{i=1}^n C_{i-1}*C_{n-i}&2\le n\end{cases}$

$C_n=\dbinom {2n}{n}-\dbinom {2n}{n+1}$
# FFT
对于[原文](https://cp-algorithms.com/algebra/fft.html#discrete-fourier-transform)的翻译和个人理解的笔记，略有删减
## DFT
定义一个度数 $n-1$ 的多项式

$A(x)=a_0+a_1x+...+a_{n-1}x^{n-1}$

>为了方便，假设 $n$ 是2的幂，如果 $n$ 不是2的幂，添加缺失的项 $a_ix^i$，同时设 $a_i=0$

从复数论得知，$x^n=1$ 有 $n$ 个根，根的形式：$w_{n,k}=e^{\frac{2k\pi i}n}$，$k\in[0,n-1]$

>为了方便，以下 $w_n$ 表示 $w_{n,1}$

$w_n$ 可以表示其他根，即 $w_{n,k}=w_n^k$

DFT被定义为 系数表达法 向 点值表达法 的转换
### 系数表达法
$A(x)=a_0+a_1x+...+a_{n-1}x^{n-1}$

一个vector，$(a_0,a_1,...,a_{n-1})$可以表示这个多项式
### 点值表达法
$n$ 个点可以唯一确定一个 $n-1$ 次多项式

一个vector，$(A(x_0),A(x_1),...,A(x_{n-1}))$可以表示这个多项式

DFT定义如下

$DFT(a_0,a_1,...,a_{n-1})=(y_0,y_1,...,y_{n-1})$

$=(A(w_n^0),A(w_n^1),...,A(w_n^{n-1}))$

类似的，IDFT定义如下，即DFT的逆运算

$IDFT(y_0,y_1,...,y_{n-1})=(a_0,a_1,...,a_{n-1})$
## DFT应用：快速多项式乘法
对于系数表达法，两个多项式相乘需要 $O(n^2)$

但对于点值表达法，两个多项式相乘需要 $O(n)$，即相同位置的点，点值乘起来

因此有如下式子：

$AB=IDFT(DFT(A)DFT(B))$

>两个多项式应该有相同度，否则两个DFT的结果vector有不同长度，可以添加系数为0的项

>由于结果是度为 $2(n-1)$ 的多项式，对于两个多项式应该加倍度数，同样添加系数为0的项
## FFT
$O(nlogn)$ 计算DFT，基本思想是分治，把系数vector分成两个，递归计算这两个的DFT，组合结果去计算整个多项式的DFT

定义多项式 $A(x)$，$deg$ $A=n-1$，$n>1$，$n$ 是2的幂

$A(x)=a_0+a_1x+...+a_{n-1}x^{n-1}$

根据位置奇偶性分成两半

$A_0(x)=a_0+a_2x+...+a_{n-2}x^{\frac n2-1}$

$A_1(x)=a_1+a_3x+...+a_{n-1}x^{\frac n2-1}$

显然，

$A(x)=A_0(x^2)+xA_1(x^2)$

因此合并是 $O(n)$

$T_{DFT}(n)=2T_{DFT}(\frac n2)+O(n)=O(nlogn)$

假设已计算出 $DFT(A_0),DFT(A_1)$，考虑合并的表达式

>$y_k^0$ 表示 $DFT(A_0)$ 第k项，$y_k^1$ 表示 $DFT(A_1)$ 第k项，$y_k$ 表示 $DFT(A)$ 第k项 

对于 $k\in[0,n/2-1]$

$y_k=A(w_n^k)=A_0((w_n^k)^2)+w_n^kA_1((w_n^k)^2)$

因为 $(w_n^k)^2=w_{n/2}^k$

$=A_0(w_{n/2}^k)+w_n^kA_1(w_{n/2}^k)$

$=y_k^0+w_n^ky_k^1$

对于 $k\in[n/2,n-1]$

$y_{k+n/2}=A(w_n^{k+n/2})=A_0(w_n^{2k+n})+w_n^{k+n/2}A_1(w_n^{2k+n})$

$=A_0(w_n^{2k})-w_n^{k}A_1(w_n^{2k})$

$=y_k^0-w_n^ky_k^1$

整理一下

$y_k=y_k^0+w_n^ky_k^1$

$y_{k+n/2}=y_k^0-w_n^ky_k^1$
## IFFT
$w_n^k$ 组成的矩阵乘上系数矩阵等于点值矩阵

点值矩阵乘上逆矩阵即可算出系数矩阵，即

$a_k=\frac 1n\sum\limits_{j=0}^{n-1}y_jw_n^{-kj}$

和点值矩阵的计算的形式很像

$y_k=\frac 1n\sum\limits_{j=0}^{n-1}a_jw_n^{kj}$

因此，传递一个参数表示FFT/IFFT
## 实现
>这边直接给出优化版本（二进制反转）
```cpp
using cd = complex<double>;
const double PI = acos(-1);
void fft(vector<cd> & a, bool invert)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
    {
        for (cd & x : a)
            x /= n;
    }
}
```
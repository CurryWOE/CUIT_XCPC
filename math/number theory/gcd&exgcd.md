#! https://zhuanlan.zhihu.com/p/662653668
# gcd&EXgcd
# gcd
欧几里得算法,又名辗转相除法
## 辗转相减例题：证明 $\gcd(2^i-1,2^j-1)=2^{\gcd(i,j)}-1$
设 $j>i$

$gcd(2^i-1,2^j-1)=gcd(2^i-1,2^j-2^i)=gcd(2^i-1,2^i(2^{j-i}-1))$

因为 $gcd(2^i-1,2^i)=1$

所以 $gcd(2^i-1,2^i(2^{j-i}-1))=gcd(2^i-1,2^{j-i}-1)$

发现指数上的辗转相减形式

$gcd(2^i-1,2^j-1)=2^{gcd(i,j)}-1$
## 时间复杂度
$O(log n)$
```c++
//手写
int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}
//库函数,最好用这个
<algorithm> 里的__gcd
```
# exgcd
解二元一次方程，多元一次方程可以拆解为多个二元一次方程

$Ax+By+Cz\equiv d\rightarrow\begin{cases}Ax+By=k\gcd(A,B)\\k\gcd(A,B)+Cz=d\end{cases}$

下面以二元一次方程为例： $Ax+By=C$

设 $d=gcd(A,B)$

若 $C \% d\ne 0$,则方程无解

例如 $2x+4y=1$ 没有整数解，因为 $gcd=2$，$1\%2\ne 0$

exgcd解出最大公约数 $d$，特解$x_0,y_0$

通解： $x=\frac Cdx_0+\frac Bdk$，$y=\frac Cdy_0-\frac Adk$
```c++
int exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	int r=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return r;
}
```
#! https://zhuanlan.zhihu.com/p/557860454
part 1
# gcd
欧几里得算法（又名辗转相除法）
## 时间复杂度
$O(log n)$
## 代码
```c++
//手写
int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}
//库函数,最好用这个
<algorithm> 里的__gcd
```

part 2
# exgcd

解线性同余方程，其形式如下

$Ax\equiv C \pmod B$
，其中$A$、$B$、$C$都为常量，$x$是未知数

可以转化为$Ax+By=C$.  

$A$、$B$、$C$是整数,求$x$和$y$的整数解

设$d=gcd(A,B)$

若$C \% d!=0$,则方程无解

例如$2*x+4*y=1$没有整数解，因为gcd=2，$1\%2=1$

exgcd解出特解$x_0,y_0$

通解：

$x=C/d*x_0+B/d*k$，$y=C/d*y_0-A/d*k$。

exgcd函数返回值是最大公约数

## 代码
```c++
int exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	int r=exgcd(b,a%b,y,x);
	y-=x*(a/b);
	return r;
}
```
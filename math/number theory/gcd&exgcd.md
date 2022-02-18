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

$ax\equiv b \pmod n$
，其中$a$、$b$、$n$都为常量，$x$是未知数

可以转化为$Ax+By=C$.  

$A$、$B$、$C$是整数,求$x$和$y$的整数解

设$d=gcd(A,B)$

若$C \% d=0$,则方程有解

例如$2*x+4*y=1$没有整数解，因为gcd=2，$1\%2=1$

有解的方程取一般形式为$ax+by=c$,

(若C是c的倍数,x和y乘相应的倍数即可)

$x=x_0+B*k/d$，$y=y_0-A*k/d$。

(k是任意整数,/是整除,$x_0$和$y_0$是特解)

exgcd函数返回值是最大公约数,调用后引用的x和y赋值为特解

如需求X正整数最小解

加上以下代码
```c++
	int t=B/d;
	ans=(C/d*x%t+t)%t;
```
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
/*
part 1
欧几里得算法（又名辗转相除法）
时间复杂度(log n)
空间复杂度(log n)
gcd:
最大公因数Greatest Common Divisor(简称gcd)
1：求最大公约数
最小公倍数=两整数的乘积÷最大公约数
2：判断是否互质(gcd=1)
*/
//手写
int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}
//库函数,最好用这个
//<algorithm> 里的__gcd

/*
part 2
exgcd：
解线性同余方程，其形式如下
ax≡b (mod n)，其中a、b、n都为常量，x是未知数
可以转化为Ax+By=C.   A、B、C是整数,求x和y的整数解
设d=gcd(A,B)
若C%d==0,则方程有解
例如2*x+4*y=1没有整数解，因为gcd=2，1%2=1
有解的方程取一般形式为ax+by=c,(若C是c的倍数,x和y乘相应的倍数即可)
x=x0+B*k/d,y=y0-A*k/d。(k是任意整数,/是整除,x0和y0是特解)
exgcd函数返回值是最大公约数,调用后引用的x和y赋值为特解
如需求X正整数最小解
加上以下代码
	int t=B/d;
	ans=(C/d*x%t+t)%t;
*/

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
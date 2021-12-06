/*
欧几里得算法（又名辗转相除法）
时间复杂度(log n)
空间复杂度(log n)
gcd:
最大公因数Greatest Common Divisor(简称gcd)
1：求最大公约数
最小公倍数=两整数的乘积÷最大公约数
2：判断是否互质(gcd=1)

exgcd：
解线性同余方程
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
//递归版
int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}
//迭代版
int gcd(int a,int b)
{
	while(b)
	{
		int c=a%b;
		a=b;
		b=c;
	}
	return a;
}
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
/*
结论：gcd(a,b)=gcd(b,a%b)           gcd(a,0)设为a
证明:
证明分为两步骤：
1、证明gcd(a,b)是a%b的一个因子
2、证明这个因子是gcd(b,a%b)

1:
设gcd(a,b)=d,再令a=k1*d,b=k2*d
再设,a=k*b+c,则a%b=c
c=a-k*b
c=k1*d-k*k2*d=(k1-k*k2)*d
c有d这个因子

2:
已知，c =（k1-k*k2）*d,b=k2*d
只需证明k1-k*k2，k2互质
反证：
设k1-k*k2=q*t,k2=p*t,且t>1（也就是那两个不互质）
k1=q*t+k*k2
a=(q*t+k*k2)*d
a=q*t*d+k*p*t*d
a=(q+k*p)*t*d
b=p*t*d
gcd(a,b)=t*d,矛盾，所以假设不成立，得证
证明完毕
*/
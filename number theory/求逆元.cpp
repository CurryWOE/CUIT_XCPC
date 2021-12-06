/*
求a的逆元x
模意义下，一个数a可能有唯一的与之对应的乘法逆元x，使得a*x≡1(mod n)
一个数有逆元的充分必要条件是gcd(a,n)=1，此时逆元唯一存在
逆元的含义：模n意义下，1个数a如果有逆元x，那么除以a相当于乘以x
逆元用处：(a/b)%p=(a%p*inv(b)%p)%p
*/

/*
1:EXgcd扩展欧几里得
ln(n)   (时间复杂度最优)
求a的逆元相当于求解ax=1(mod n),这个方程可以转化为ax-ny=1
然后套用求二元一次方程的方法，用扩展欧几里得算法求得一组x0,y0和gcd
*/
long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	long long r=exgcd(b,a%b,y,x);
	y-=x*(a/b);
	return r;
}
long long inverse_element(long long a,long long n)
{
    long long x,y;
    if(exgcd(a,n,x,y)==1ll)
        return (x%n+n)%n;
    else
        return -1;
}

/*
2:费马小定理及欧拉定理
欧拉定理
sqrt(n)+log2(n)
a^-1≡a^(φ(n)-1)  (mod n)
*/
long long euler(long long n)
{
    long long res=n,a=n;  
    for(long long i=2;i*i<=a;i++)
    {  
        if(a%i==0)
        {  
            res=res/i*(i-1);//先除后乘是为了防止中间数据的溢出
            while(a%i==0)
                a/=i;
        }
    }
    if(a>1)
        res=res/a*(a-1);
    return res;
}
long long qpow(long long base,long long power,long long n)
{
    long long result=1;
    while(power>0)
    {
        if(power&1)
            result=result*base%n;
        base=base*base%n;
        power>>=1;
    }
    return result;
}
long long inverse_element(long long a,long long n)
{
    long long ie=qpow(a,euler(n)-1,n);
    if(ie*a%n==1ll)
        return ie;
    else
        return -1;//逆元不存在
}
/*
费马小定理
log2(n)
a^-1≡a^(n-2)     (mod n)
*/
long long qpow(long long base,long long power,long long n)
{
    long long result=1;
    while(power>0)
    {
        if(power&1)
            result=result*base%n;
        base=base*base%n;
        power>>=1;
    }
    return result;
}
long long inverse_element(long long a,long long n)
{
    return qpow(a,n-2,n);
}

/*
3:逆元打表
在模质数p下，求1~n逆元, n < p (p是奇质数)
O(n)
设t=M/i,k=M%i
t*i+k≡0 (mod M)
-t*i≡k (mod M)
-t*inv(k)=inv(i) (mod M)
inv(i)=(M-M/i)*inv(M%i)%M
inv(1)=1
*/
const int N = 1e5 + 5;
int inv[N];
void inverse(int n, int p) 
{
    inv[1] = 1;
    for(int i=2; i<=n; ++i)
        inv[i] = (ll) (p - p / i) * inv[p%i] % p;
}
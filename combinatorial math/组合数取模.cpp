/*
1.杨辉三角
适用条件：n,m都很小
公式：C(n,m)=C(n-1,m)+C(n-1,m-1)
证明：
n个元素里选m个
相当于分两种情况讨论：
选第一个，在后面n-1个选m-1个
不选第一个，在后面n-1个选m个
时间复杂度：O(nm)
*/
long long c[4000][4000];
void yanghui_triangle(int n,int m)
{
    c[0][0]=1ll;
    for(int i=1;i<=n;++i)
    {
        c[i][0]=1ll;
        for(int j=1;j<=m;++j)
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
}
/*
2.Lucas定理
适用条件：n,m较大，p为素数
公式：C(n,m)%p=C(n/p,m/p)*C(n%p,m%p)%p
时间复杂度：O(f(x)+g(n)logp n)
f(x)为预处理组合数的复杂度，g(n)为单次求组合数的复杂度
p小，逆元打表，O(n+p+logp n)
//n为处理阶乘，p为打表，logp n为单次查询
p大，exgcd求逆元,O(n+ln p*logp n)
//n为处理阶乘，ln p*logp n为单次查询
*/
long long Lucas(long long n, long long m, long long p)
{
    if (m == 0) return 1;
    return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}
/*
3.exLucas
适用条件：n,m较大，p不为素数
前置知识：快速幂，逆元，lucas，crt
原理讲解见
https://www.cnblogs.com/fzl194/p/9095177.html
时间复杂度：O(plog p)
*/
ll qpow(ll base,ll exponent,ll mod)
{
    ll result=1;
    for(;exponent;base=base*base%mod,exponent>>=1)
    {
        if(exponent&1)
            result=result*base%mod;
    }
    return result;
}
ll g(ll n,ll p)
{
    if(n<p)
        return 0;
    return g(n/p,p)+n/p;
}
ll calc(ll n,ll p,ll MOD)
{
    if(n==0)
        return 1;
    ll res=1;
    for(ll i=1;i<=MOD;i++)
    {
        if(i%p)
            res=res*i%MOD;
    }
    res=qpow(res,n/MOD,MOD);
    for(ll i=n/MOD*MOD+1;i<=n;i++)
    {
        if(i%p)
            res=res*(i%MOD)%MOD;
    }
    return res*calc(n/p,p,MOD)%MOD;
}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b) {x=1,y=0;return a;}
	ll r=exgcd(b,a%b,y,x);
	y-=x*(a/b);
	return r;
}
ll inv(ll a,ll n)
{
    ll x,y;
    if(exgcd(a,n,x,y)==1ll)
        return (x%n+n)%n;
    else
        return -1;
}
ll lucas(ll n,ll m,ll p,ll MOD)
{
    ll pw=qpow(p,g(n,p)-g(m,p)-g(n-m,p),MOD);
    return calc(n,p,MOD)*inv(calc(m,p,MOD),MOD)%MOD*inv(calc(n-m,p,MOD),MOD)%MOD*pw%MOD;
}
ll CRT(const vector<ll> &a,const vector<ll> &m)
{
    int siz=a.size();
    ll mul=1,sum=0;
    for(auto tmp:m) 
        mul*=tmp;
    for(int i=0;i<siz;i++)
    {
        ll M=mul/m[i];
        sum=(sum+a[i]*M%mul*inv(M,m[i]))%mul;
    }
    return sum%mul;
}
ll exlucas(ll n,ll m,ll MOD)
{
    vector<ll> a,mod;
    ll tmp=MOD;
    for(int p=2;p<=tmp/p;p++)
    {
        if(tmp%p==0)
        {
            ll mul=1;
            while(tmp%p==0) 
                mul*=p,tmp/=p;
            mod.push_back(mul),a.push_back(lucas(n,m,p,mul));
        }
    }
    if(tmp>1) mod.push_back(tmp),a.push_back(lucas(n,m,tmp,tmp));
    return CRT(a,mod);
}
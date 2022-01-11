/*
part 1
y^x ≡ z (mod p)
给定y,z,p，求最小x
要求gcd(y,p)=1
设x=a*m-b,m=向上取整(sqrt(p)),a∈(0,m+1],b∈[0,m)
y^(a*m) ≡ z*y^b  (mod p)
右边的b枚举[0,m)，算出z∗y^b (mod p)，哈希存起来
左边a枚举(0,m+1]，算出y^(a∗m) (mod p)查表就行了
时间复杂度O(sqrt(p))
空间复杂度O(sqrt(p))
哈希表放最下面
*/
ll bsgs(ll base,ll remain,ll p)
{
	base%=p;
	remain%=p;
	ll t=ceil(sqrt(1.0*p));
	for(ll i=1;i<=t;++i)
    {
        remain=remain*base%p;
        insert(i,remain);
    }
	base=fast_power(base,t,p);
	if(!base)
        return !remain ? 1 : -1;
    remain=1;
    int flag;
	for(ll i=1;i<=t;++i)
    {
		remain=remain*base%p;
        flag=find(remain);
        if(flag!=-1)
            return i*t-flag;
	}
	return -1;
}
/*
part 2
exbsgs
gcd(y,p)!=1
d=gcd(y,p)
改写成等式形式
y^x + k*p = z
发现此时的z必须要是d的倍数，否则无解。
因此，除掉d
y/d * y^(x-1) + k*(p/d) = z/d
这样前面的y/d就是一个系数了，
不断检查gcd(z/d,y)，一直除到互质为止
此时的形式就变成了
y^k/d *y^(x-k) = z/d (mod p/d)
*/
ll EXbsgs(ll base,ll remain,ll mod)
{
    base%=mod;
    remain%=mod;
	if(remain==1)
        return 0;
	ll k=0,a=1;
	for(ll g=__gcd(base,mod);g>1;g=__gcd(base,mod))
	{
		if(remain%g)
            return -1;
		remain/=g;
        mod/=g;
        ++k;
        a=a*(base/g)%mod;
		if(remain==a)
            return k;
	}
    init();
	ll m=ceil(sqrt(1.0*mod));
	for(int i=1;i<=m;++i)
    {
        remain=remain*base%mod;
        insert(i,remain);
    }
    base=fast_power(base,m,mod);
    remain=a;
    ll flag;
	for(ll i=1;i<=m;++i)
	{
        remain=remain*base%mod;
        flag=find(remain);
        if(flag!=-1)
            return (i*m-flag+k);
	}
	return -1;
}
//返回值要求余mod,但不能在子函数里，因为mod变了
//哈希表
typedef long long ll;
const int MAXN=1e7+1;
struct hash
{
    ll id,value;
    int next;
}e[MAXN];
int head[MAXN];
int tot;
inline ll hashfunc(ll x) 
{
    return x%MAXN;
}
void insert(ll id,ll x)
{
    e[++tot]={id,x,head[hashfunc(x)]};
    head[hashfunc(x)]=tot;
}
ll find(ll x)
{
    for(int i=head[hashfunc(x)];i;i=e[i].next)
    {
        if(e[i].value==x)
            return e[i].id;
    }
    return -1;
}
void clear()
{
    for(;tot;--tot)
        head[hashfunc(e[tot].value)]=0;
}
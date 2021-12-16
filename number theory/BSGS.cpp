/*
y^x ≡ z (mod p)
给定y,z,p，求最小x
要求gcd(y,p)=1
设x=a*m-b,m=向上取整(根号p),a∈(0,m+1],b∈[0,m)
y^(a*m) ≡ z*y^b  (mod p)
右边的b枚举[0,m)，算出z∗y^b (mod p)，哈希存起来
左边a枚举(0,m+1]，算出y^(a∗m) (mod p)查表就行了
*/
long long bsgs(long long base,long long remain,long long p)
{
	map<long long,long long> hash;
    hash.clear();
	base%=p;
	remain%=p;
	long long t=sqrt(p)+1;
	for(register long long i=0;i<t;++i)
    {
		hash[remain]=i;
        remain=remain*base%p;
    }
	base=fast_power(base,t,p);
	if(!base)
        return remain==0 ? 1 : -1;
    remain=1;
	for(long long i=1;i<=t;++i)
    {
		remain=remain*base%p;
        if(hash.count(remain))
            return i*t-hash[remain];
	}
	return -1;
}
/*
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
    map<ll,ll> hash;
    hash.clear();
	ll m=sqrt(mod)+1;
	for(int i=0;i<m;++i)
    {
        hash[remain]=i;
        remain=remain*base%mod;
    }
    base=fast_power(base,m,mod);
    remain=a;
	for(ll i=1;i<=m;++i)
	{
        remain=remain*base%mod;
        if(hash.count(remain))
            return (i*m-hash[remain]+k);
	}
	return -1;
}
//返回值要求余mod,但不能在子函数里，因为mod变了
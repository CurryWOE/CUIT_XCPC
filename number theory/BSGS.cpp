/*
y^x ≡ z (mod p)
给定y,z,p，求最小x
要求gcd(y,p)=1
设x=a*m-b,m=向上取整(根号p),a∈(0,m+1],b∈[0,m)
y^(a*m) ≡ z*y^b  (mod p)
右边的b枚举[0,m)，算出z∗y^b (mod p)，哈希存起来
左边a枚举(0,m+1]，算出y^(a∗m) (mod p)查表就行了
*/
long long bsgs(long long a,long long b,long long p)
{
	map<long long,long long> hash;
    hash.clear();
	b%=p;
	long long t=sqrt(p)+1;
	for(register long long i=0;i<t;++i)
		hash[b*fast_power(a,i,p)%p]=i;
	a=fast_power(a,t,p);
	if(!a)
        return b==0?1:-1;//特判
	for(register long long i=1;i<=t;++i)
    {
		long long val=fast_power(a,i,p);
		int j=hash.find(val)==hash.end()?-1:hash[val];
		if(j>=0&&i*t-j>=0)
            return i*t-j;
	}
	return -1;//无解返回-1
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
int ex_BSGS(int y,int z,int p)//Hash是一个散列表
{
	if(z==1)
        return 0;
	int k=0,a=1;
	while(1)
	{
		int d=__gcd(y,p);
        if(d==1)
            break;
		if(z%d)
            return -1;
		z/=d;
        p/=d;
        ++k;
        a=1ll*a*y/d%p;
		if(z==a)
            return k;
	}
	Hash.clear();
	int m=sqrt(p)+1;
	for(int i=0,t=z;i<m;++i,t=1ll*t*y%p)
        Hash.Insert(t,i);
	for(int i=1,tt=fast_power(y,m,p),t=1ll*a*tt%p;i<=m;++i,t=1ll*t*tt%p)
	{
		int B=Hash.Query(t);
        if(B!=-1)
    		return i*m-B+k;
	}
	return -1;
}
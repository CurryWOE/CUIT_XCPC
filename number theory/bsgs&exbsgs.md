## 离散对数

### 定义

当模 $m$ 有原根是，设 $l$ 为模 $m$ 的一个原根，则当 $x\equiv l^k \pmod m$ 时，$Ind_lx\equiv k \pmod {φ(m)}$

这里的 $Ind_lx$ 为 $x$ 以 $l$ 为底，模 $φ(m)$ 时的离散对数值

$1 \le k \le φ(m)$

### 性质

离散对数和普通对数有类似的性质

$Ind_lxy\equiv Ind_lx+Ind_ly \pmod {φ(m)}$

$Ind_lx^y\equiv yInd_lx \pmod {φ(m)}$

通过这些性质，可以将乘法操作变成加法操作，来简化或者解决一些运算问题.

## BSGS

求离散对数

### 前提条件

$gcd(base,modulus)=1$

### 原理

由欧拉定理推论

$a^b=a^{b\%φ(n)} \pmod n$

得知 $a^b$ 在模 $n$ 下有长度为 $φ(n)$ 的循环节

所以最多枚举 $φ(n)$ 次 $a^b$ 就可以求出离散对数

但是如果 $n$ 是质数，那暴力枚举时间复杂度就是 $O(n)$

bsgs时间复杂度更优

$y^x \equiv z \pmod p$

给定 $y$ , $z$ , $p$ , 求 $x$ 最小正整数解

设$x=am-b$，$m=\left\lceil \sqrt p\right\rceil$，$a\in[1,m],b\in[1,m]$

>$\left\lceil x\right\rceil$是向上取整

$a$,$b$的值域保证$x$取遍$[0,p]$

原式变为

$y^{am} ≡ z*y^b  \pmod p$

如果发现这个式子成立，说明有解

### 时间复杂度

$O(\sqrt {modulus})$

### 算法流程

右边的$b$枚举$[1,m]$，算出$z∗y^b \pmod p$，哈希存起来

PS：map也可以过一些题，但是如果卡常就不行，所以最好用哈希表

左边$a$枚举$[1,m]$，算出$(y^m)^a \pmod p$查表就行了

如果$p\mid base^m$，那么remain只能是0，否则无解

### 代码
```c++
long long bsgs(long long base,long long remain,long long p)
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
```

## exbsgs

解决$gcd(base,modulus)\ne 1$的情况

### 原理

$y^x \equiv z \pmod p$

设$g=gcd(y,p)$

发现此时的$z$必须要是$g$的倍数，否则无解。

因此，除掉g

<font size=4>$\frac{y}{g} * y^{x-1} \equiv \frac{z}{g} \pmod {\frac{p}{g}}$</font>

不断检查$gcd(p,y)$，一直除到互质为止

此时的形式就变成了

<font size=6>$\frac{y^k}{\prod\limits_{i=1}^k g_i} *y^{x-k} = \frac{z}{\prod\limits_{i=1}^k g_i} \pmod {\frac{p}{\prod\limits_{i=1}^k g_i}}$</font>

互质之后就可以套用bsgs了

```c++
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
    clear();
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
```
## 哈希表
链地址法解决冲突
```c++
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
```

## pohlig-hellman
待更新
/*
线性筛（又名欧拉筛）
快速查询某数是否素数，查找出范围内所有素数
时间复杂度O(n)
v[i]为0表示i是素数，为1表示i是合数
p存放素数
i%p[j]==0 break;减少重复筛
*/
const long long N=1e7+3;
int v[N],p[N>>2];
void Euler_seive()
{
	int cnt=0;
	for(int i=2;i<N;++i)
	{
		if(!v[i])
			p[cnt++]=i;
		for(int j=0;j<cnt && i*p[j]<N;++j)
		{
			v[i*p[j]]=1;
			if(i%p[j]==0)
				break;
		}
	}
}
/*
下面内容和莫比乌斯反演有关，
可以用线性筛求一些积性函数
概念解释：
数论函数（又称算术函数）：
在数论上，指定义域为正整数、陪域为复数的函数
陪域：
在映射f：X→Y 中，X称为定义域，Y称为陪域。
对于某个映射来说，它的值域一定为陪域的子集
积性函数：
数论函数中
若p,q互质，满足f[p*q]=f[p]*f[q]
则f为积性函数
如约数，欧拉，莫比乌斯
若任意p,q,满足f[p*q]=f[p]*f[q]
则f为完全积性函数
如1函数，即f[x]=1

积性函数性质可知，f[1]=1
*/
/*
欧拉函数φ
1-n,和n互质的数的个数
*/
const long long N=1e7+3; 
int v[N],p[N>>2],phi[N];
void getphi()
{
	int cnt=0;
    phi[1]=1;
    for(int i=2;i<N;++i)
    {
        if(!v[i])
        {
            prime[cnt++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j < cnt && p[j]*i < N;++j)
        {
            v[i*p[j]]=1;
            if(i%p[j]==0)
            {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
			phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
}
/*莫比乌斯函数μ
有平方因子，函数为0
否则，函数=(-1)^k,k为质因子个数
*/
const long long N=1e7+3;
int v[N],p[N>>2],mu[N];
void getmu()
{
	int cnt=0;
	mu[1]=1;
	for(int i=2;i<N;++i)
	{
		if(!v[i])
		{
			p[cnt++]=i;
			mu[i]=-1;
		}
		for(int j=0;j < cnt && i*p[j] < N;++j)
		{
			v[i*p[j]]=1;
			if(i%p[j])
				mu[i*p[j]]=-mu[i];
			else
			{
				//mu[i*p[j]]=0;
				//全局变量初始为0，所以这句可省去
				break;
			}
		}
	}
}
/*
约数：
约数有两种，分别是求约数个数，求约数和
https://blog.csdn.net/controlbear/article/details/77527115
*/
//约数个数
//dn:divisor number,mpdn:minimum prime divisor number
const long long N=1e7+3;
int v[N],p[N>>2],dn[N],mpdn[N];
void getDivisorNumber()
{
	int cnt=0;
	for(int i=2;i<N;++i)
    {
        if(!v[i])
		{
			p[cnt++]=i;
			dn[i]=2;
			mpdn[i]=1;
		}
        for(int j=0;j < cnt && i*p[j] < N;++j)
        {
            v[i*p[j]]=1;
            if(i%p[j]==0)
            {
				mpdn[i*p[j]] = mpdn[i]+1;
                dn[i*p[j]]=dn[i]/(mpdn[i]+1)*(mpdn[i]+1);
                break;
            }
			dn[i*p[j]]=dn[i]*dn[p[j]];
			mpdn[i*p[j]]=1;
			//p[j]是i*p[j]的最小素因子 
        }
    }
}
//约数和
//sd:sum of divisor,smpd:sum of minimum prime divisor polynomial
//sd约数和，smpd最小质因子的那个多项式（也可以理解为由最小质因子组成的数的约数和吧） 
const long long N=1e7+3;
int v[N],p[N>>2],sd[N],smpd[N];
void getSumOfDivisors()
{
	int cnt=0;
    sd[1]=1;
    for(int i=2;i<N;++i)
    {
        if(!v[i])
		{
			p[cnt++]=i;
			sd[i]=i+1;
			smpd[i]=i+1;
		}
        for(int j=0;j<cnt && i*prime[j]<N;++j)
        {
            v[i*p[j]]=1;
            if(i%p[j]==0)
            {
				smpd[i*p[j]]=smpd[i]*p[j]+1;
                sd[i*p[j]]=sd[i]/smpd[i]*smpd[i*p[j]];
                break;
            }
			sd[i*p[j]]=sd[i]*sd[p[j]];
			smpd[i*p[j]]=p[j]+1;
        }
    }
}
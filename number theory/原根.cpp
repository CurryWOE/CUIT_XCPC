/*
证明啥的太复杂，也用不上，就不写了
//https://zhuanlan.zhihu.com/p/166043237
//https://www.luogu.com.cn/problem/solution/P6091
原根(Primitive Root)定义:
如果a^x≡1 (mod p),且x为最小正整数解,且x=φ(p)
则a为模p下的一个原根

原根存在充要条件：
p能表示为下列形式之一：1,2,4,k^n,2*k^n，其中 k 为奇素数。
a^φ(p)≡1 (mod p)或者gcd(a,p)=1(欧拉定理)

原根数量：
φ(φ(p))
//φ表示欧拉函数

求 p 的所有原根的步骤为：
1.线性筛出不大于 p 的素数，并求出所有不大于 p 的正整数的欧拉函数值。
对每个不大于 p 的素数 m ，求出所有不大于 p 的 m^q 和 2*m^q。
2.判断 p 是否有原根
3.求最小原根
求出 φ(p) 的所有因数，由于质数已经筛出，复杂度 O((n^0.5)/logn) 
枚举 i ,满足i^φ(p)=1,
对于 φ(p) 的每个因数 j ，分别计算 i^j ，如果 j!=φ(p) 但 i^j≡1 (mod p)
说明 i不是原根
继续循环，直到找到合适的 i 为止
4.求所有原根
枚举 φ(p) 以内的正整数 s
如果 s 与 φ(p) 互质，则 a^s 是一个原根
求s,用埃氏筛的思想。
φ(p) 的质因数已经求出，可以用这些数标记所有与 φ(p) 不互质的数，
复杂度优化至 O(nlogloglogn) 。

优化
如果要求顺序输出原根，基数排序比快速排序更快
*/
//luogu p6091
typedef long long ll;
const int N=1e6+7;
int p[N],phi[N],factor[15];
bool v[N],pr[N],coprime[N],proot[N];
void init(int n)//筛素数，欧拉函数，有原根的数
{
	pr[1]=pr[2]=pr[4]=phi[1]=1;
	int cnt=0;
	for(int i=2;i<=n;++i)
    {
		if(!v[i])
        {
            p[cnt++]=i;
            phi[i]=i-1;
        }
		for(int j=0;j<cnt && p[j]*i<=n;++j)
        {
			v[p[j]*i]=1;
			if(!(i%p[j]))
            {
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*phi[p[j]];
		}
	}
	for(int i=1;i<cnt;++i)
    {
        for(ll j=p[i];j<=n;j*=p[i])
            pr[j]=1;
        for(ll j=2*p[i];j<=n;j*=p[i])
            pr[j]=1;
	}
}
long long fast_power(long long base,long long exponent,ll mod)
{
    long long result=1;
    for(;exponent>0;exponent>>=1)
    {
        if(exponent&1)
            result=result*base%mod;
        base=base*base%mod;
    }
    return result;
}
vector<int> PrimitiveRoot(int n)
{
    vector<int> vec;
    if(!pr[n])//模数n没有原根
        return vec;
    int temp=phi[n];
    int cnt=0;
    if(phi[n]!=1)
        coprime[phi[n]]=1;
    for(int i=0;p[i]*p[i]<=temp;++i)//求φ(n)的质因子，用埃氏筛的思想筛出与φ(n)互质的数(即coprime[i]=0)
    {
        if(!(temp%p[i]))
        {
            factor[cnt++]=p[i];
            while(!(temp%p[i]))
                temp/=p[i];
            for(int j=p[i];j<phi[n];j+=p[i])
                coprime[j]=1;
        }
    }
    if(temp>1)//处理大于根号φ(n)的质因子
    {
        factor[cnt++]=temp;
        for(int i=temp;i<phi[n];i+=temp)
            coprime[i]=1;
    }
    int minPr=1;
    for(;;++minPr)//求最小原根
    {
        for(;fast_power(minPr,phi[n],n)!=1;++minPr);
        int j=0;
        for(;j<cnt && fast_power(minPr,phi[n]/factor[j],n)!=1;++j);
        if(j>=cnt)
            break;
    }
    temp=minPr;
    for(int i=1;i<=phi[n];++i,temp=temp*minPr%n)//求所有原根
    {
        if(!coprime[i])
            proot[temp]=1;
        else
            coprime[i]=0;//清零
    }
    for(int i=1;i<n;++i)//排序原根
    {
        if(proot[i])
        {
            proot[i]=0;//清零
            vec.push_back(i);
        }
    }
    return vec;
}
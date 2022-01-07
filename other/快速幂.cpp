/*
快速幂：
给出底数和指数，快速求出幂
时间复杂度O(log n)
空间复杂度O(1)
计算2^k,位运算最快:1<<k(1左移k位)
若用LL，则1LL<<k
*/
//倍增，仅用于理解，不会用到
int qpow(int a, int n)
{
    if (n == 0)
        return 1;
    else if (n&1)
        return qpow(a, n - 1) * a;
    else
    {
        int temp = qpow(a, n>>1);//必须，否则算法退化
        return temp * temp;
    }
}
//循环，常用，用二进制表示指数
//5=101,3^5=3^(2^0+2^2)=3^(2^0) * 3^(2^2)
//通过上式可以发现，只有指数当前位为1，才对答案有贡献
long long fast_power(long long base,long long exponent)
{
    long long result=1;
    for(;exponent>0;exponent>>=1)
    {
        if(exponent&1)
            result=result*base;
        base=base*base;
    }
    return result;
}
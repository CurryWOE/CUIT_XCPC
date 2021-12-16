/*
快速幂：
给出底数和指数，快速求出幂
时间复杂度O(log n)
空间复杂度O(1)
无论是cmath头文件里的pow还是for循环处理都需要O(n)的时间复杂度
计算2^k,位运算最快:1<<k(1左移k位)
若用LL，则1LL<<k
*/
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
/*
矩阵快速幂：
给出底矩阵和指数，快速求出幂矩阵
时间复杂度O(t^3*log n),t是矩阵边长，t^3表示矩阵乘法
空间复杂度O(t^2)
把对整数的操作移植到矩阵上来
应用：
给出多项式定义，满足递推关系，可以用矩阵快速幂快速求出第n项
1.从题目抽象出底矩阵和指数
2.抽象出第一项矩阵
3.用矩阵快速幂求幂
4.幂和第一项矩阵相乘得目标矩阵
5.输出答案

常见多项式抽象：
1.
f(n) = a * f(n-1) + b * f(n-2) +c
a b 1     f(n-1)        f(n)
1 0 0     f(n-2)        f(n-1)
0 0 1        c            c
2.
f(n) = f(n-1) + c^n
1 c        f(n-1)        f(n)
0 c        c^(n-1)       c^n
3.
f(n)= f(n-1) + n^3
因为
n^3 = (n - 1 + 1)^3
    = C(0,3)*(n-1)^3 + C(1,3)*(n-1)^2 + C(2,3)*(n-1)^1 + C(3,3)*(n-1)^0
所以
1 C(0,3) C(1,3) C(2,3) C(3,3)     f(n-1)          f(n)
0 C(0,3) C(1,3) C(2,3) C(3,3)     (n-1)^3         n^3
0 0      C(0,2) C(1,2) C(2,2)     (n-1)^2         n^2
0 0      0      C(0,1) C(1,1)     (n-1)^1         n^1
0 0      0      0      C(0,0)     (n-1)^0         n^0
*/
const int MAXN = 4;
struct matrix
{
    int row,column;
    ll m[MAXN][MAXN];
};
matrix e;//单位矩阵
for(int i=0;i<MAXN;++i)
{
    for(int j=0;j<MAXN;++j)
        e.m[i][j]=(i==j);
}
e.column=e.column=MAXN;
matrix Matrix_multiplication(matrix x,matrix y)
{
    matrix c;
    c.row=x.row;
    c.column=y.column;
    for(int i=0;i<c.row;++i)
    {
        for(int j=0;j<c.column;++j)
            c.m[i][j] = 0;
    }
    //稠密矩阵
    for(int i=0;i<c.row;++i)
    {
        for(int j=0;j<c.column;++j)
        {
            for(int k=0;k<x.column;++k)
                c.m[i][j] = (c.m[i][j] + x.m[i][k] * y.m[k][j] % mod) % mod;
        }
    }
    //稀疏矩阵
    for(int i=0;i<c.row;++i)
    {
        for(int j=0;j<x.column;++j)
        {
            if(!x.m[i][j])
                continue;
            for(int k=0;k<c.column;++k)
                c.m[i][k] = (c.m[i][k] + x.m[i][j] * y.m[j][k] % mod) % mod;
        }
    }
    return c;
}
matrix Matrix_fast_power(matrix base,ll exponent)
{
    matrix result = e;
    result.column=result.row=MAXN;
    for(;exponent;exponent>>=1)
    {
        if(exponent&1)
            result = Matrix_multiplication(result,base);
        base = Matrix_multiplication(base,base);
    }
    return result;
}
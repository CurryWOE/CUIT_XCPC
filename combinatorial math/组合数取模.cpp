/*
1.当n,m都很小的时候可以利用杨辉三角直接求
C(n,m)=C(n-1,m)+C(n-1,m-1)
*/
ll c[4000][4000];
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
2.n和m较大，但是p为素数的时候
Lucas定理是用来求 c(n,m) mod p，p为素数的值。
C(n,m)%p=C(n/p,m/p)*C(n%p,m%p)%p
也就是Lucas(n,m)%p=Lucas(n/p,m/p)*C(n%p,m%p)%p
施工中
*/
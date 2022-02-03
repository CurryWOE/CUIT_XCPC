ll qmul(ll a,ll b,ll mod)a*b%mod
{
    ll c=(ld)a/mod*b;
    ll res=(ull)a*b-(ull)c*mod;
    return (res+mod)%mod;
}
//用溢出解决溢出
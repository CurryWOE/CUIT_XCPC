typedef long long ll;
const int MAXN = 3e6 + 10;
const int P = 998244353;
const int G = 3;
const int Gi = 332748118;//G在模P的逆元
int N, M, limit, l, r[MAXN];
ll a[MAXN], b[MAXN];
ll fastpow(ll a, ll k)
{
	ll base = 1;
	for(;k;k>>=1)
    {
		if(k & 1)
            base = (base * a ) % P;
		a = (a * a) % P;
	}
	return base % P;
}
void NTT(ll *A, int type)
{
	for(int i = 0; i < limit; i++)
    {
		if(i < r[i])
            swap(A[i], A[r[i]]);
    }
	for(int mid = 1; mid < limit; mid <<= 1)
    {	
		ll Wn = fastpow( type == 1 ? G : Gi , (P - 1) / (mid << 1));
		for(int j = 0,R=mid<<1; j < limit; j +=R)
        {
			ll w = 1;
			for(int k = 0; k < mid; k++, w = (w * Wn) % P)
            {
				 int x = A[j + k], y = w * A[j + k + mid] % P;
				 A[j + k] = (x + y) % P,
				 A[j + k + mid] = (x - y + P) % P;
			}
		}
	}
    if(type==-1)
    {
        ll inv = fastpow(limit, P - 2);
        for(int i=N+M;i>=0;--i)
            A[i]=A[i]*inv%P;
    }
}
void init(int x)
{
    limit=1;
    l=-1;
    while(limit<x)
        limit<<=1,++l;
    for(int i=0;i<limit;++i)
        r[i]=(r[i>>1]>>1)|((i&1)<<l);
}
init(N+M+1);
NTT(a, 1);
NTT(b, 1);
for(int i = 0; i < limit; i++)
    a[i] = (a[i] * b[i]) % P;
NTT(a, -1);

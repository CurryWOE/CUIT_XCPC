#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ll n,sum=0ll;
    scanf("%lld",&n);
    for(ll l=1,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        sum+=(r-l+1)*(n/l);
    }
    printf("%lld",sum);
    return 0;
}
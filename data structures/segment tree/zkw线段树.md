```cpp
#include <bit>
struct zkwSegmentTree
{
    int sum[N<<2];
    int N;
    void Build(int n)
    {
        //+2是查询需要为左右各预留一个点
        N=bit_ceil(n+2);//bit_ceil找到大于或等于 target 的最小 2 的幂次
        for(int i=1;i<=n;++i)
            sum[N+i]=A[i];
        for(int i=N-1;i;--i)
        {
            sum[i]=sum[i<<1]+sum[i<<1|1];
        }
    }
    void Update(int q,int c)
    {
        for(int i=N+q;i;i>>=1)
            sum[i]+=c;
    }
    int Query(int l,int r)
    {
        int ans=0;
        for(int L=N+l-1,R=N+r+1;L^R^1;L>>=1,R>>=1)
        {
            if(~L&1)
                ans+=sum[L+1];
            if(R&1)
                ans+=sum[R-1];
        }
        return ans;
    }
}
```
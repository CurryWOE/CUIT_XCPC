#! https://zhuanlan.zhihu.com/p/559793518
# 稀疏表(Sparse Table)
符合结合律且可重复贡献的信息查询

可重复贡献：交集不为空的区间合并，不影响结果

倍增思想
# 时间复杂度
$O(nlogn)$ 预处理

$O(1)$ 查询
# 空间复杂度
$O(nlogn)$

# 板子
```cpp
const uint32_t N = 5e4 + 3,M = bit_width(N);
namespace SparseTable
{
    int st[M][N];
    void init(uint32_t n)
    {
        memcpy(st[0],a,sizeof(int)*(n+1));
        for (uint32_t i = 1; i < bit_width(n); ++i)
            for (uint32_t j = 1; j + (1 << i) - 1 <= n; ++j)
                st[i][j] = min(st[i-1][j], st[i-1][j + (1 << (i - 1))]);
    }
    int query(uint32_t l, uint32_t r)
    {
        int s = bit_width(r - l + 1)-1;
        return min(st[s][l], st[s][r - (1 << s) + 1]);
    }
}
```
# 加减1RMQ
>此算法主要在空间受限的情况下使用，空间充足时速度不如稀疏表

如果数组 A 相邻元素总是相差 1，可以使用此算法

将数组 A 划分为大小为 K 的块，块内计算最值，并存入数组 B，B 的大小为 $\frac NK$，在数组 B 上构建ST表，时空复杂度为 $O(\frac NK\log_2\frac NK)$

去掉每个块的第一个元素，然后将该元素从块内所有其他元素中减去，那么每个块可以由一个长度为 K−1 的序列来标识，不同序列个数 $2^{K-1}$

对每个序列暴力处理所有区间最值，时间复杂度 $O(\min(\frac NK,2^{K-1})\frac{K(K-1)}{2})$

总复杂度为 $O(\frac NK\log_2\frac NK+\min(\frac NK,2^{K-1})\frac{K(K-1)}{2})$

考虑到计算机的物理特性，K一般取16，此时总复杂度约为 $$\frac{N \log_2 N}{16} - \frac{N}{4}+\min(\frac NK,32768)*120$$，再考虑到竞争性编程中的N的范围，上式近似为 $O(N)$
```cpp
const uint32_t N=5e5+3,K=16;
namespace PlusMinusOneRMQ
{
    int a[N],st[bit_width(N/K)][N/K];
    uint16_t mask[N/K];
    int8_t inBlock[1<<(K-1)][K][K];
    void init0()//只需执行一次，多测会用到此优化
    {
        for (uint32_t m = 0; m < (1<<(K-1)); ++m)
            for (uint32_t l = 0; l < K; ++l)
            {
                int8_t cur = 0, mi = 0;
                inBlock[m][l][l] = 0;
                for (uint32_t r = l + 1; r < K; ++r)
                {
                    cur += (m & (1 << (r - 1))) ? 1 : -1;
                    mi = min(mi, cur);
                    inBlock[m][l][r] = mi;
                }
            }
    }
    void init(uint32_t n)
    {
        uint32_t block=n/K;
        for(uint32_t i=0,cur=1;i<block;++i,++cur)
        {
            uint16_t mas=0;
            for(uint32_t j=0,R=i*K+K;cur<R;++j,++cur)
                if(a[cur+1]>a[cur])
                    mas|=(1<<j);
            mask[i]=mas;
        }
        for(uint32_t i=0;i<block;++i)
            st[0][i]=*min_element(a+i*K,a+i*K+K);
        for (uint32_t i = 1; i < bit_width(block); ++i)
            for (uint32_t j = 0; j + (1 << i) - 1 < block; ++j)
                st[i][j] = min(st[i-1][j], st[i-1][j + (1 << (i - 1))]);
    }
    int query(uint32_t l, uint32_t r)
    {
        uint32_t bl=l/K,br=r/K;
        if(bl==br)
            return a[l]+inBlock[mask[bl]][l%K][r%K];
        int res=min(a[l]+inBlock[mask[bl]][l%K][K-1],
            a[br*K]+inBlock[mask[br]][0][r%K]);
        if(bl+1==br)
            return res;
        uint32_t s = bit_width(br - bl - 1)-1;
        return min({res,st[s][bl+1], st[s][br - (1 << s)]});
    }
}
```
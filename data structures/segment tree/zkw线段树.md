# 张昆玮线段树
只支持堆式编码和标记永久化

[测试题目1](https://www.luogu.com.cn/problem/P3372)，[递归线段树](https://www.luogu.com.cn/record/281354854)484ms，[张昆玮线段树](https://www.luogu.com.cn/record/281375931)267ms

[测试题目2](https://judge.yosupo.jp/problem/range_affine_range_sum)，[堆式编码](https://judge.yosupo.jp/submission/378191)444ms，[张昆玮线段树](https://judge.yosupo.jp/submission/378990)229ms
```cpp
constexpr bool isCommutative=true;
struct zkwSegmentTree
{
    struct node
    {
        uint32_t mul, add, sum;
    }st[bit_ceil(N+2)*2];
    uint32_t leaf;
    void Build(uint32_t n)
    {
        //+2是查询需要为左右各预留一个点
        leaf=bit_ceil(n+2);
        for(uint32_t i=1;i<=n;++i)
            st[leaf+i]={1,0,A[i]};
        for(uint32_t i=leaf-1;i;--i)
            st[i]={1,0,st[i<<1].sum+st[i<<1|1].sum};
    }
    void apply(uint32_t id, uint32_t mul, uint32_t add, uint32_t len)
    {
        st[id].mul = st[id].mul * mul;
        st[id].add = st[id].add * mul + add;
        st[id].sum = st[id].sum * mul + len * add;
    }
    void pushdown(uint32_t id)
    {
        for (int i = bit_width(id) - 2; i >= 0; --i)
        {
            apply(id >> i, st[id >> i >> 1].mul, st[id >> i >> 1].add, 1 << i);
            apply((id >> i) ^ 1, st[id >> i >> 1].mul, st[id >> i >> 1].add, 1 << i);
            st[id >> i >> 1].mul = 1;
            st[id >> i >> 1].add = 0;
        }
    }
    void pushup(uint32_t id)
    {
        st[id].sum = addmod(st[id << 1].sum + st[id << 1 | 1].sum);
    }
    void update(uint32_t l,uint32_t r,uint64_t val)
    {
        l += leaf - 1,r += leaf + 1;
        if constexpr(isCommutative)
            pushdown(l),pushdown(r);
        uint32_t fir = min(countr_one(l), countr_zero(r));
        l >>= fir,r >>= fir;
        for(uint32_t i=fir;l^r^1;++i)
        {
            if(~l&1)
                apply(l ^ 1, mul, add, 1u << i);
            if(r&1)
                apply(r ^ 1, mul, add, 1u << i);
            l>>=1,r>>=1;
            pushup(l),pushup(r);
        }
        for(l>>=1;l;l>>=1)
            pushup(l);
    }
    uint64_t query(uint32_t l,uint32_t r)
    {
        l += leaf - 1,r += leaf + 1;
        const uint32_t l0=~l,r0=r,len=r-l-1;
        uint64_t resL=0,resR=0;
        for(uint32_t i=0;l^r^1;++i)
        {
            if(~l&1)
                resL+=st[l^1].sum;
            if(r&1)
                resR+=st[r^1].sum;
            l>>=1,r>>=1;
            resL = st[l].mul * resL + st[l].add * (l0 & ((1ull << i + 1) - 1));
            resR = st[r].mul * resR + st[r].add * (r0 & ((1ull << i + 1) - 1));
        }
        uint64_t res = resL + resR;
        for(l>>=1;l;l>>=1)
            res = st[l].mul * res + st[l].add * len;
        return res;
    }
};
```
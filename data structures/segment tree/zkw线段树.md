# 张昆玮线段树
只支持标记永久化

[测试题目](https://www.luogu.com.cn/problem/P3372)，[递归线段树](https://www.luogu.com.cn/record/281354854)484ms，[张昆玮线段树](https://www.luogu.com.cn/record/281375931)267ms
```cpp
struct zkwSegmentTree
{
    struct node
    {
        uint64_t sum,lz;
    }st[bit_ceil(N+2)*2];
    uint32_t leaf;
    void Build(uint32_t n)
    {
        //+2是查询需要为左右各预留一个点
        leaf=bit_ceil(n+2);
        for(uint32_t i=1;i<=n;++i)
            st[leaf+i]={A[i],0};
        for(uint32_t i=leaf-1;i;--i)
            st[i]={st[i<<1].sum+st[i<<1|1].sum,0};
    }
    void update(uint32_t l,uint32_t r,uint64_t val)
    {
        l=leaf+l-1;
        r=leaf+r+1;
        const uint32_t l0=l,r0=r;
        uint32_t i=0;
        for(;l^r^1;l>>=1,r>>=1,++i)
        {
            st[l].sum+=val*((~l0)&((1ull<<i)-1));
            st[r].sum+=val*(r0&((1ull<<i)-1));
            if(~l&1)
            {
                st[l^1].sum+=val*(1ull<<i);
                st[l^1].lz+=val;
            }
            if(r&1)
            {
                st[r^1].sum+=val*(1ull<<i);
                st[r^1].lz+=val;
            }
        }
        st[l].sum+=val*((~l0)&((1ull<<i)-1));
        st[r].sum+=val*(r0&((1ull<<i)-1));
        for(l>>=1;l;l>>=1)
            st[l].sum+=val*(r0-l0-1);
    }
    uint64_t query(uint32_t l,uint32_t r)
    {
        l=leaf+l-1;
        r=leaf+r+1;
        const uint32_t l0=l,r0=r;
        uint32_t i=0;
        uint64_t res=0;
        for(;l^r^1;l>>=1,r>>=1,++i)
        {
            res+=st[l].lz*((~l0)&((1ull<<i)-1))+st[r].lz*(r0&((1ull<<i)-1));
            if(~l&1)
                res+=st[l^1].sum;
            if(r&1)
                res+=st[r^1].sum;
        }
        res+=st[l].lz*((~l0)&((1ull<<i)-1))+st[r].lz*(r0&((1ull<<i)-1));
        for(l>>=1;l;l>>=1)
            res+=st[l].lz*(r0-l0-1);
        return res;
    }
};
```
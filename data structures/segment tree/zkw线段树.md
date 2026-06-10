# 张昆玮线段树
只支持标记永久化

[测试题目](https://www.luogu.com.cn/problem/P3372)，[递归线段树](https://www.luogu.com.cn/record/281354854)484ms，[张昆玮线段树](https://www.luogu.com.cn/record/281367814)274ms
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
        uint32_t lNum=0,rNum=0;
        l=leaf+l-1;
        r=leaf+r+1;
        for(uint32_t len=1;l^r^1;l>>=1,r>>=1,len<<=1)
        {
            st[l].sum+=val*lNum;
            st[r].sum+=val*rNum;
            if(~l&1)
            {
                st[l^1].sum+=val*len;
                st[l^1].lz+=val;
                lNum+=len;
            }
            if(r&1)
            {
                st[r^1].sum+=val*len;
                st[r^1].lz+=val;
                rNum+=len;
            }
        }
        st[l].sum+=val*lNum;
        st[r].sum+=val*rNum;
        l>>=1;
        lNum+=rNum;
        for(;l;l>>=1)
            st[l].sum+=val*lNum;
    }
    uint64_t query(uint32_t l,uint32_t r)
    {
        uint32_t lNum=0,rNum=0;
        uint64_t res=0;
        l=leaf+l-1;
        r=leaf+r+1;
        for(uint32_t len=1;l^r^1;l>>=1,r>>=1,len<<=1)
        {
            res+=st[l].lz*lNum+st[r].lz*rNum;
            if(~l&1)
            {
                res+=st[l^1].sum;
                lNum+=len;
            }
            if(r&1)
            {
                res+=st[r^1].sum;
                rNum+=len;
            }
        }
        res+=st[l].lz*lNum+st[r].lz*rNum;
        l>>=1;
        lNum+=rNum;
        for(;l;l>>=1)
            res+=st[l].lz*lNum;
        return res;
    }
};
```
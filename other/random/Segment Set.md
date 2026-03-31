# Segment Set
## 别名
珂朵莉树(Chtholly Tree)，老司机树(Old Driver Tree)
## 简介
在长度 n 的数组上操作，如果有一种操作是把区间内每一个元素修改为相同信息，且区间左右端点是在 [1,n] 均匀随机抽取的，则经过 m 次这种操作，连续相同信息段的段数的期望是 $O(\frac nm+\log\min(n,m))$，当 n 和 m 同阶，m 次操作过程中连续相同信息段的段数的期望平均值为 $O(\log n)$

>具体复杂度分析见[Segment Set 的复杂度分析](https://zhuanlan.zhihu.com/p/102786071)

如果把连续相同信息段压缩成一个节点，存储“左右端点，信息”，就可以以优秀复杂度支持其他操作

区间写操作满足以下两点性质则可以支持：  
1. 不会显著增加连续相同信息段的段数
2. 复杂度和包含的节点数有关，和区间长度无关

区间读操作满足“复杂度和包含的节点数有关，和区间长度无关”则可以支持
## 区间写的例子
区间加法，段数可能+0，+1，+2，不会显著增加段数
## 区间读的例子
区间和，区间第k大值

---
```cpp
namespace SegmentSet
{
    using PositionType=int;
    using ValueType=unsigned long long;
    struct Segment
    {
        PositionType l, r;
        mutable ValueType v;//l不重复，但是可能有写操作需要改v，删除再重新插入性能会差，或者用map性能会差，set不允许直接改键，所以加mutable
        Segment(PositionType _l,PositionType _r,ValueType _v):l(_l),r(_r),v(_v){}
        bool operator<(const Segment &o) const { return l < o.l; }
    };
    std::set<Segment> se;
    void init(int n)
    {
        for(int i=1;i<=n;++i)
            se.emplace_hint(se.end(),i,i,a[i]);
        se.emplace_hint(se.end(),n+1,n+1,0);
    }
    auto split(PositionType pos)
    {
        auto it = se.lower_bound(Segment(pos,0,0));
        if (it->l == pos)
            return it;
        --it;
        PositionType l = it->l, r = it->r;
        ValueType v = it->v;
        return se.emplace_hint(std::next(se.emplace_hint(se.erase(it),l,pos-1,v)),pos,r,v);
    }
    void assign(PositionType l, PositionType r, ValueType v)
    {
        auto end = split(r + 1);//必须先split(r+1)，再split(l)
        se.emplace_hint(se.erase(split(l), end),l, r, v);
    }
    void RangeWrite(PositionType l, PositionType r)
    {
        auto end = split(r + 1);
        for (auto it = split(l); it != end; ++it)
        {
            //写[it->l,it->r]
        }
    }
    void RangeRead(PositionType l, PositionType r)
    {
        auto it=--se.upper_bound(Segment(l,0,0));
        if(it->r >= r)
        {
            //读[l,r]
            return;
        }
        {
            //读[l,it->r]
        }
        while ((++it)->r <= r)
        {
            //读[it->l,it->r]
        }
        if(it->l<=r)
        {
            //读[it->l,r]
        }
    }
}
```

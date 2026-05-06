#! https://zhuanlan.zhihu.com/p/557879685
# 莫队
如果可以$O(1)$从[l,r]的答案转移到[l-1,r]、[l+1,r]、[l,r-1]、[l,r+1]的答案，而且离线查询，考虑莫队

奇偶化排序（常数优化），左端点所在块是第奇数块，按右端点降序，否则右端点升序

原理是处理第0块询问时，右指针向右移动；处理第1块询问时，右指针向左移动，处理第2块询问时，右指针向右移动······

这样奇偶块降升序能减少右指针移动次数

设序列长度 n，询问次数 m，块长 $S$，$O(\frac{n^2}S+mS)$，当块长取 $\frac n{\sqrt m}$ 最优，此时复杂度为 $O(n\sqrt m)$
```cpp
const unsigned int sq=N/sqrt(Q);
struct query { uint32_t l, r, id; } q[Q];
void solve(int T)
{
    for (int i = 0; i < T; ++i)
    {
        cin>>q[i].l>>q[i].r;
        q[i].id = i;
    }
    auto qSpan = span(q,T);
    ranges::sort(qSpan,[sq](const auto& x,const auto& y){
        if(x.l / sq != y.l / sq)
            return x.l < y.l;
        return (x.l / sq & 1) ? (x.r > y.r) : (x.r < y.r);
    });
    l=1,r=0;
    for (const auto& [ql,qr,id]:qSpan)
    {
        while (l > ql)
            add(--l);
        while (r < qr)
            add(++r);
        while (l < ql)
            del(l++);
        while (r > qr)
            del(r--);
        ans[id] = res;
    }
}
```
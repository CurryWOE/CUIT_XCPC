#! https://zhuanlan.zhihu.com/p/557879685
# 莫队
如果可以$O(1)$从[l,r]的答案转移到[l-1,r]、[l+1,r]、[l,r-1]、[l,r+1]的答案，而且离线查询，考虑莫队

奇偶化排序（常数优化），左端点所在块是第奇数块，按右端点降序，否则右端点升序

原理是处理第0块询问时，右指针向右移动；处理第1块询问时，右指针向左移动，处理第2块询问时，右指针向右移动······

这样奇偶块降升序能减少右指针移动次数

设块长 $S$，$O(\frac{n^2}S+mS)$，当块长取 $\frac n{\sqrt m}$ 最优，此时复杂度为 $O(n\sqrt m)$
```cpp
int sq;
struct query
{
    int l, r, id;
    bool operator<(const query &o) const
    {
        if (l / sq != o.l / sq)
            return l < o.l;
        if (l / sq & 1)
            return r > o.r;
        return r < o.r;
    }
}Q[MAXQ];
int main()
{
    cin>>q;
    for (int i = 0; i < q; ++i)
    {
        cin>>Q[i].l>>Q[i].r;
        Q[i].id = i;
    }
    sq=sqrt(n);
    sort(Q, Q + q);
    l=1,r=0;
    for (int i = 0; i < q; ++i)
    {
        while (l > Q[i].l)
            add(--l);
        while (r < Q[i].r)
            add(++r);
        while (l < Q[i].l)
            del(l++);
        while (r > Q[i].r)
            del(r--);
        ans[Q[i].id] = res;
    }
}
```
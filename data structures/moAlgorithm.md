#! https://zhuanlan.zhihu.com/p/557879685
# 莫队
如果可以$O(1)$从[l,r]的答案转移到[l-1,r]、[l+1,r]、[l,r-1]、[l,r+1]的答案，而且离线查询，考虑莫队

# 算法流程
1. 记录查询（询问的输入以及询问的序号）
2. 排序
3. 逐个询问，并转移区间

# 区间转移
往区间里添1个数的转移，或往区间里删1个数的转移

一个区间移动到另一个区间的转移
```cpp
while (l > Q[i].l)
    add(--l);
while (l < Q[i].l)
    del(l++);
while (r < Q[i].r)
    add(++r);
while (r > Q[i].r)
    del(r--);
```

add和del由具体题目决定

# 排序
bel[i]表示下标为i的数据在哪一块，$\sqrt n$为一块

以bel[l]为第一关键词,bel[r]为第二关键词

## 奇偶化排序（常数优化）
如果bel[l]是奇数，r升序，否则r降序

```cpp
struct query
{
    int l, r, id;
    bool operator<(const query &o) const
    {
        if (l / sq != o.l / sq) 
            return l < o.l;
        if (l / sq & 1)
            return r < o.r;
        return r > o.r;
    }
}Q[MAXQ];

for (int i = 0; i < q; ++i)
{
    cin>>Q[i].l>>Q[i].r;
    Q[i].id = i;
}
sq=sqrt(n);
sort(Q, Q + q);
l=1;
r=0;
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
```
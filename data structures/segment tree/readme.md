# 线段树
# 代码无关的前置知识
幺半群是一个代数结构，由一个集合 $M$ 和一个二元运算 $\cdot$ 组成，满足以下三条公理：

1. 封闭性，$\forall a, b \in M$，有 $a \cdot b \in M$
2. 结合律，$\forall a, b, c \in M$，有 $(a \cdot b) \cdot c = a \cdot (b \cdot c)$
3. 单位元，$\exist e \in M$，使得 $\forall a \in M$，有 $e \cdot a = a \cdot e = a$
# 最朴素的线段树
当信息满足幺半群，即可用线段树维护。下面给出，单点修改，区间查询，堆式建树，递归式，的例程
## 实现细节
1. array of struct 比 struct of array 略快一点
2. 实时计算区间的l，r，比存到线段树节点里去读，快
3. 求mid用右移比除2，快。因为编译器不会把有符号除2的幂优化为右移，而是包含判断负数，负数加偏差，再右移
4. 原始数组使用0-indexed或1-indexed均可，本仓库的线段树均为1-indexed
```cpp
const uint32_t N = 1e5 + 3;
int64_t a[N];
struct SegmentTree
{
    struct node { int64_t sum; } st[N << 2];
    void build(uint32_t id, uint32_t l, uint32_t r)
    {
        if (l == r)
        {
            st[id] = {a[l]};
            return;
        }
        auto mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        st[id].sum = st[id << 1].sum + st[id << 1 | 1].sum;
    }
    void update(uint32_t id, uint32_t segl, uint32_t segr, uint32_t pos, int64_t val)
    {
        if (segl == segr)
        {
            st[id].sum += val;
            return;
        }
        auto mid = (segl + segr) >> 1;
        if (pos <= mid)
            update(id << 1, segl, mid, pos, val);
        else
            update(id << 1 | 1, mid + 1, segr, pos, val);
        st[id].sum = st[id << 1].sum + st[id << 1 | 1].sum;
    }
    int64_t query(uint32_t id, uint32_t segl, uint32_t segr, uint32_t L, uint32_t R)
    {
        if (L <= segl && segr <= R)
            return st[id].sum;
        auto mid = (segl + segr) >> 1;
        int64_t res = 0;
        if (L <= mid)
            res += query(id << 1, segl, mid, L, R);
        if (R > mid)
            res += query(id << 1 | 1, mid + 1, segr, L, R);
        return res;
    }
} st;
st.build(1,1,n);
st.update(1,1,n,pos,val);
st.query(1,1,n,l,r);
```
# 区间修改
懒标记和标记永久化两种方法各擅胜场，具体地说：

平衡树这样点的相对位置会改变的，只能用懒标记，保证碰到的节点，其信息是最新的

标记永久化必须满足分配律，设修改操作为 $f$，聚合值 $a,b$，分配律为 $f(a\cdot b)=f(a)\cdot f(b)$，比如 $max(a+b,c)$ 和 $max(a,c)+max(b,c)$ 就不满足分配律

标记永久化，如果修改不满足交换律，会变慢修改速度，修改复杂度不变，查询速度不变。比如加法乘法混合就不满足交换律。有两种做法“支持”交换律

1. 在修改节点之前，被修改点的祖先的标记，都需要从上到下下推到被修改点。这样做的目的是，从叶子到根，标记的时间戳是递增的，这样聚合信息就不会违反交换律
2. 把X操作变成Z操作，中间遇到的标记都不动，满足Y标记+X操作=Z操作+Y标记，常见的是X操作是一种可逆操作

可持久化这样一个点有多个父亲的，如果用懒标记，下传标记如果不开新节点会影响前面的树，开新节点容易卡空间，推荐用标记永久化

其他情况用两个都行

标记永久化cache friendly一点，[测试题目](https://www.luogu.com.cn/problem/P3372)，[懒标记](https://www.luogu.com.cn/record/281314416)518ms，[标记永久化](https://www.luogu.com.cn/record/281354854)484ms
## 建模小技巧
对于区间覆盖的问题，线段覆盖直接原值乘2后离散化，点覆盖需要离散化之后，相邻点之间插入一个点，再离散化
# 数据存储
静态开点和动态开点两种方法各擅胜场，具体地说：

静态开点：占用空间大，时间快

动态开点：占用空间小，时间慢。

如果需要很多颗线段树，只能用动态开点，记录下每棵树根分配到的下标

要表示的区间很多而有用的区间少，只能用动态开点
# 权值线段树
朴素版是维护区间信息的，权值线段树是维护值域内数的个数

$[2,3,1,2,2,3]$ 这个原序列，转化为值域序列就是 $[1,3,2]$ ，表示1的个数有1个，2的个数有3个，3的个数有2个

权值线段树的操作和朴素版几乎一致，只是维护信息不同。

通常题目的值域会很大，可以通过离散化或者动态开点解决

01字典树和强制值域为 $[0,2^k-1]$ 的动态开点权值线段树，获得的树形结构是一模一样的，但是由于写法不同，01字典树常数小一点，根据luoguP1908 逆序对，约快 9%，[提交1](https://www.luogu.com.cn/record/274194118)，[提交2](https://www.luogu.com.cn/record/274238117)，如果01字典树要处理负值域，可以加偏移

下面给出动态开点，单点修改，权值线段树的例程
## 实现细节
1. 如果区间[segl,segr]包含负数时不能用除法，因为segl=-2,segr=-1，(-3)/2=-1，按照[segl,mid],[mid+1,segr]的写法，会死循环，而((-3)>>1)=-2，就正常划分成两个区间
2. 当值域特别大的时候很容易写出溢出代码，正确写法是 std::midpoint(l,r)。CPP20之前有符号整数的右移行为是实现定义的，尽管主流编译器都实现为算术右移，没有任何一种“理论上绝对安全且可移植”的方法能同时满足“无溢出”和“等价于 (l+r)>>1 的向下取整行为”
```cpp
struct SegmentTree
{
    struct node
    {
        uint32_t l,r,sum;
    }st[N];
    uint32_t tot,root;
    void update(uint32_t &id, int l, int r,int val)
    {
        if(!id)
            id=++tot;
        ++st[id].sum;
        if(l==r)
            return;
        auto mid = midpoint(l,r);
        if (val <= mid)
            update(st[id].l,l,mid,val);
        else
            update(st[id].r,mid+1,r,val);
    }
    uint32_t query(uint32_t id,int segl,int segr,int l, int r)
    {
        if (l <= segl && segr <= r)
            return st[id].sum;
        auto mid = midpoint(segl,segr);
        uint32_t res=0;
        if (l <= mid)
            res+=query(st[id].l,segl,mid,l,r);
        if (r > mid)
            res+=query(st[id].r,mid+1,segr,l,r);
        return res;
    }
    void init()
    {
        root=0;
        for(;tot;--tot)
            st[tot]={0,0,0};
    }
}st;
st.init();
st.update(st.root,MinVal,MaxVal,val);
st.query(st.root,MinVal,MaxVal,l,r);
```
# 张昆玮线段树
对于可以堆式编码和标记永久化的题目，可以把递归线段树换成张昆玮线段树，时间能快50%左右

但是如果两个条件有一个不满足，就不能使用张昆玮线段树
# 进阶技巧
1. 线段树上二分
2. 可持久化
3. 主席树
4. 扫描线
5. 势能线段树
6. 线段树优化建图
7. 李超树
8. 线段树合并
9. 猫树
10. 线段树分裂
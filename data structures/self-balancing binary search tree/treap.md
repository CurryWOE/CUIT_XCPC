# Treap
# RotateTreap
每个新元素插入时给定一个随机的优先级，插入或删除时通过旋转保持优先级是小顶堆

如果卡空间就在remove回收节点
```cpp
const uint32_t N = 1e5 + 3;
namespace RotateTreap
{
    uint32_t xorshift32_state = 1;
    uint32_t xorshift32()
    {
        uint32_t x = xorshift32_state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return xorshift32_state = x;
    }
    struct Node
    {
        int element;
        uint32_t priority, elementCount, subtreeElementCount, son[2];
    } tr[N];
    uint32_t vertexCount, root;
    void updateSize(uint32_t id)
    {
        auto &cur = tr[id];
        cur.subtreeElementCount = cur.elementCount + tr[cur.son[0]].subtreeElementCount + tr[cur.son[1]].subtreeElementCount;
    }
    void rotate(uint32_t &id, bool dir)
    {
        auto son = tr[id].son[dir ^ 1];
        tr[id].son[dir ^ 1] = tr[son].son[dir];
        tr[son].son[dir] = id;
        updateSize(id);
        updateSize(son);
        id = son;
    }
    void insert(uint32_t &id, int val)
    {
        if (!id)
        {
            id = ++vertexCount;
            tr[id].element=val;
            tr[id].priority=xorshift32();
            tr[id].elementCount=tr[id].subtreeElementCount=1;
            tr[id].son[0]=tr[id].son[1]=0;
            return;
        }
        auto &cur = tr[id];
        if (val == cur.element)
            ++cur.elementCount;
        else
        {
            bool dir = val > cur.element;
            insert(cur.son[dir], val);
            if (tr[cur.son[dir]].priority > cur.priority)
                rotate(id, dir ^ 1);
        }
        updateSize(id);
    }
    void remove(uint32_t &id, int val)
    {
        auto &cur = tr[id];
        if (val == cur.element)
        {
            if (cur.elementCount > 1)
            {
                --cur.elementCount;
                updateSize(id);
                return;
            }
            if (!cur.son[0] || !cur.son[1])
            {
                id = cur.son[0] | cur.son[1];
                return;
            }
            bool dir = tr[cur.son[0]].priority > tr[cur.son[1]].priority;
            rotate(id, dir);
            remove(tr[id].son[dir], val);
        }
        else
            remove(cur.son[val > cur.element], val);
        updateSize(id);
    }
    uint32_t rank(int val)
    {
        for (uint32_t res = 1, x = root; true;)
        {
            if (!x)
                return res;
            auto &cur = tr[x];
            if (cur.element == val)
                return res + tr[cur.son[0]].subtreeElementCount;
            else if(cur.element > val)
                x = cur.son[0];
            else
            {
                res += tr[cur.son[0]].subtreeElementCount + cur.elementCount;
                x = cur.son[1];
            }
        }
    }
    int kth(uint32_t k)
    {
        for (auto x = root; true;)
        {
            auto l = tr[x].son[0];
            if (k <= tr[l].subtreeElementCount)
                x = l;
            else if (k <= tr[l].subtreeElementCount + tr[x].elementCount)
                return tr[x].element;
            else
            {
                k -= tr[l].subtreeElementCount + tr[x].elementCount;
                x = tr[x].son[1];
            }
        }
    }
    int prevElement(int val)
    {
        auto res = numeric_limits<int>::min();
        for (auto x = root; x;)
        {
            if (tr[x].element < val)
            {
                res = tr[x].element;
                x = tr[x].son[1];
            }
            else
                x = tr[x].son[0];
        }
        return res;
    }
    int nextElement(int val)
    {
        auto res = numeric_limits<int>::max();
        for (auto x = root; x;)
        {
            if (tr[x].element > val)
            {
                res = tr[x].element;
                x = tr[x].son[0];
            }
            else
                x = tr[x].son[1];
        }
        return res;
    }
}
```
# SplitMergeTreap
分裂：将一颗树分裂成两颗，左树所有元素小于等于val，右树所有元素大于val，回溯时确定左右儿子

合并：将两颗树合并成一颗，左树最大元素小于右树最小元素，新树的根是左树右树优先级小的根，保持优先级是小顶堆，回溯时确定左右儿子

插入：树分裂成两颗，新点和左树合并，再和右树合并

删除：树分裂成三颗，左树小于val，中树等于val，右树大于val，中树的左右子树合并，再和左树合并，再和右树合并
```cpp
const uint32_t N = 1e5 + 3;
namespace SplitMergeTreap
{
    uint32_t xorshift32_state = 1;
    uint32_t xorshift32()
    {
        uint32_t x = xorshift32_state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return xorshift32_state = x;
    }
    struct Node
    {
        int element;
        uint32_t priority, subtreeSize, l, r;
    } tr[N];
    uint32_t vertexCount, root;
    inline void updateSize(uint32_t id)
    {
        auto &cur = tr[id];
        cur.subtreeSize = 1 + tr[cur.l].subtreeSize + tr[cur.r].subtreeSize;
    }
    void splitByKey(uint32_t id, uint32_t val, uint32_t &l, uint32_t &r)
    {
        if (!id)
        {
            l = r = 0;
            return;
        }
        if (tr[id].element <= val)
        {
            l = id;
            splitByKey(tr[id].r, val, tr[id].r, r);
        }
        else
        {
            r = id;
            splitByKey(tr[id].l, val, l, tr[id].l);
        }
        updateSize(id);
    }
    uint32_t merge(uint32_t l, uint32_t r)
    {
        if (!l || !r)
            return l | r;
        if (tr[l].priority < tr[r].priority)
        {
            tr[l].r = merge(tr[l].r, r);
            updateSize(l);
            return l;
        }
        tr[r].l = merge(l, tr[r].l);
        updateSize(r);
        return r;
    }
    void insert(int val)
    {
        uint32_t l, r;
        split(root, val, l, r);
        auto id = ++vertexCount;
        tr[id].element=val;
        tr[id].priority=xorshift32();
        tr[id].subtreeSize=1;
        tr[id].l=tr[id].r=0;
        root=merge(merge(l,id),r);
    }
    void remove(int val)
    {
        uint32_t l, m, r;
        split(root, val - 1, l, r);
        split(r, val, m, r);
        root=merge(merge(l,merge(tr[m].l,tr[m].r)),r);
    }
    uint32_t rank(int val)
    {
        uint32_t res = 1;
        for (uint32_t x = root; x;)
        {
            auto &cur = tr[x];
            if(cur.element >= val)
                x = cur.l;
            else
            {
                res += tr[cur.l].subtreeSize + 1;
                x = cur.r;
            }
        }
        return res;
    }
    int kth(uint32_t k)
    {
        for (auto x = root; true;)
        {
            auto l = tr[x].l;
            if (k <= tr[l].subtreeSize)
                x = l;
            else if (k == tr[l].subtreeSize + 1)
                return tr[x].element;
            else
            {
                k -= tr[l].subtreeSize + 1;
                x = tr[x].r;
            }
        }
    }
    int prevElement(int val)
    {
        auto res = numeric_limits<int>::min();
        for (auto x = root; x;)
        {
            if (tr[x].element < val)
            {
                res = tr[x].element;
                x = tr[x].r;
            }
            else
                x = tr[x].l;
        }
        return res;
    }
    int nextElement(int val)
    {
        auto res = numeric_limits<int>::max();
        for (auto x = root; x;)
        {
            if (tr[x].element > val)
            {
                res = tr[x].element;
                x = tr[x].l;
            }
            else
                x = tr[x].r;
        }
        return res;
    }
}
```
## 区间操作SplitMergeTreap
把数组下标作为键，优先级作为值，treap就是笛卡尔树，因此可以按照笛卡尔树方式建treap
```cpp
const uint32_t N = 1e5 + 3;
int a[N];//1-index
namespace SplitMergeTreap
{
    uint32_t xorshift32_state = 1;
    uint32_t xorshift32()
    {
        uint32_t x = xorshift32_state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return xorshift32_state = x;
    }
    struct Node
    {
        uint32_t priority, subtreeSize, l, r;
    } tr[N];
    uint32_t vertexCount, root;
    inline void updateSize(uint32_t id)
    {
        auto &cur = tr[id];
        cur.subtreeSize = 1 + tr[cur.l].subtreeSize + tr[cur.r].subtreeSize;
    }
    void splitByRank(uint32_t id, uint32_t k, uint32_t &l, uint32_t &r)
    {
        if (!id)
        {
            l = r = 0;
            return;
        }
        if (k <= tr[tr[id].l].subtreeSize)
        {
            splitByRank(tr[id].l, k, l, tr[id].l);
            r = id;
            tr[r].subtreeSize -= k;
        }
        else
        {
            splitByRank(tr[id].r, k - tr[tr[id].l].subtreeSize - 1, tr[id].r, r);
            l = id;
            tr[l].subtreeSize = k;
        }
    }
    uint32_t merge(uint32_t l, uint32_t r)
    {
        if (!l || !r)
            return l | r;
        if (tr[l].priority < tr[r].priority)
        {
            tr[l].r = merge(tr[l].r, r);
            updateSize(l);
            return l;
        }
        tr[r].l = merge(l, tr[r].l);
        updateSize(r);
        return r;
    }
    void build(int n)
    {
        vector<uint32_t> stk;
        stk.reserve(n);
        for (uint32_t i = 1; i <= n; ++i)
        {
            tr[i] = {xorshift32(), 1, 0, 0};
            uint32_t last = 0;
            for (; !stk.empty() && tr[stk.back()].priority > tr[i].priority; stk.pop_back())
                last = stk.back();
            tr[i].l = last;
            if (!stk.empty())
                tr[stk.back()].r = i;
            stk.push_back(i);
        }
        root = stk.front();
        stk.resize(1);
        vector<uint32_t> ord;
        ord.reserve(n);
        while (!stk.empty())
        {
            uint32_t u = stk.back();
            stk.pop_back();
            ord.push_back(u);
            if (tr[u].l)
                stk.push_back(tr[u].l);
            if (tr[u].r)
                stk.push_back(tr[u].r);
        }
        for (auto u : ord | ranges::views::reverse)
            tr[u].subtreeSize = tr[tr[u].l].subtreeSize + tr[tr[u].r].subtreeSize + 1;
    }
}
```
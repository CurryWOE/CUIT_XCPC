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
        uint32_t priority, subtreeSize, son[2];
    } tr[N];
    uint32_t vertexCount, root;
    inline void updateSize(uint32_t id)
    {
        auto &cur = tr[id];
        cur.subtreeSize = 1 + tr[cur.son[0]].subtreeSize + tr[cur.son[1]].subtreeSize;
    }
    void split(uint32_t id,int val,uint32_t& l,uint32_t& r)
    {
        if(!id)
        {
            l=r=0;
            return;
        }
        if(tr[id].element<=val)
        {
            l=id;
            split(tr[id].son[1],val,tr[id].son[1],r);
        }
        else
        {
            r=id;
            split(tr[id].son[0],val,l,tr[id].son[0]);
        }
        updateSize(id);
    }
    uint32_t merge(uint32_t l,uint32_t r)
    {
        if(!l || !r)
            return l|r;
        if(tr[l].priority<tr[r].priority)
        {
            tr[l].son[1]=merge(tr[l].son[1],r);
            updateSize(l);
            return l;
        }
        tr[r].son[0]=merge(l,tr[r].son[0]);
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
        tr[id].son[0]=tr[id].son[1]=0;
        root=merge(merge(l,id),r);
    }
    void remove(int val)
    {
        uint32_t l, m, r;
        split(root, val - 1, l, r);
        split(r, val, m, r);
        root=merge(merge(l,merge(tr[m].son[0],tr[m].son[1])),r);
    }
    uint32_t rank(int val)
    {
        uint32_t res = 1;
        for (uint32_t x = root; x;)
        {
            auto &cur = tr[x];
            if(cur.element >= val)
                x = cur.son[0];
            else
            {
                res += tr[cur.son[0]].subtreeSize + 1;
                x = cur.son[1];
            }
        }
        return res;
    }
    int kth(uint32_t k)
    {
        for (auto x = root; true;)
        {
            auto l = tr[x].son[0];
            if (k <= tr[l].subtreeSize)
                x = l;
            else if (k == tr[l].subtreeSize + 1)
                return tr[x].element;
            else
            {
                k -= tr[l].subtreeSize + 1;
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
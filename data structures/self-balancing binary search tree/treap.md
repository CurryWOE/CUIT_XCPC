# Treap
每个新元素插入时给定一个随机的优先级，插入或删除时通过旋转保持优先级是小顶堆

如果卡空间就在remove回收节点
```cpp
const uint32_t N = 1e5 + 3;
namespace Treap
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
        if (!id)
            return;
        auto &cur = tr[id];
        cur.subtreeElementCount = cur.elementCount + tr[cur.son[0]].subtreeElementCount + tr[cur.son[1]].subtreeElementCount;
    }
    void rotate(uint32_t &id, uint32_t dir)
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
            uint32_t dir = val > cur.element;
            insert(cur.son[dir], val);
            if (tr[cur.son[dir]].priority > cur.priority)
                rotate(id, dir ^ 1);
        }
        updateSize(id);
    }
    void remove(uint32_t &id, int val)
    {
        if (!id)
            return;
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
            int dir = tr[cur.son[0]].priority > tr[cur.son[1]].priority;
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
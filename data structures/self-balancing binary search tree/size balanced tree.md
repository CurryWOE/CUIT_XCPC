# Size Balanced Tree
任意节点的子树大小不小于其兄弟节点的所有子节点的子树大小

通过旋转，把过大的子树向根的方向提升
```cpp
const uint32_t N = 1e5 + 3;
namespace SizeBalancedTree
{
    struct Node
    {
        uint32_t son[2], subtreeSize;
        int element;
    } tr[N];
    uint32_t vertexCount, root;
    void rotate(uint32_t &id, bool dir)
    {
        auto son = tr[id].son[dir ^ 1];
        tr[id].son[dir ^ 1] = tr[son].son[dir];
        tr[son].son[dir] = id;
        tr[son].subtreeSize=tr[id].subtreeSize;
        tr[id].subtreeSize=tr[tr[id].son[0]].subtreeSize+tr[tr[id].son[1]].subtreeSize+1;
        id = son;
    }
    void maintain(uint32_t &x, bool dir)
    {
        if (tr[tr[tr[x].son[dir]].son[dir]].subtreeSize > tr[tr[x].son[dir ^ 1]].subtreeSize)
            rotate(x, dir ^ 1);
        else if (tr[tr[tr[x].son[dir]].son[dir ^ 1]].subtreeSize > tr[tr[x].son[dir ^ 1]].subtreeSize)
        {
            rotate(tr[x].son[dir], dir);
            rotate(x, !dir);
        }
        else
            return;
        maintain(tr[x].son[0], 0);
        maintain(tr[x].son[1], 1);
        maintain(x, 1);
        maintain(x, 0);
    }
    void insert(uint32_t &id, int val)
    {
        if (!id)
        {
            id = ++vertexCount;
            tr[id].element = val;
            tr[id].subtreeSize = 1;
            tr[id].son[0] = tr[id].son[1] = 0;
            return;
        }
        ++tr[id].subtreeSize;
        insert(tr[id].son[val >= tr[id].element], val);
        maintain(id, val >= tr[id].element);
    }
    int remove(uint32_t &id, int val)
    {
        --tr[id].subtreeSize;
        int res = 0;
        if (val == tr[id].element || (val < tr[id].element && !tr[id].son[0]) || (val > tr[id].element && !tr[id].son[1]))
        {
            res = tr[id].element;
            if (!tr[id].son[0] || !tr[id].son[1])
                id = tr[id].son[0] | tr[id].son[1];
            else
                tr[id].element = remove(tr[id].son[0], tr[id].element + 1);
            return res;
        }
        return remove(tr[id].son[val >= tr[id].element], val);
    }
    uint32_t rank(int val)
    {
        for (uint32_t res = 1, x = root; true;)
        {
            if (!x)
                return res;
            if (tr[x].element >= val)
                x = tr[x].son[0];
            else
            {
                res += tr[tr[x].son[0]].subtreeSize + 1;
                x = tr[x].son[1];
            }
        }
    }
    int kth(uint32_t k)
    {
        for(uint32_t x=root;true;)
        {
            auto l=tr[x].son[0];
            if(k<=tr[l].subtreeSize)
                x=l;
            else if(k==tr[l].subtreeSize+1)
                return tr[x].element;
            else
            {
                k-=tr[l].subtreeSize+1;
                x=tr[x].son[1];
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
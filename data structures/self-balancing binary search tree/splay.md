# Splay
伸展：通过左旋右旋将点调整到根的位置

插入：普通二叉搜索树一样插入，最后伸展新点

删除：找到该点，伸展该点，如果左右儿子没有两个，其中一个儿子作为新根，如果有两个儿子，左子树里面最大元素的点伸展到根的左儿子的位置，再把根的右子树挂到左儿子的右子树位置

排名，第K小，前驱后驱和其他二叉搜索树类似，最后伸展要找的点
```cpp
const uint32_t N = 1e5 + 3;
namespace Splay
{
    struct Node
    {
        uint32_t father, son[2], subtreeSize;
        int element;
    } tr[N];
    uint32_t vertexCount, root;
    void pushup(uint32_t x)
    {
        tr[x].subtreeSize = tr[tr[x].son[0]].subtreeSize + tr[tr[x].son[1]].subtreeSize + 1;
    }
    void rotate(uint32_t x)
    {
        auto y = tr[x].father;
        if(auto z = tr[y].father; z)
            tr[z].son[tr[z].son[1] == y] = x;
        tr[x].father = tr[y].father;
        uint32_t k = (tr[y].son[1] == x);
        tr[y].son[k] = tr[x].son[k^1];
        if (auto son=tr[x].son[k^1]; son)
            tr[son].father = y;
        tr[x].son[k ^ 1] = y;
        tr[y].father = x;
        pushup(y);
        pushup(x);
    }
    void splay(uint32_t x, uint32_t goal = 0)
    {
        for(;tr[x].father != goal;rotate(x))
            if (auto y=tr[x].father,z=tr[y].father; z != goal)
                rotate((tr[y].son[1] == x) ^ (tr[z].son[1] == y) ? x : y);
        if (goal == 0)
            root = x;
    }
    void insert(int val)
    {
        auto x = root, last = 0u;
        for (; x; x = tr[x].son[val > tr[x].element])
            last = x;
        x = ++vertexCount;
        tr[x].father = last;
        tr[x].son[0] = tr[x].son[1] = 0;
        tr[x].subtreeSize = 1;
        tr[x].element = val;
        if (last)
            tr[last].son[val > tr[last].element] = x;
        splay(x);
    }
    void remove(int val)
    {
        auto x=root;
        while(tr[x].element != val)
        {
            auto son=tr[x].son[val > tr[x].element];
            if(!son)
                break;
            x=son;
        }
        splay(x);
        if (!tr[x].son[0] || !tr[x].son[1])
        {
            root = tr[x].son[0] | tr[x].son[1];
            tr[root].father = 0;
        }
        else
        {
            auto l = tr[x].son[0];
            while (tr[l].son[1])
                l = tr[l].son[1];
            splay(l, x);
            tr[l].son[1] = tr[x].son[1];
            root = tr[tr[x].son[1]].father = l;
            tr[l].father = 0;
            pushup(l);
        }
    }
    uint32_t rank(int val)
    {
        uint32_t res = 1, last = 0;
        for (auto x = root; x;)
        {
            last = x;
            if (val <= tr[x].element)
                x = tr[x].son[0];
            else
            {
                res += tr[tr[x].son[0]].subtreeSize + 1;
                x = tr[x].son[1];
            }
        }
        if (last)
            splay(last);
        return res;
    }
    int kth(uint32_t k)
    {
        for (auto x = root; true;)
        {
            auto lSize = tr[tr[x].son[0]].subtreeSize;
            if (k <= lSize)
                x = tr[x].son[0];
            else if (k == lSize + 1)
            {
                splay(x);
                return tr[x].element;
            }
            else
            {
                k -= lSize + 1;
                x = tr[x].son[1];
            }
        }
    }
    int prevElement(int val)
    {
        uint32_t res = 0;
        for(auto x=root;x;)
        {
            if (tr[x].element < val)
            {
                res = x;
                x = tr[x].son[1];
            }
            else
                x = tr[x].son[0];
        }
        splay(res);
        return tr[res].element;
    }
    int nextElement(int val)
    {
        uint32_t res = 0;
        for(auto x=root;x;)
        {
            if (tr[x].element > val)
            {
                res = x;
                x = tr[x].son[0];
            }
            else
                x = tr[x].son[1];
        }
        splay(res);
        return tr[res].element;
    }
}
```
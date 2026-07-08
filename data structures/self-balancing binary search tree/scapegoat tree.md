# 替罪羊树
像一颗普通二叉搜索树增删查，当增删时发现某个子树极度不平衡（懒惰删除导致有效点太少，左右儿子点数不平衡）、超过了设定的阈值时，中序遍历取出该子树所有仍有效的子节点存在数组里，重构出一颗完美平衡子树挂在原来的位置

平衡因子取0.5-1.0之间，写多靠近0.5，读多靠近1.0

如果卡空间就在inOrderTraversal和remove回收节点

```cpp
const uint32_t N=1e5+3;
namespace ScapegoatTree
{
    constexpr double Alpha=0.8;
    uint32_t treeToArray[N],treeToArrayIndex,vectexCount,root;
    struct node
    {
        uint32_t l,r,allNodeCount,aliveNodeCount;
        int element;
        bool alive;
    }st[N];
    void pushup(uint32_t x)//合并左右子树信息，用来自平衡
    {
        auto l=&st[st[x].l],r=&st[st[x].r];
        st[x].allNodeCount=l->allNodeCount+r->allNodeCount+1;
        st[x].aliveNodeCount=l->aliveNodeCount+r->aliveNodeCount+st[x].alive;
    }
    void inOrderTraversal(uint32_t x)//中序遍历收集所有有效点
    {
        if(!x)
            return;
        inOrderTraversal(st[x].l);
        if(st[x].alive)
            treeToArray[++treeToArrayIndex]=x;
        inOrderTraversal(st[x].r);
    }
    void build(uint32_t& x,uint32_t l,uint32_t r)//重建完美平衡子树
    {
        auto mid=(l+r)>>1;
        x=treeToArray[mid];
        if(l<mid)
            build(st[x].l,l,mid-1);
        else
            st[x].l=0;
        if(r>mid)
            build(st[x].r,mid+1,r);
        else
            st[x].r=0;
        pushup(x);
    }
    void checkAndRebuild(uint32_t& x)//重构不平衡的子树
    {
        if(auto limit=st[x].allNodeCount*Alpha; limit > max(st[st[x].l].allNodeCount,st[st[x].r].allNodeCount) || limit < st[x].aliveNodeCount)
            return;
        treeToArrayIndex=0;
        inOrderTraversal(x);
        build(x,1,treeToArrayIndex);
    }
    void insert(uint32_t& x,int val)
    {
        if(!x)
        {
            x=++vectexCount;
            st[x]={0,0,1,1,val,true};
            return;
        }
        if(st[x].element>val)
            insert(st[x].l,val);
        else
            insert(st[x].r,val);
        pushup(x);
        checkAndRebuild(x);
    }
    bool remove(uint32_t& x,int val)
    {
        if(!x)
            return false;
        bool del=false;
        if(st[x].element>val)
            del=remove(st[x].l,val);
        else if(st[x].element<val)
            del=remove(st[x].r,val);
        else if(st[x].alive)
        {
            st[x].alive=false;
            del=true;
        }
        else
        {
            del=remove(st[x].l,val);
            if(!del)
                del=remove(st[x].r,val);
        }
        pushup(x);
        if(st[x].aliveNodeCount==0)
        {
            x=0;
            return del;
        }
        checkAndRebuild(x);
        return del;
    }
    uint32_t rank(int val)//如果val插入多重集的排名
    {
        for(uint32_t res=1,x=root;true;)
        {
            if(!x)
                return res;
            if(st[x].element>=val)
                x=st[x].l;
            else
            {
                res+=st[st[x].l].aliveNodeCount+st[x].alive;
                x=st[x].r;
            }
        }
    }
    int kth(uint32_t k)//求第K小，需保证有解
    {
        for(uint32_t x=root;true;)
        {
            auto l=st[x].l;
            if(k<=st[l].aliveNodeCount)
                x=l;
            else if(st[x].alive && k==st[l].aliveNodeCount+1)
                return st[x].element;
            else
            {
                k-=st[l].aliveNodeCount+st[x].alive;
                x=st[x].r;
            }
        }
    }
    int prevElement(int val)//严格小于val的最大值，需保证有解
    {
        return kth(rank(val)-1);
    }
    int nextElement(int val)//严格大于val的最小值，需保证有解
    {
        return kth(rank(val+1));
    }
}
```
## 区间操作替罪羊树
```cpp
const uint32_t N = 1e5 + 3;
uint32_t a[N];//1-index
namespace ScapegoatTree
{
    uint32_t treeToArray[N], treeToArrayIndex, root;
    struct node
    {
        uint32_t son[2], subtreeSize, father;
    } st[N];
    void pushup(uint32_t x) // 合并左右子树信息，用来自平衡
    {
        auto l = st[x].son[0], r = st[x].son[1];
        st[x].subtreeSize = st[l].subtreeSize + st[r].subtreeSize + 1;
        if (l)
            st[l].father = x;
        if (r)
            st[r].father = x;
    }
    void inOrderTraversal(uint32_t x) // 中序遍历收集所有点
    {
        if (!x)
            return;
        inOrderTraversal(st[x].son[0]);
        treeToArray[++treeToArrayIndex] = x;
        inOrderTraversal(st[x].son[1]);
    }
    void build(uint32_t &x, uint32_t l, uint32_t r) // 重建完美平衡子树
    {
        auto mid = (l + r) >> 1;
        x = treeToArray[mid];
        if (l < mid)
            build(st[x].son[0], l, mid - 1);
        else
            st[x].son[0] = 0;
        if (r > mid)
            build(st[x].son[1], mid + 1, r);
        else
            st[x].son[1] = 0;
        pushup(x);
    }
    void checkAndRebuild(uint32_t &x) // 重构不平衡的子树
    {
        if (st[x].subtreeSize * 3 > max(st[st[x].son[0]].subtreeSize, st[st[x].son[1]].subtreeSize) * 4)
            return;
        treeToArrayIndex = 0;
        inOrderTraversal(x);
        auto oldFather = st[x].father;
        build(x, 1, treeToArrayIndex);
        st[x].father = oldFather;
    }
    void rotate(uint32_t &x, bool dir)
    {
        auto son = st[x].son[dir ^ 1];
        st[x].son[dir ^ 1] = st[son].son[dir];
        st[son].son[dir] = x;
        st[son].father = st[x].father;
        pushup(x);
        pushup(son);
        x = son;
    }
    inline uint32_t rankToRoot(uint32_t id)
    {
        uint32_t res = st[st[id].son[0]].subtreeSize + 1;
        auto fa = st[id].father;
        while (fa)
        {
            if (st[fa].son[1] == id)
                res += st[st[fa].son[0]].subtreeSize + 1;
            id = fa;
            fa = st[id].father;
        }
        return res;
    }
    void removeByRotate(uint32_t &x)
    {
        auto l = st[x].son[0], r = st[x].son[1];
        if (l == 0 && r == 0)
        {
            st[x].son[0] = st[x].son[1] = st[x].father = 0;
            st[x].subtreeSize = 1;
            x = 0;
            return;
        }
        auto dir = st[l].subtreeSize > st[r].subtreeSize;
        rotate(x, dir);
        removeByRotate(st[x].son[dir]);
        pushup(x);
        checkAndRebuild(x);
    }
    void removeByRank(uint32_t &x, uint32_t k)//调用后根的father记得清空
    {
        if (k <= st[st[x].son[0]].subtreeSize)
            removeByRank(st[x].son[0], k);
        else if (k == st[st[x].son[0]].subtreeSize + 1)
        {
            removeByRotate(x);
            return;
        }
        else
            removeByRank(st[x].son[1], k - (st[st[x].son[0]].subtreeSize + 1));
        pushup(x);
        checkAndRebuild(x);
    }
    void insertByRankFromOldNode(uint32_t &x, uint32_t k, uint32_t oldNodeID)//调用后根的father记得清空
    {
        if (!x)
        {
            x = oldNodeID;
            return;
        }
        if (k <= st[st[x].son[0]].subtreeSize + 1)
            insertByRankFromOldNode(st[x].son[0], k, oldNodeID);
        else
            insertByRankFromOldNode(st[x].son[1], k - (st[st[x].son[0]].subtreeSize + 1), oldNodeID);
        pushup(x);
        checkAndRebuild(x);
    }
    int kth(uint32_t k) // 求第K小，需保证有解
    {
        for (uint32_t x = root; true;)
        {
            auto l = st[x].son[0];
            if (k <= st[l].subtreeSize)
                x = l;
            else if (k == st[l].subtreeSize + 1)
                return x;
            else
            {
                k -= st[l].subtreeSize + 1;
                x = st[x].son[1];
            }
        }
    }
    inline void build(uint32_t n)
    {
        for (int i = 1; i <= n; ++i)
            treeToArray[i] = i;
        build(root, 1, n);
        st[root].father=0;
    }
}
```
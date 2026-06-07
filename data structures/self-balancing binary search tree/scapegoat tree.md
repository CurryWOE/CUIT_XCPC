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
        uint32_t l,r,element,elementCount,subtreeElementCount,allNodeCount,aliveNodeCount;
    }st[N];
    void pushup(uint32_t x)//合并左右子树信息，用来自平衡
    {
        auto l=&st[st[x].l],r=&st[st[x].r];
        st[x].subtreeElementCount=l->subtreeElementCount+r->subtreeElementCount+st[x].elementCount;
        st[x].allNodeCount=l->allNodeCount+r->allNodeCount+1;
        st[x].aliveNodeCount=l->aliveNodeCount+r->aliveNodeCount+(st[x].elementCount>0);
    }
    bool bad(uint32_t x)//判断子树是否平衡
    {
        return st[x].allNodeCount*Alpha <= max(st[st[x].l].allNodeCount,st[st[x].r].allNodeCount)
        || st[x].allNodeCount*Alpha >= st[x].aliveNodeCount;
    }
    void inOrderTraversal(uint32_t x)//中序遍历收集所有有效点
    {
        if(!x)
            return;
        inOrderTraversal(st[x].l);
        if(st[x].elementCount)
            treeToArray[++treeToArrayIndex]=x;
        inOrderTraversal(st[x].r);
    }
    void build(uint32_t& x,uint32_t l,uint32_t r)//重建完美平衡子树
    {
        if(l>r)
        {
            x=0;
            return;
        }
        uint32_t mid=(l+r)>>1;
        x=treeToArray[mid];
        build(st[x].l,l,mid-1);
        build(st[x].r,mid+1,r);
        pushup(x);
    }
    void rebuild(uint32_t& x)//重构不平衡的子树
    {
        treeToArrayIndex=0;
        inOrderTraversal(x);
        build(x,1,treeToArrayIndex);
    }
    void insert(uint32_t&x,uint32_t val)
    {
        if(!x)
        {
            x=++vectexCount;
            st[x]={0,0,val,1,1,1,1};
            return;
        }
        if(st[x].element==val)
            ++st[x].elementCount;
        else if(st[x].element>val)
            insert(st[x].l,val);
        else
            insert(st[x].r,val);
        pushup(x);
        if(bad(x))
            rebuild(x);
    }
    void remove(uint32_t& x,uint32_t val)
    {
        if(st[x].element==val)
            --st[x].elementCount;
        else if(st[x].element>val)
            remove(st[x].l,val);
        else
            remove(st[x].r,val);
        pushup(x);
        if(st[x].subtreeElementCount==0)
        {
            x=0;
            return;
        }
        if(bad(x))
            rebuild(x);
    }
    uint32_t rank(uint32_t x,uint32_t val)//如果val插入多重集的排名
    {
        for(uint32_t res=1;true;)
        {
            if(!x)
                return res;
            if(st[x].element==val)
                return res+st[st[x].l].subtreeElementCount;
            else if(st[x].element>val)
                x=st[x].l;
            else
            {
                res+=st[st[x].l].subtreeElementCount+st[x].elementCount;
                x=st[x].r;
            }
        }
    }
    uint32_t kth(uint32_t x,uint32_t k)//求第K小，需保证有解
    {
        while(true)
        {
            auto l=st[x].l;
            if(k<=st[l].subtreeElementCount)
                x=l;
            else if(k<=st[l].subtreeElementCount+st[x].elementCount)
                return st[x].element;
            else
            {
                k-=(st[l].subtreeElementCount+st[x].elementCount);
                x=st[x].r;
            }
        }
    }
    uint32_t prevElement(uint32_t val)//严格小于val的最大值，需保证有解
    {
        return kth(root,rank(root,val)-1);
    }
    uint32_t nextElement(uint32_t val)//严格大于val的最小值，需保证有解
    {
        return kth(root,rank(root,val+1));
    }
}
```
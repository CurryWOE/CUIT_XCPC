# trie
```c++
const uint32_t N=1e5+3,STR=26;
struct TRIE
{
    int trie[N][STR],tot;
    bool exist[N];
    void init()
    {
        memset(exist,0,sizeof(bool)*(tot+1));
        for(;tot>=0;--tot)
            memset(trie[tot],0,sizeof(trie[tot]));
        tot=0;
    }
    void insert(string& str)
    {
        int root = 0;
        for (char s:str)
        {
            auto& son=trie[root][s-'a'];
            if(!son)
                son = ++tot;
            root = son;
        }
        exist[root] = 1;
    }
    bool find(char *str)
    {
        int root = 0;
        for (char s:str)
        {
            auto& son=trie[root][s-'a'];
            if(!son)
                return 0;
            root = son;
        }
        return exist[root];
    }
};
```
## 01字典树
字符集限定为'0'和'1'的字典树，由于整数可以表示为01串，所以01字典树的功能非常丰富，要单独介绍

线性基能解决一部分异或问题，另一部分大概率是01字典树能解决

对于权值线段树和01字典树都能解决的问题，包括二者持久化都能解决的问题，01字典树跑的更快，实现更简单，权值线段树强在能解决更多问题

01字典树虽然不是自平衡树，但是能实现自平衡树的基本功能，优点是快，缺点就是空间消耗大，平衡树强在能解决更多问题
### 所需空间
N次插入值域为 [0,A] 的数，最坏情况的节点数 $S = \sum\limits_{i=0}^{\lceil \log_2 (A+1) \rceil - 1} \min(2^i, N)$

若N,A变成不小于原数的2的幂，公式简化为

$S = \begin{cases} 2A, & N \ge A \\ 2N + N \log_2 \frac{A}{N}, & N < A \end{cases}$
```c++
const int N=1e5+3;
struct TRIE
{
    int trie[N][2],tot;
    bool exist[N];
    void init()
    {
        for(;tot>=0;--tot)
        {
            exist[tot]=0;
            for(int j=0;j<2;++j)
                trie[tot][j]=0;
        }
        tot=0;
    }
    void insert(ll x)
    {
        int root = 0;
        for(int i=30;i>=0;--i)
        {
            auto& son=trie[root][(x>>i)&1];
            if(!son)
                son = ++tot;
            root = son;
        }
        exist[root] = 1;
    }
};
```

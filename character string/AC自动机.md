#! https://zhuanlan.zhihu.com/p/668062180
# AC自动机
## 确定有限状态自动机(DFA)
一个DFA包含有限个状态（包含一个初始状态和若干个终止状态），并可以根据输入和转移函数在状态间进行转移。我们常常把DFA看作一张有向图（称为状态图），节点表示状态，而边表示转移。确定有限状态自动机的“确定”一词体现在，对于一个给定的状态和给定的输入，可以唯一地确定下一个要转移的状态。

如果输入结束后，DFA处于终止状态，就称这个字符串被接受了。
## AC自动机接受什么
以任一模式串结尾的文本串
## fail树
给每个状态分配一条fail边，它连向的是该状态对应字符串在trie上存在的最长真后缀所对应的状态

特别地，根节点转移到自己

如果当前状态 s 在某个终止状态 t 的fail树的子树上，那么当前文本串就与 t 所对应模式串匹配

重构之后这个东西已经不是模式串组成的trie了，新加了原来没有的转移
```cpp
namespace AhoCorasickAutomaton
{
    const int M = 1e6 + 5;
    const int STR = 26;
    int tot, dfn;
    struct node
    {
        int nxt[STR], fail, en;
    } G[M];
    vector<int> e[N];
    void insert(const string &s)
    {
        int rt = 0;
        for (auto &c : s)
        {
            int &nxt = G[rt].nxt[c - 'a'];
            if (!nxt)
                nxt = ++tot;
            rt = nxt;
        }
        G[rt].en++;
    }
    void build()
    {
        queue<int> Q;
        for (int i = 0; i < 26; ++i)
            if (G[0].nxt[i])
                Q.push(G[0].nxt[i]);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int i = 0; i < 26; ++i)
            {
                int &v = G[u].nxt[i], &w = G[G[u].fail].nxt[i];
                if (v)
                    G[v].fail = w, Q.push(v);
                else
                    v = w;
            }
        }
        for (int i = 1; i <= tot; ++i)
            e[G[i].fail].push_back(i);
    }
    void init()
    {
        for (int i = 1; i <= tot; ++i)
            e[i].clear();
        for (int i = 1; i <= tot; ++i)
        {
            memset(G[i].nxt, 0, sizeof(int) * STR);
            G[i].fail = G[i].en = 0;
        }
        tot = dfn = 0;
    }
};
```
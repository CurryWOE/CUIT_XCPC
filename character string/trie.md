# trie
```c++
const int N=1e5+3;
const int STR=26;
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
        int id,root = 0;
        for (char s:str)
        {
            id= s - 'a';
            if(!trie[root][id])
                trie[root][id] = ++tot;
            root = trie[root][id];
        }
        exist[root] = 1;
    }
    bool find(char *str)
    {
        int root = 0,id;
        for (char s:str)
        {
            id= s - 'a';
            if(!trie[root][id])
                return 0;
            root = trie[root][id];
        }
        return exist[root];
    }
};
```

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
        int root = 0,id;
        for(int i=30;i>=0;--i)
        {
            id= (x>>i)&1;
            if(!trie[root][id])
                trie[root][id] = ++tot;
            root = trie[root][id];
        }
        exist[root] = 1;
    }
};
```

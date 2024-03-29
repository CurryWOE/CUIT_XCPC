#! https://zhuanlan.zhihu.com/p/662653310
# 2-SAT
有 $n$ 个布尔变量 $x_i$ ，另有 $m$ 个需要满足的条件，每个条件形如 ["$x_i$ 为真" 或 "$x_j$ 为假"]，["$x_i$ 为假" 或 "$x_j$ 为假"]

2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。

要满足 ["$x_i$ 为真" 或 "$x_j$ 为假"] 这个条件，显然能推出两结论： $x_i$ 为假必定有 $x_j$ 为假；$x_j$ 为真必定有 $x_j$ 为真

把A推导出B的逻辑关系，变成图上的有向边，每个变量有两个点，分别表示 $x_i$ 为真，$x_i$ 为假

当 $x_i$ 为真，$x_i$ 为假能互相推导（即鱼越大鱼越小的矛盾），反应在图上就是二者处于一个强连通分量，此时无解

当A能推导出非A，而非A不能推导出A，那么A只能是假；反之同理。反应在图上就是拓扑序越大的是所需答案，在我的SCC板子里就是所属强连通分量编号小

如果A和非A没有逻辑关系，那么取值随意
```cpp
for(int i=0;i<m;++i)
{
    cin>>x>>a>>y>>b;//A_x为a或A_y为b
    e[2*x-(!a)].push_back(2*y-b);
    e[2*y-(!b)].push_back(2*x-a);
}
for(int i=1;i<=n*2;++i)
    if(!dfn[i])
        tarjan(i);
for(int i=1;i<=n;++i)
{
    if(f[2*i]==f[2*i-1])
    {
        cout<<"IMPOSSIBLE";
        return 0;
    }
    else
        ans[i]=(f[2*i-1]<f[2*i]);
}
cout<<"POSSIBLE\n";
for(int i=1;i<=n;++i)
    cout<<ans[i]<<" ";
```
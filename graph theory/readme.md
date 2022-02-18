>英文一定要记一下，某一年很多人不知道DAG啥意思导致错误  
>比赛是全英文题面，记住了就不用查
# 图(Graph)
图是一个二元组 $G=(V,E)$

$V$ 表示点集(Vertex set),即点的集合，$E$ 表示边集(Edge set)，即边的集合

常用 $|V|,|E|$ 表示点集内元素数量，边集内元素数量

# 稠密图
$|E|\approx|V|^2$

# 稀疏图
$|E|\approx |V|$

# 有向图(Directed graph)
边有方向，即可以从a点到b点，但不能从b点到a点

例如你欠我的钱和我欠你的钱是万万不能混淆的。

# 无向图(Undirected graph)
边无方向，即可以从a点到b点，又可以从b点到a点

# 边权(Edge weight)
边被赋予的一个数，表示通过该边，会变化多少

## 例子
你开车从a地到b地，汽油减少10L，点a到点b的边的边权为10

通常减少为正数，增加为负数

假如中途有加油站，你开车从a地到b地，汽油增加10L，点a到点b的边的边权为-10

# 图的存储
>实现仅给出关键代码
1. 直接存
## 定义
```c++
struct EDGE
{
    int u,v;//表示点u连着点v
}e[1000];
int total;//边的数量
```
## 清零
```c++
total=0;
```
## 加边
```c++
e[++total]={u,v};
```
## 遍历
```c++
for(int i=1;i<=total;++i)
{
    printf("%d %d",e[i].u,e[j].v);
}
```

2. 邻接矩阵

$a[i][j]$ 表示点 $i$ 到点 $j$ 的边
## 定义
```c++
int a[100][100];//邻接矩阵
```
## 清零
```c++
memset(a,0,sizeof(a));
```
## 加边
```c++
a[u][v]=1;//表示u和v有边连接
```
## 遍历
```c++
for(int i=0;i<n;++i)
{
    for(int j=0;j<n;++j)
    {
        if(a[i][j])
            printf("%d %d\n",i,j);
    }
}
```

3. 邻接表

$e[i]$ 表示点i连接的边,$e[i][j]$ 表示点 $i$ 连接的第 $j+1$ 条边
## 定义
```c++
vector<int> e[1000];//邻接表
```
## 清零
```c++
for(int i=0;i<n;++i)
    e[i].clear();
```
## 加边
```c++
e[u].push_back(v);//表示u和v有边连接
```
## 遍历
```c++
for(int i=0;i<n;++i)
{
    int sz=e[i].size();
    for(int j=0;j<sz;++j)
        printf("%d %d\n",i,e[i][j]);
}
```

4. 链式前向星

和邻接表类似

head[i]表示点i最近连的一条边的下标，e[i]表示第i条边

## 定义
```c++
struct EDGE
{
    int v;//表示点i连的这条边的对应的点
    int next;//表示点i连的下一条边的下标
}e[1000];
int head[100];
int total;//边的数量
```
## 清零
```c++
memset(head,-1,sizeof(head));
total=0;
```
## 加边
```c++
e[++total]={v,head[u]};
head[u]=total;
```
## 遍历
```c++
for(int i=0;i<n;++i)
{
    for(int j=head[i];j!=-1;j=e[j].next)
        printf("%d %d",i,e[j].v);
}
```
邻接矩阵适用于稠密图

邻接表和链式前向星适用于稀疏图

在 $|E|>1e5$ 时，邻接表更快，反之链式前向星

# 自环(Loop)
对 $E$ 中的边 $e=(u,v)$,若 $u=v$，则e被称为自环

# 重边(Multiple edge)
若 $E$ 中存在两个顶点完全相同的元素 $e_1,e_2$，则它们被称作重边
## 注意
在无向图中 $(u,v)$ 和 $(v,u)$ 算一组重边

而在有向图中 $(u,v)$ 和 $(v,u)$ 不为重边

# 简单图(Simple graph)
若一个图中没有自环和重边，它被称为简单图

在题目中，如果没有特殊说明，可以不是简单图，需要处理一下

>下面3个概念帮助理解环，不需要记忆

# 途径
将若干个点连接起来的边的集合 $W$

# 迹
对于一条途径 $W$，$e_1,e_2,...,e_k$ 两两互不相同

# 回路
对于一个迹 $W$，起点和终点是同一个点

# 环(Cycle)(又称简单回路(Simple circuit))
对于一个回路 $W$，起点和终点是点序列中唯一重复出现的点对

# 无环图(Acyclic graph)
不存在环的图

>开头说的DAG就是有向无环图

# 图的遍历
## 深度优先搜索(Depth first search)
## 广度优先搜索(Breadth first search)


# 度数(Degree)
与点 $a$ 相连的边的数量，称之为度

以点 $a$ 为起点的边的数量，称之为出度(Out-degree)

以点 $a$ 为终点的边的数量，称之为入度(In-degree)

# 拓扑排序

# 传递闭包
# 最短路
# 最小生成树

# 补图(Complement graph)
点集一样，边集互补，和补集类似

# 反图(Transpose Graph)
点集一样，边集反向，仅对于有向图有反图概念

# 完全图(Complete graph)
>对无向图和有向图定义不一样

## 无向图
任意不同两点间均有边

## 有向图
任意不同两点间都有两条方向不同的边

# 支配点(Universal vertex)
点 $v$ 的度数 $=|G|-1$
# 星图/菊花图(Star graph)
若无向简单图满足，存在一个点v为支配点，其余点之间没有边相连

这个图常用来卡图论算法

# 链(Chain/Path Graph)
无向简单图的所有边恰好构成一条简单路径

这个图常用来卡图论算法

菊花图和链结合一下也能用来卡图论算法

# 树(Tree)
无向连通图不含环


---
# k - 正则图 (k-Regular Graph)
无向图，每个顶点的度数都是一个固定的常数k



# 子图(Subgraph)
对一张图 $G=(V,E)$，若存在另一张图 $H=(V',E')$，

满足 $V'$ 是 $V$ 的子集且 $E'$ 是 $E$ 的子集，则称H是G的子图



# 点连通(Connected)
对于一张图 $G=(V,E)$，$u,v∈V$，$u,v$ 二点连通

即至少存在一条迹，使得起点是 $u$，终点是 $v$

## 连通图(Connected graph)
>对无向图和有向图定义不一样

### 无向图
$\forall u,v∈V$，$u,v$ 二点连通

### 有向图
$\forall u,v∈V$，$u,v$ 二点连通，则称这张图是强连通的(Strongly connected)

若一张有向图的边替换为无向边后可以得到一张连通图，则称原来这张有向图是弱连通的(Weakly connected)

## 连通块(又称连通分量)(Connected component)
>对无向图和有向图定义不一样
### 无向图
不连通的图是由多个连通子图组成的。

这些不相交的连通子图称为图的连通块/连通分量

### 有向图
与无向图类似，

弱连通分量 (Weakly connected component)

强连通分量 (Strongly Connected component)

## 割(Cut)
>分别有点的定义和边的定义
### 点上定义
删掉一部分点以及相连的边,使图不连通

## 点割集(Vertex cut)
被删掉的点的集合

## 割点(Cut vertex)
大小为一的点割集

## $k$ -点连通的(k-vertex-connected)
图 $G$ 的阶$\ge k+1$且不存在大小为 $K-1$ 的点割集

## 点连通度(Vertex connectivity)
使得上式成立的最大的 $k$ 

## 点双连通(Biconnected)
没有割点的连通图

与连通分量类似，也有点双连通分量(Biconnected component)

### 边上定义
删掉一部分边，（点不删，可以孤立存在），使图不连通

## 边割集(Edge cut)
被删掉的边的集合

## 桥(Bridge)
大小为一的边割集

## k-边连通的(k-edge-connected)
图 $G$ 边集 $E$ 元素数量 $\ge k+1$ 且不存在大小为 $K-1$ 的边割集

## 边连通度(Edge connectivity)
使得上式成立的最大的 $k$

## 边双连通(2-edge-connected)
没有桥的连通图

与连通分量类似，也有边双连通分量(2-edge-connected component)



## 森林(Forest)
多棵树组成

## 仙人掌(Cactus)
无向连通图的每条边最多在一个环内

## 沙漠(desert)
多棵仙人掌组成

## 二分图(Bipartite graph)
图的点集可以被分为两部分，每一部分的内部都没有连边

完全二分图/满二分图(Complete bipartite graph/Biclique)：
二分图中任何两个不在同一部分的点之间都有连边

匹配(Matching)(又叫边独立集 (Independent edge set))：
对于图G，E的子集E'中任意两条不同的边都没有公共的端点，
且E'中任意一条边都不是自环，则E'是图G的一个匹配，
例子：
一夫一妻制，任一丈夫都只有一个妻子，任一妻子都只有一个丈夫

如果一个点是匹配中某条边的一个端点，
则称这个点是 被匹配的 (matched)/饱和的 (saturated)，
否则称这个点是 不被匹配的 (unmatched)。

极大匹配(Maximal matching)：
一个匹配，满足加入任何一条边后都不再是一个匹配

最大匹配(Maximum-cardinality matching)：
边数最多的匹配
最大的极大匹配就是最大匹配

最大权匹配 (Maximum-weight matching)：
边权之和最大的匹配

完美匹配 (Perfect matching)：
一个匹配，满足所有点都是被匹配的

增广路径(Augmenting path)：
一个匹配M，满足一条路径以非匹配点为起点和终点，每相邻两条边的其中一条在匹配中而另一条不在匹配中

---



构造图方式（持续更新）：

以下内容需思考后再看答案

1.假如你会用边权，但不会点权，现在给你一个有点权的图，如何处理：
点权：
到达该点会变化多少

---



拆点：
把一个点变成两个点，入点和出点，点权就变成了边权

2.（区域赛真题）有向图，同一点集合内任意两点边权一样，不同集合间的点边权不一样，如何处理：

---



共点：
点集合内增加一个点，集合内其他点到该点边权为该点集合内任意两点边权，该点到集合内其他点边权为0，反之亦可

3.waiting.......
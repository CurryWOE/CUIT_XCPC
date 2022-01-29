# 概率DP
解决概率问题与期望问题

一般情况下，

解决概率问题需要顺序处理，

而解决期望问题使用逆序处理，

如果定义的状态转移方程存在后效性问题，还需要用到 高斯消元 来优化。

如果处理DAG上的问题，需要拓扑序处理

## 一些期望知识

区分 $E(X)$ 、 $E(X \mid Y)$ 、 $E(X \mid Y=y)$

$E(X)$ ：一个数

$E(X \mid Y)$ ：随机变量，关于 $Y$ 的函数，没有固定的 y 值

$E(X \mid Y=y)$ ： $y$ 的函数 $f(y)$ ，对于给定的 $y$ ，有唯一确定值与之对应

$E(X)$ 是对所有 $ω∈Ω$ ，$X(ω)$ 取值全体的加权平均；

而 $E(X \mid Y=y)$ 是局限在 $ω∈{ω:Y(ω)=y}$ 时， $X(ω)$ 取值局部的加权平均。

可以理解为先挑出满足 $Y=y$ 的，再对挑出的不同群体求加权平均

计算期望用到全期望公式 $E(X)=E(E(X\mid Y))$

### 全期望公式例子

1个学校有多个班，每个班有多个学生，如何计算全校的平均分？

1. 全部学生的分数加起来，除以总人数，这就是计算 $E(X)$

2. 先计算每个班的平均分，这就是计算 $E(X \mid Y='一班')$，$E(X \mid Y='二班')$...每个班是一个群体，再算加权平均数，这就是计算 $E(E(X\mid Y))$

第2个方法是先局部平均，再整体平均

所以期望用加权平均数算

### 加权平均数例子

1袋糖果，由3种糖果混装，

第一种糖果装了$\frac{1}{2}$，价格是40/克，

第二种糖果装了$\frac{1}{3}$，价格是60/克，

第三种糖果装了$\frac{1}{6}$，价格是80/克，

如何定价这1袋糖果？

<font size=7>$\frac{\frac{1}{2}*40+\frac{1}{3}*60+\frac{1}{6}*80}{\frac{1}{2}+\frac{1}{3}+\frac{1}{6}}=45$</font>

45就是糖果定价

---
## 好题推荐
[绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)

[换教室](https://www.luogu.com.cn/problem/P1850)

[收集邮票](https://www.luogu.com.cn/problem/P4550)

[OSU!](https://www.luogu.com.cn/problem/P4316)

## luogu p4316题解（经典期望DP）

要求处理1到n的期望距离

如果正向处理得记录1到每个点的概率

设$probability[i]$是1到 $i$ 概率，$distance[i]$是1到 $i$ 期望距离

有一条u到v的边，边权为 $w$ ，选择该边的的概率为 $p$ 

### 更新公式

$probability[v]= \sum probability[u]*p$

$distance[v]= \sum (distance[u]+w*probability[u])*p$

概率更新公式显然，

### 期望更新公式证明

<font size=4>$probability[v]=\sum probability[u_i]*p$</font>

<font size=6>$distance[v]=\frac{\sum probability[u_i]*p*(w+distance[u_i])}{\sum probability[u_i]*p}$</font>

由于更新 $u \rightarrow v$ 相关信息时，$\sum probability[u_i]*p$暂时不知道,所以先更新 

<font size=4>$distance[v]=\sum probability[u_i]*p*(w+distance[u_i])$</font>

当v变成新的 $u'$ 时,就可以知道正确的$distance[v]$了，式子可以写成

<font size=6>$distance[u']=\frac{distance[u']}{probability[u']}$</font>

再把这个式子代回去

<font size=6>$distance[v']=\sum probability[u']*p*(w+\frac{distance[u']}{probability[u']})$</font>

再化简就可以得到最后的式子

<font size=4>$distance[v]= \sum (distance[u]+w*probability[u])*p$</font>

这道题正向处理理解了，逆向就好说了

设$probability[i]$是 $i$ 到 $n$ 概率，$distance[i]$是 $i$ 到 $n$ 期望距离

由于题目保证每个点都能到 $n$ ，所以$probability[i]$恒为1，所以只需要$distance[i]$一个数组

更新公式改为：

$distance[v]= \sum (distance[u]+w)*p$

为了方便逆向遍历图，建反向图
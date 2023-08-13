#! https://zhuanlan.zhihu.com/p/648827761
# 子集和DP
每个集合有一个权值，计算一个集合的所有子集的和
## 从前缀和说起
一二三维前缀和预处理过程如下：
```cpp
for(int i=1;i<=n;++i)
    s[i]=s[i-1]+a[i];
for(int i=1;i<=n;++i)
    for(int j=1;j<=n;++j)
        s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
for(int i=1;i<=n;++i)
    for(int j=1;j<=n;++j)
        for(int k=1;k<=n;++k)
            s[i][j][k]=a[i][j][k]+s[i−1][j][k]+s[i][j−1][k]+s[i][j][k−1]−s[i−1][j−1][k]−s[i−1][j][k−1]−s[i][j−1][j−1]+s[i−1][j−1][k−1];
```
可以发现，到了高维，容斥操作不能视为 $O(1)$ ，和维度有关

设维度 $t$ ，上面这种写法的复杂度是 $(n^t\times 2^t)$

---
介绍另一种方法计算高维前缀和：
```cpp
for(int i=1;i<=n;++i)
	s[i]=s[i-1]+a[i];
//	
for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
		s[i][j]=s[i][j-1]+a[i][j];
for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
		s[i][j]=s[i-1][j]+s[i][j];
//
for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
        for(int k=1;k<=n;++k)
		    s[i][j][k]=s[i][j][k-1]+a[i][j][k];
for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
        for(int k=1;k<=n;++k)
		    s[i][j][k]=s[i][j-1][k]+a[i][j][k];
for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
        for(int k=1;k<=n;++k)
		    s[i][j][k]=s[i-1][j][k]+a[i][j][k];
```
实际上是一维一维的统计，正确性可以对着二维前缀和模拟一下

复杂度降到了 $O(n^t\times t)$
## 高维前缀和与SOSDP的联系
在状压DP中，使用一个二进制数表示集合，比如0110101，0表示没选这个物品，1表示选了这个物品

子集：原来选了，子集可以选或不选，也就是0或1；原来没选，子集只能不选，也就是0

如果把这个二进制数看成7维的坐标，然后这个集合的权值就是这个坐标的权值，且每个维度最大值是2，即n=2

那么要统计的就是所有坐标中满足每一维度的坐标都小于等于0110101每一维度的坐标的权值和，就是高维前缀和

SOSDP就是n=2的高维前缀和
## SOSDP
由于是高维前缀和的特化版本，代码用状压优化

正确性可以对照高维前缀和理解，其他维度一样，当前维度少1
```cpp
for(int i=0;i<t;++i)//枚举当前处理哪一维度
	for(int j=0;j<(1<<t);++j) 
        if(j>>i&1) S[j]+=(S[j^(1<<i)]);//如果该维度为1，统计上该维度为0的前缀和
```
## 子集&超集
二进制的子集满足偏序关系，在前文的联系中介绍过了

把二进制中的1当成0,0当成1。求出来的就是超集
```cpp
for(int i=0;i<t;++i)
	for(int j=0;j<(1<<t);++i)
        if(!(j>>i&1)) S[j]+=(S[j^(1<<i)]);
```
## 题目特征
下标和位运算组成的关系式，求权值的（和，最值）等。或者反之

位运算要转化为偏序关系
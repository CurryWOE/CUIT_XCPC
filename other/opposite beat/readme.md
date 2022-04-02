# 对拍

## 作用
用程序判断你的程序答案是否正确，有运气成分

## 实现
先写出正解（你认为的），和暴力。再写一个数据生成器，生成的数据作为正解和暴力的输入，比较输出，如有不一样，输出错误数据

## 暴力(brute force)
指时间复杂度或空间复杂度高，但实现简单的解答。

## 不适用
1. TLE和MLE，对拍只能保证正确性
2. 正解就是暴力的题目，你可能暴力写不对

## 为什么有运气成分
数据是随机生成的，不一定找到你的bug

## 注意事项
所有文件需在同一文件夹的同一层里

编数据时最好不要用原题数据，暴力会卡死，毕竟只是保证正确性，数据小一点就好

修改cpp文件后要重新编译，因为调用的是exe文件

## 实操
以斐波那契数列为例，这里设递归为暴力，迭代为正解

先写出前4个程序并编译再运行最后一个程序

正解
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,f0,f1,f2;
    freopen("data.txt","r",stdin);
    scanf("%d",&n);
    f0=1;
    f1=1;
    if(n<2)
        printf("1");
    else
    {
        for(;n>=2;--n)
        {
            f2=f0+f1;
            f0=f1;
            f1=f2;
        }
        printf("%d",f2);
    }
    return 0;
}
```
暴力
```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int n)
{
    if(n<2)
        return 1;
    return f(n-1)+f(n-2);
}
int main()
{
    int n;
    freopen("data.txt","r",stdin);
    scanf("%d",&n);
    printf("%d",f(n));
    return 0;
}
```
数据生成
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("data.txt","W",stdout);
    srand(time(0));
    //必加，否则生成数据不随机
    int n,l,r;
    l=0,r=20;
    n=rand()%r+l;
    //rand()函数用来生成随机数
    //n的范围在[l,r-1+l]
    printf("%d\n",n);
    return 0;
}
```
检查
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    t=10;
    //测试数据的组数
    while(t--)
    {
        system("dataGenerator.exe > data.txt");
        system("positiveSolution.exe < data.txt > ps.txt");
        system("bruteForce.exe < data.txt > bf.txt");
        if(system("fc ps.txt bf.txt"))
            break;
        //fc是file compare的缩写,当两个文件不同时输出1，否则0
        //system函数执行失败会返回-1，我自己电脑常规方式运行不了，要用coderunner插件
    }
    if(t==-1)
        printf("No errors were found.");
    else
        printf("Errors found.");
    return 0;
}
```

[树和图的生成方法](https://space.bilibili.com/31675307/article)
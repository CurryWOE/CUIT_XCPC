#include<bits/stdc++.h>
using namespace std;
int main()
{
    // freopen("data.txt","W",stdout);
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
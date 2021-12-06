#include<iostream>
#include<cstdio>
using namespace std;
char strin[20];
int main()
{
    int tests = 10;
    int test = 0;
    srand((unsigned)time(NULL));
    //使用当前时钟作为随机数种子,必需加
    while(++test <= tests)
    {
        sprintf(strin, "%d.in", test);
        //向strin数组格式化输入
        freopen(strin, "w", stdout);
        //打开名为strin内容的文件并写入，如果不存在就创建
        printf("%d",rand()%10000000000+1);
        //产生随机数并输入文件
    }
    return 0;
}
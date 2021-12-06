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
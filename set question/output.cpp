#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 1e6 + 5;
char strin[20];
char strout[20];
int num[maxn];
int main()
{
    int cases = 8;
    int Case = 0;
    while(++Case<=cases)
    {
        sprintf(strin, "%d.in", Case);
        sprintf(strout, "%d.out", Case);
        freopen(strin, "r", stdin);
        //读取strin内容为名的文件
        freopen(strout, "w", stdout);
        //写入strout内容为名的文件
        {
            //标程，或者叫正解
        }
    }
    return 0;
}
/*
快速傅立叶变换（fast Fourier transform）简称fft
时间复杂度O(nlogn)
空间复杂度O(2^t),（2^t>单项式合并后项数）
直接作用：对于一个一元函数，系数表达式和点值表达式互相转换
稍微复杂点作用：快速求出两个多项式相乘的结果
1个1元二次和一个1元3次相乘，最多有6项，空间复杂度里的t=3
应用：
1.从题目中抽象出多项式（难点）
2.求出答案和多项式之间联系（难点）
3.用fft求解多项式相乘（fft本体，但没啥好变化的，看懂原理就好了）
4.输出答案

fft原理讲解见
https://www.zhihu.com/zvideo/1440666041495621632
下面是洛谷p3803模板题
只写了一点注解，题解里有更详细的
*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 10;
const double Pi = acos(-1.0);
struct comp//c++complex头文件的complex类运行速度很慢，所以自己定义复数结构体
{
    double x, y;
    comp (double xx = 0, double yy = 0) {x = xx, y = yy;}
    comp operator + (const comp b) const {return comp(x + b.x,y + b.y);}
    comp operator - (const comp b) const {return comp(x - b.x,y - b.y);}
    comp operator * (const comp b) const {return comp(x * b.x - y * b.y,x * b.y + y * b.x);}
} a[MAXN], b[MAXN];
int l, limit, r[MAXN];
int N,M;
void fft(comp *A, int type)
{
    for (int i = 0; i < limit; i++)//求出要迭代的序列 
    {
        if (i < r[i])
            swap(A[i], A[r[i]]);
    }
    for (int mid = 1; mid < limit; mid <<= 1)//待合并区间的中点
    {
        comp Wn( cos(Pi / mid) , type * sin(Pi / mid) );//单位根 
        for (int R = mid << 1, j = 0; j < limit; j += R)//R是区间的右端点，j表示前已经到哪个位置了 
        {
            comp w(1, 0);//幂 
            for (int k = 0; k < mid; k++, w = w * Wn)//枚举左半部分 
            {
                comp x = A[j + k], y = w * A[j + mid + k];//蝴蝶效应 
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
    if(type==-1)
    {
        for (int i = 0; i <= N + M; i++)
            a[i].x=(double)((int)(a[i].x / limit + 0.5));//四舍五入取整
    }
}
void input()
{
    cin>>N>>M;
    for (int i = 0; i <= N; i++)
        cin>>a[i].x;
    for (int i = 0; i <= M; i++)
        cin>>b[i].x;
}
void init(int x)//x表示2个多项式相乘最多有几个单项式
{
    limit=1;
    l=-1;
    while (limit < x)
        limit <<= 1, l++;
    for (int i = 0; i < limit; i++)
        r[i] = ( r[i >> 1] >> 1 ) | ( (i & 1) << l );
}
void output()
{
    for (int i = 0; i <= N + M; i++)
        cout<<(int)a[i].x<<" ";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    input();
    init(N+M+1);
    fft(a, 1);
    fft(b, 1);
    for (int i = 0; i < limit; i++)
        a[i] = a[i] * b[i];
    fft(a, -1);
    output();
    return 0;
}
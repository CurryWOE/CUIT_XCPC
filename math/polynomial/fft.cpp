/*
快速傅立叶变换（fast Fourier transform）简称fft
时间复杂度O(nlogn)
空间复杂度O(2^t),（2^t>单项式合并后项数）
直接作用：对于一个一元函数，系数表达式和点值表达式互相转换
稍微复杂点作用：快速求出两个多项式相乘的结果
1个1元二次和一个1元3次相乘，最多有6项，空间复杂度里的t=3
应用：
1.从题目中抽象出多项式
2.求出答案和多项式之间联系
3.用fft求解多项式相乘（fft本体，学到后面会要求对fft本质优化，所以原理要看懂）
4.输出答案

fft原理讲解见
https://www.zhihu.com/zvideo/1440666041495621632
下面是洛谷p3803模板题
只写了一点注解，题解里有更详细的
*/
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
void init(int x)//x表示2个多项式相乘最多有几个单项式
{
    limit=1;
    l=-1;
    while (limit < x)
        limit <<= 1, l++;
    for (int i = 0; i < limit; i++)
        r[i] = ( r[i >> 1] >> 1 ) | ( (i & 1) << l );
}
init(N+M+1);
fft(a, 1);
fft(b, 1);
for (int i = 0; i < limit; i++)
    a[i] = a[i] * b[i];
fft(a, -1);
/*
三次变两次优化：
(a+bi)^2=a^2-b^2+2abi
所以把b放在虚部，答案是虚部/2，注意把fft除limit改成虚部
*/
分治fft
void solve(int l,int r,int logn)
{
    if(logn<=0) return;
    if(l>=n) return;
    int mid=(l+r)>>1,i;
    ll t=inv(r-l);
    solve(l,mid,logn-1); // 计算左区间
    calcrev(logn);
    memset(a+(r-l)/2,0,sizeof(ll)*(r-l)/2); // 拷贝左区间
    memcpy(a,f+l,sizeof(ll)*(r-l)/2); // 填充0
    memcpy(b,g,sizeof(ll)*(r-l)); // 拷贝g
    FFT(a,logn,0),FFT(b,logn,0); // 卷积
    for(i=0;i<r-l;i++) a[i]=a[i]*b[i]%kcz;
    FFT(a,logn,1);
    for(i=0;i<r-l;i++) a[i]=a[i]*t%kcz;
    for(i=(r-l)/2;i<r-l;i++)
        f[l+i]=(f[l+i]+a[i])%kcz; // 把卷积后的右半段的数加到f数组后半段
    // 可能你会注意到，这个卷积是(r-l)/2的长度卷一个r-l的长度，而我卷积时最终结果当作r-l的长度来存，这会不会有影响？注意到超出部分是(r-l)/2左右，根据fft的实现，超出部分是会重新从0开始填的，所以只会影响结果的前半段，与后半段无关
    solve(mid,r,logn-1); // 计算右区间
}
#! https://zhuanlan.zhihu.com/p/563153071
# 输入输出(input/output)
这里不写C的IO，因为C的IO相比于精细实现的CPP的IO，性能不行
# 输入(cin)
```cpp
#include<iostream>
cin>>a>>b;
char s[10];
cin>>(s+1);//cpp17及以前
cin.get(s+1,x)//cpp20及以后，读入至多x个字符
```
# 输出(cout)
```cpp
#include <iostream>
#include <iomanip>
cout<<a<<" "<<b<<endl;
//保留 n 位小数，小于 5 舍去，大于 5 进位，大部分数字不能精确等于5
//只有分母为 $2^n$ 的小数（如 0.5, 0.125）能精准等于 5，如果保留位的最后一位是奇数，则进位；否则舍去
cout << fixed << setprecision(3) << 3.1415; // 3.142
//指定宽度(只对紧随其后的一个输出有效)
cout << setw(5) << 12; // " 12"
//左对齐(默认右对齐)
cout << left << setw(5) << 12; // "12 "
//补零
cout << setfill('0') << setw(5) << 12; // 00012
//进制转换(hex / oct / dec)
cout << hex << 255; // ff
```
# 最常用的两个优化
## endl换成'\n'
endl表示清空缓冲区，同时起到换行的作用，不同于printf，cout的结果不会马上看到，要么清空缓冲区才能看到，要么程序结束才能看到

但是endl比较慢，如果不需要立即看到输出，那么换成'\n'
## 取消与标准C输入输出的同步，取消CPP输入输出流的绑定
在 main 开头加入

开启后绝对不能混用 scanf/printf，否则会导致输出顺序混乱或程序崩溃
```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
//cout.tie(nullptr);读者可能在某些地方见过它，但它实际上是多余的，cout 默认就没有绑定任何流
```
# 各类输入输出的性能比较
这里只讨论编译器优化开启O3的情况，不开全优化的性能比较没有意义
## 输入整数
| 方法 | 性能 (million numbers/second) |
| :--- | :--- |
| scanf | 12.3 |
| cin | 15.9 |
| cin + from_chars | 21.8 |
| getchar | 28.3 |
| int_unlocked | 35.3 |
| fread + from_chars | 40.2 |
| cin.read + from_chars | 40.6 |
| fread + 手动解析 | 57.1 |

性能取决于 IO 链路长度，fread/cin.read > getchar > cin > scanf

scanf 因运行期解析字符串格式最慢，cin 在 -O3 下内联了类型重载
## 输入浮点数
| 方法 | 性能 (million numbers/second) |
| :--- | :--- |
| cin | 4.8 |
| scanf | 6.6 |
| cin + from_chars | 20.4 |
| cin.read + from_chars | 28.5 |
| fread 快读 + from_chars | 33.3 |

性能取决于 Locale (本地化) 检查，传统 scanf 和 cin 必须检查区域设置（如小数点符号）；from_chars 强制按标准格式解析且无 Locale 锁
## 输出整数
| 方法 | 性能 (million numbers/second) |
| :--- | :--- |
| printf | 20.0 |
| cout | 26.5 |
| to_chars + cout.write | 50.0 |
| fwrite + 手动解析 | 54.0 |
## 输出浮点数
| 方法 | 性能 (million numbers/second) |
| :--- | :--- |
| printf | 3.2 |
| cout(sync_off) | 4.0 |
| to_chars + cout.write | 15.0 |
# 不同场景的输入输出选择
## 一般情况
假定输入时间/输出时间不超过100ms视为一般情况，测试等于：

输入2e6个整数，4e5个浮点数

输出2.5e6个整数，3e5个浮点数

那么直接使用cin/cout
## IO为主要瓶颈
这里主要考虑极致性能，不能手动输入数据，也不能动态观察输出，交互题不能用它
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <charconv>
#include <type_traits>
#include <string>
class FastIO
{
private:
    static const int BUF_SIZE=1<<20,FLOAT_PRECISION=6,FLOAT_BUF_MAX=128,INT_BUF_MAX=40,WRITE_MARGIN=512;
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE];
    char *in_cursor = in_buf, *in_end = in_buf, *out_cursor = out_buf;
    inline char fetch_char()
    {
        if (in_cursor == in_end)
        {
            in_end = (in_cursor = in_buf) + fread(in_buf, 1, BUF_SIZE, stdin);
            if (in_cursor == in_end)
                return EOF;
        }
        return *in_cursor++;
    }
    inline void flush()
    {
        if (out_cursor != out_buf)
        {
            fwrite(out_buf, 1, out_cursor - out_buf, stdout);
            out_cursor = out_buf;
        }
    }
    inline void push(char c)
    {
        if (out_cursor == out_buf + BUF_SIZE)
            flush();
        *out_cursor++ = c;
    }
public:
    FastIO()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
    ~FastIO()
    {
        flush();
    }
    template <typename T>
    requires std::is_integral_v<T>
    inline void read(T &x)
    {
        x = 0;
        bool neg = false;
        char ch = fetch_char();
        for(;ch != EOF && !isdigit(ch);ch = fetch_char())
            if (ch == '-')
                neg = true;
        if (neg)
            for(;isdigit(ch);ch = fetch_char())
                x = x * 10 - (ch - '0');
        else
            for(;isdigit(ch);ch = fetch_char())
                x = x * 10 + (ch - '0');
    }
    template <typename T>
    requires std::is_floating_point_v<T>
    inline void read(T &x)
    {
        x = 0;
        static char temp[FLOAT_BUF_MAX];
        int len = 0;
        char ch = fetch_char();
        for(;ch != EOF && isspace(ch);ch = fetch_char()){}
        for(;ch != EOF && !isspace(ch);ch = fetch_char())
            if (len < FLOAT_BUF_MAX-1)
                temp[len++] = ch;
        temp[len] = '\0';
        std::from_chars(temp, temp + len, x);
    }
    inline void read(char &c) { for(c = fetch_char();c != EOF && isspace(c);c = fetch_char()){} }
    inline void read(char *s)
    {
        char ch = fetch_char();
        for(;ch != EOF && isspace(ch);ch = fetch_char()){}
        for(;ch != EOF && !isspace(ch);ch = fetch_char())
            *s++ = ch;
        *s = '\0';
    }
    inline void read(std::string &s,int len=0)
    {
        s.clear();
        s.reserve(len);
        char ch = fetch_char();
        for(;ch != EOF && isspace(ch);ch = fetch_char()){}
        for(;ch != EOF && !isspace(ch);ch = fetch_char())
            s.push_back(ch);
    }
    template <typename T>
    requires std::is_integral_v<T>
    inline void write(T x)
    {
        if (x == 0)
        {
            push('0');
            return;
        }
        if (x < 0)
            push('-');
        static char stack[INT_BUF_MAX]; 
        int top = 0;
        std::make_unsigned_t<T> abs_x = (x < 0) ? -static_cast<std::make_unsigned_t<T>>(x) : x;
        for(;abs_x;abs_x/=10)
            stack[++top] = (abs_x % 10) + '0';
        for(;top;--top)
            push(stack[top]);
    }
    template <typename T>
    requires std::is_floating_point_v<T>
    inline void write(T x)
    {
        if (out_cursor > out_buf + BUF_SIZE - WRITE_MARGIN)
            flush();
        out_cursor = std::to_chars(out_cursor, out_buf + BUF_SIZE, x, std::chars_format::fixed, FLOAT_PRECISION).ptr;
    }
    inline void write(char c) { push(c); }
    inline void write(const char* s) { for(;*s;++s) push(*s); }
} io;
```
# 交互题
需要将原来输出格式
```cpp
cout<<a<<'\n';
```
改为下面这种格式
```cpp
cout<<a<<endl;
```
# 输入到文件末尾
```cpp
while(cin>>n){}
```
# 读取一行数字，数字个数未知
```cpp
string line;
getline(cin, line);
char* p = line.data();
char* end = p + line.size();
while(p < end)
{
    for(;p < end && *p <= ' ';++p){}
    if (p >= end)
        break;
    int val;
    auto [next_p, ec] = from_chars(p, end, val);
    p = const_cast<char*>(next_p);
    // 使用 val...
}
```
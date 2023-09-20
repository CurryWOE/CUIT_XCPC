#! https://zhuanlan.zhihu.com/p/563153071
# 输入输出(input/output)
# C的IO
>这里只讲scanf和printf  
>getchar,putchar,puts等，可以自己查[Cpp Reference](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)

scanf，格式化输入并赋值给变量，其格式如下
```cpp
scanf("%控制符",&变量名);
scanf("%控制符%控制符",&变量名,&变量名);
```
需要记忆常见数据类型对应的控制符

数据类型|控制符|
--|:--:|
int|d|
long long|lld|
char|c|
char*(字符串)|s|
float|f|
double|lf|

一些零散的知识：

%c会输入所有的字符，而其他类型会跳过[space],[enter],[tab]

%3d可以控制数字输入位数为3位，多于这个位数的不会读入

---
printf，格式化输出，其格式如下
```cpp
printf("%控制符",变量名);
printf("%控制符 %控制符",变量名);
```
控制符和输入一样

一些零散的知识：

%-05d

5表示输出位数至少为5位，如果实际位数少于5位，则补上一些字符，默认补空格

0表示补0

-表示左对齐，默认右对齐

\%.2f，控制输出浮点数小数位数为2位，如果实际位数多于2位，则5舍6入

---
# C++的IO
cin，输入，其格式如下
```cpp
cin>>a;
cin>>a>>b;
char s[10];
cin>>(s+1);//cpp17及以前
cin.get(s+1,x)//cpp20及以后，读入至多x个字符
```
不同于C，没有控制符

---
cout，输出，其格式如下
```cpp
cout<<a;
cout<<a<<" "<<b;
cout<<fixed<<setprecision(3)<<c;
cout<<endl;
```
一些零散的知识：

<<fixed<<setprecision(3)表示控制浮点数小数位数为3位， 如果实际位数多于3位，则5舍6入

endl表示清空缓冲区，同时起到换行的作用，不同于printf，cout的结果不会马上看到，要么清空缓冲区才能看到，要么程序结束才能看到

但是endl比较慢，如果不需要立即看到输出，那么换成'\n'

为了加快C++的IO，需要在int main里，最前面加上
```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
cout.tie(nullptr);
```
注意，上面代码加上后，不能再使用C的IO

## C和C++的IO性能比较
在不开O2时，C快，开之后C++快

因为C的scanf和printf在运行期解析字符串(因为涉及到类型转换)

而C++的cin和cout在编译期就已经确定类型

但是C如果用快读快写，那可能比C++快（注意是可能，因为出题人可能卡快读快写）

2023.6.1 UPD:浮点数读写C风格快，其他都是Cpp风格快。大量浮点数读写差距明显。
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
C
```c
while(scanf("%d",&a)!=EOF)
{}
```
C++
```cpp
while(cin>>n)
{}
```
# 快读快写
```cpp
template <typename T>
inline void read(T &x)
{
    T sum = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    x = sum * f;
}
inline void read(double &x)
{
    double z = 0, t = 0;
    int s = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        if (c == '.')
            goto readt;
        c = getchar();
    }
    while (isdigit(c) && c != '.')
    {
        z = z * 10 + c - '0';
        c = getchar();
    }
readt:
    while (c == '.')
        c = getchar();
    while (isdigit(c))
    {
        t = t * 10 + c - '0';
        ++s;
        c = getchar();
    }
    x = (z + t / pow(10, s)) * f;
}
inline void read(string &x)
{
    x = "";
    char ch = getchar();
    while (ch == ' ' || ch == '\n' || ch == '\r')
        ch = getchar();
    while (ch != ' ' && ch != '\n' && ch != '\r')
        x += ch, ch = getchar();
}
inline void readline(string &x)
{
    x = "";
    char ch = getchar();
    while (ch == ' ' || ch == '\n' || ch == '\r')
        ch = getchar();
    while (ch != '\n' && ch != '\r')
        x += ch, ch = getchar();
}
template <typename T, typename... Args>
inline void read(T &t, Args &...args)
{
    read(t);
    read(args...);
}
template <typename T>
inline void write(T x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
inline void write(double x, int k = 6)
{
    ll n = pow(10, k + 1);
    if (x == 0)
    {
        putchar('0'), putchar('.');
        for (int i = 1; i <= k; ++i)
            putchar('0');
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    ll y = (ll)(x * n) % n;
    x = (ll)x;
    write((ll)x), putchar('.');
    int bit[20], p = 0, i;
    if (y % 10 >= 5)
        y = y / 10 + 1;
    else
        y = y / 10;
    for (; p < k; y /= 10)
        bit[++p] = y % 10;
    for (i = p; i > 0; i--)
        putchar(bit[i] + 48);
}
inline void write(string x)
{
    for (int i = 0; x[i] != '\0'; i++)
        putchar(x[i]);
}
template <typename T>
inline void write(const char ch, T x)
{
    write(x);
    putchar(ch);
}
template <typename T, typename... Args>
inline void write(const char ch, T x, Args... args)
{
    write(ch, x);
    write(ch, args...);
}
```
# 读取一行数字，数字个数未知
```cpp
string s;
getline(cin, s);
stringstream ss;
ss << s;
while (ss >> s)
{
    auto res = stoi(s);
}
```
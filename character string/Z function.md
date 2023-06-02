#! https://zhuanlan.zhihu.com/p/625076568
# Z function
Z函数, $z[i]$ 表示, $s$ ,和, $s[i]$ 开头的后缀，的最长公共前缀（LCP），的长度

假设我们已经计算出 $z[i]$ ，求 $z[x]$ ， $x>i$

$s[0,z[i]-1]=s[i,i+z[i]-1]$ ，由定义得（即蓝线）

当 $x\in [i,i+z[i]-1]$，易得 $s[x-i,z[i]-1]=s[x,i+z[i]-1]$ （即红线）

当 $x+z[x-i]-1<i+z[i]-1$

因为 $s[x+z[x-i]]=s[x-i+z[x-i]]$ （第2、3条绿线）且 $s[x-i+z[x-i]]\ne s[z[x-i]]$ （第1、2条绿线）

所以 $s[x+z[x-i]]\ne s[z[x-i]]$，所以 $z[x]=z[x-i]$。

![1](../graph%20for%20md/z%20function1.png)

当 $x-i+z[x-i]-1>=z[i]-1$ ， $z[x]\ge z[i]-x+i$ 。之后不清楚，所以暴力做

![2](../graph%20for%20md/z%20function2.png)

如果 $x>i+z[i]-1$ ，说明之前的信息无法利用，直接暴力做

代码部分把第2、3种情况合并了，并用l表示i，r表示i+z[i]-1
```cpp
char s[N];//0-indexed
int z[N];
void getZ()
{
    int len=strlen(s);
    z[0]=len;
    for(int i=1,l=0,r=0;i<len;++i)
    {
        if(z[i-l]<r-i+1)
            z[i]=z[i-l];
        else
        {
            z[i]=max(0,r-i+1);
            while(i+z[i]<len && s[z[i]]==s[i+z[i]])
                ++z[i];
            l=i,r=i+z[i]-1;
        }
    }
}
```
## 应用
1. 求文本串的后缀与模式串的LCP

设新字符串=模式串+（非字符集内的字符）+文本串，求其z函数，文本串后缀 $[i,n-1]$ 与模式串的LCP为 $z[模式串长度+1+i]$

2. 求字符串的前缀，作为子串出现的次数

求其z函数，如果 z[i] 不等于0，说明长度为 z[i],z[i]-1,...,1 的前缀在此各出现一次，求一个后缀和

3. 相同位数大数比较，预处理Z函数，比较LCP后一位
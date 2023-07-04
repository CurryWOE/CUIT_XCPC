#! https://zhuanlan.zhihu.com/p/625075884
# kmp
border：一个字符串的border是其真子串中，既是前缀又是后缀

部分匹配表PMT：字符串前缀的最长border长度

文本串text string：查找的文本范围

模式串pattern string：需要查找的字符串，通常长度远小于文本串

字符串最小循环节长度=len-PMT[len-1]
```cpp
char txt[N],str[N];//0-Index
int pmt[N];//P[0]~P[i] 这一段字符串，最长border长度
void getpmt()
{
    int len=strlen(str);
    pmt[0]=0;
	for(int i=1,j=0;i<len;++i)
	{
		while(j && str[i]!=str[j])
            j=pmt[j-1];
		if(str[i] == str[j])
            ++j;
		pmt[i] = j;
	}
}
void KMP()
{
    int len1=strlen(txt),len2=strlen(str);
    for(int i=0,j=0;i<len1;++i)
	{
		while(j && txt[i]!=str[j])
            j=pmt[j-1];
		if(txt[i] == str[j])
            ++j;
		if(j == len2)
		{
            //允许重复匹配
			j=pmt[j-1];
            //不允许重复匹配
            j=0;
			cout<<i-len2+1<<"\n";
		}
	}
}
```
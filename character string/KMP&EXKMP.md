# kmp
```cpp
char txt[N],str[N];//0-Index
int pmt[N];//P[0]~P[i] 这一段字符串，使得真前缀等于真后缀的最长长度
void getNext()
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
# EXkmp
```cpp
//EXKMP
#define MAXN 100
char s1[MAXN],s2[MAXN];
int next[MAXN],ex[MAXN];
void Getnext(char *str)
{
    int i=0,j,po,len=strlen(str);
    next[0]=len;
    while(i+1<len && str[i]==str[i+1])
        ++i;
    next[1]=i;
    po=1;
    for(int i=2;i<len;++i)
    {
        if(next[i-po]+i<next[po]+po)
            next[i]=next[i-po];
        else
        {
            j=next[po]+po-i;
            if(j<0)
                j=0;
            while(i+j<len && str[j]==str[i+j])
                ++j;
            next[i]=j;
            po=i;
        }
    }
}
void EXKMP(char *s1,char *s2)
{
    int i=0,j,po,len1=strlen(s1),len2=strlen(s2);
    while(i<len1 && i<len2 && s1[i]==s2[i])
        ++i;
    ex[0]=i;
    po=0;
    for(i=1;i<len1;++i)
    {
        if(next[i-po]+i<ex[po]+po)
            ex[i]=next[i-po];
        else
        {
            j=ex[po]+po-i;
            if(j<0)
                j=0;
            while(i+j<len1 && j<len2 && s1[i+j]==s2[j])
                ++j;
            ex[i]=j;
            po=i;
        }
    }
}
```
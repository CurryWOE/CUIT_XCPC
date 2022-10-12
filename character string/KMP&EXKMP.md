# kmp
```cpp
char txt[N],str[N];//字符串都从1开始
int nxt[N];//P[0]~P[x-1] 这一段字符串，使得前缀等于后缀的最长长度
void getNext()
{
    int i=2,j=0,len=strlen(str+1);
	for(;i<=len;++i)
	{
		while(j && str[i]!=str[j+1])
            j=nxt[j];
		if(str[i] == str[j+1])
            ++j;
		nxt[i] = j; 
	}
}
void KMP()
{
    int i=1,j=0,len1=strlen(txt+1),len2=strlen(str+1);
    for(;i<=len1;++i)
	{
		while(j && txt[i]!=str[j+1])
            j=nxt[j];
		if(txt[i] == str[j+1])
            ++j;
		if(j == len2-1)
		{
			j=nxt[j];
			cout<<i-len2+2<<"\n";
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
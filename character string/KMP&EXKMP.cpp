int next[MAXN];//P[0]~P[x-1] 这一段字符串，使得k-前缀恰等于k-后缀的最大的k
void getNext(char *p,int *next)
{
    next[0]=-1;
    int i=0,j=-1,p_len=strlen(p);
    while(i<p_len)
    {
        if(j==-1 || p[i]==p[j])
        {
            ++i;
            ++j;
            next[i]=j;
        }
        else
            j=next[j];
    }
}
int KMP(char *t,char *p)
{
    int i=0,j=0,t_len=strlen(t),p_len=strlen(p);
    while(i<t_len && j<p_len)
    {
        if(j==-1 || t[i]==p[j])
        {
            ++i;
            ++j;
        }
        else
            j=next[j];
    }
    if(j==p_len)
        return i-j;
    return -1;
}
//返回第一次出现的下标，如果没出现，返回-1
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
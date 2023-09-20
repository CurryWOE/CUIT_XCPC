# Manacher
计算以位置i为中心的最长回文串半径，半径为i到回文串最右端包含的字符数
```cpp
int r[N*2];
void manacher(string s)
{
    string t="@#";//插入"#"，表示原字符串中的空
    //为了避免处理边界，首尾加上不和字符串内字符匹配的字符
    for(auto &c:s)
    {
        t+=c;
        t+="#";
    }
    t+="$";
    int n=t.size()-1;
    for(int i=1,mid,R=0;i<n;++i)
    {
        r[i]=R>i ? min(r[(mid<<1)-i],r[mid]+mid-i) : 1;
        for(;t[i+r[i]]==t[i-r[i]];++r[i]);
        if(R<i+r[i])
            R=r[i]+i,mid=i;
    }
    for(int i=1;i<n;++i)
        --r[i];
}
```
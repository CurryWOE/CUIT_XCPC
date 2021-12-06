string Mannacher(string s)
{
    //插入"#"
    string t="$#";
    for(int i=0;i<s.size();++i)
    {
        t+=s[i];
        t+="#";
    }
    vector<int> p(t.size(),0);
    //mx表示某个回文串延伸在最右端半径的下标，id表示这个回文子串最中间位置下标
    //resLen表示对应在s中的最大子回文串的半径，resCenter表示最大子回文串的中间位置
    int mx=0,id=0,resLen=0,resCenter=0;
     //建立p数组
    for(int i=1;i<t.size();++i)
    {
        p[i]=mx>i ? min(p[2*id-i],mx-i) : 1;
        //遇到三种特殊的情况，需要利用中心扩展法
        while(t[i+p[i]]==t[i-p[i]])
            ++p[i];
        //半径下标i+p[i]超过边界mx，需要更新
        if(mx<i+p[i])
        {
            mx=i+p[i];
            id=i;
        }
        //更新最大回文子串的信息，半径及中间位置
        if(resLen<p[i])
        {
            resLen=p[i];
            resCenter=i;
        }
    }
    //最长回文子串长度为半径-1，起始位置为中间位置减去半径再除以2
    return s.substr((resCenter-resLen)/2,resLen-1);
}
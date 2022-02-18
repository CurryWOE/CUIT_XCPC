//把字符串string散列成ull类型
typedef unsigned long long ull;
const int MAXN=1e6+1;
const int seed=13331;
//种子，要求是1个质数
ull h[MAXN],p[MAXN];
//散列表，seed的幂
string s;
int slen;
cin>>s;
s="6"+s;
//为了方便处理
slen=s.length();
for(int i=1;i<slen;++i)
    h[i]=h[i-1]*seed+s[i]-'A'+1;
p[0]=1;
for(int i=1;i<=slen;++i)
    p[i]=p[i-1]*seed;
//预处理
hashvalue=h[r]-h[l-1]*p[len];
//s[l,r]子串的散列值
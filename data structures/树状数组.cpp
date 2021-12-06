//1.单点更新、单点查询
//传统数组可做
//2.单点更新、区间查询
int n,m;
int a[50005],c[50005]; //对应原数组和树状数组
inline int lowbit(int x)
{
    return x&(-x);
} 
void updata(int i,int k)//在i位置加上k
{    
    for(;i <= n;i+=lowbit(i));
        c[i] += k;
} 
int getsum(int i)//求A[1 - i]的和
{        
    int res = 0;
    for(;i > 0;i-=lowbit(i))
        res += c[i];
    return res;
}
int main()//HDU-1166
{
    int t;
    cin>>t;
    for(int tot = 1; tot <= t; tot++)
    {
        cout << "Case " << tot << ":" << endl;
        memset(a, 0, sizeof a);
        memset(c, 0, sizeof c);
        cin>>n;
        for(int i = 1; i <= n; i++)
        {
            cin>>a[i];
            updata(i,a[i]);   //输入初值的时候，也相当于更新了值
        }
        string s;
        int x,y;
        while(cin>>s && s[0] != 'E')
        {
            cin>>x>>y;
            if(s[0] == 'Q') //求和操作
            {   
                int sum = getsum(y) - getsum(x-1);    //x-y区间和也就等于1-y区间和减去1-(x-1)区间和
                cout << sum << endl;
            }
            else if(s[0] == 'A')
                updata(x,y);
            else if(s[0] == 'S')//减去操作，即为加上相反数
                updata(x,-y);    
        }
    }
    return 0;
}
//3.区间更新、单点查询
/*用差分建树
假设我们规定A[0] = 0;
             i
则有 A[i] = Σ    D[j];(D[j] = A[j] - A[j-1])，即前面i项的差值和，这个有什么用呢？例如对于下面这个数组
             j=1
A[] = 1 2 3 5 6 9
D[] = 1 1 1 2 1 3
如果我们把[2,5]区间内值加上2，则变成了
A[] = 1 4 5 7 8 9
D[] = 1 3 1 2 1 1
发现了没有，当某个区间[x,y]值改变了，区间内的差值是不变的，只有D[x]和D[y+1]的值发生改变
所以我们就可以利用这个性质对D[]数组建立树状数组*/
int n,m;
int a[50005] = {0},c[50005]; //对应原数组和树状数组
int lowbit(int x)
{
    return x&(-x);
}
void update(int i,int k)
{    //在i位置加上k
    for(;i <= n;i+=lowbit(i))
        c[i] += k;
}
int getsum(int i)
{        //求D[1 - i]的和，即A[i]值
    int res = 0;
    for(;i > 0;i-=lowbit(i))
        res += c[i];
    return res;
}
int main()
{
    cin>>n;
    for(int i = 1; i <= n; i++)
    {
        cin>>a[i];
        updata(i,a[i] - a[i-1]);   //输入初值的时候，也相当于更新了值
    } 
    //[x,y]区间内加上k
    update(x,k);    //A[x] - A[x-1]增加k
    update(y+1,-k);        //A[y+1] - A[y]减少k  
    //查询i位置的值
    int sum = getsum(i);
    return 0;
}
//4.区间更新、区间查询
/*用差分建树
 n           n    i
∑    A[i] = ∑    ∑    D[j];
 i=1         i=1  j=1
则A[1]+A[2]+...+A[n]
= (D[1]) + (D[1]+D[2]) + ... + (D[1]+D[2]+...+D[n]) 
= n*D[1] + (n-1)*D[2] +... +D[n]
= n * (D[1]+D[2]+...+D[n]) - (0*D[1]+1*D[2]+...+(n-1)*D[n])
                n             n            n
所以上式可以变为∑    A[i] = n*∑    D[i] - ∑    ( D[i]*(i-1) );
                i=1           i=1          i=1
维护两个数状数组，sum1[i] = D[i]，sum2[i] = D[i]*(i-1);*/
int n,m;
int a[50005] = {0};
int sum1[50005];    //(D[1] + D[2] + ... + D[n])
int sum2[50005];    //(1*D[1] + 2*D[2] + ... + n*D[n])
int lowbit(int x)
{
    return x&(-x);
} 
void updata(int i,int k)
{
    int x = i;    //因为x不变，所以得先保存i值
    while(i <= n)
    {
        sum1[i] += k;
        sum2[i] += k * (x-1);
        i += lowbit(i);
    }
}
int getsum(int i)
{        //求前缀和
    int res = 0, x = i;
    while(i > 0)
    {
        res += x * sum1[i] - sum2[i];
        i -= lowbit(i);
    }
    return res;
}
int main()
{
    cin>>n;
    for(int i = 1; i <= n; i++)
    {
        cin>>a[i];
        updata(i,a[i] - a[i-1]);   //输入初值的时候，也相当于更新了值
    }
    //[x,y]区间内加上k
    updata(x,k);    //A[x] - A[x-1]增加k
    updata(y+1,-k);        //A[y+1] - A[y]减少k
    //求[x,y]区间和
    int sum = getsum(y) - getsum(x-1);
    return 0;
}
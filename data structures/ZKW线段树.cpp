//定义
#define maxn 100007
int A[maxn],n,N;//原数组,n为原数组元素个数 ,N为扩充元素个数 
int Sum[maxn<<2];//区间和 
int Lazytag[maxn<<2];//懒惰标记
//建树
void Build(int n)
{
	//计算N的值 
	N=1;
    while(N < n+2) 
        N <<= 1;
	//更新叶节点 
	for(int i=1;i<=n;++i) 
        Sum[N+i]=A[i];//原数组下标+N=存储下标
	//更新非叶节点 
	for(int i=N-1;i>0;--i)
    {
		//更新所有非叶节点的统计信息 
		Sum[i]=Sum[i<<1]+Sum[i<<1|1];
		//清空所有非叶节点的Add标记 
		Add[i]=0;
	}
}
//点修改
void Update(int L,int C)
{
	for(int s=N+L;s;s>>=1)
		Sum[s]+=C;
}
//点修改下的区间查询
int Query(int L,int R)
{
	int ANS=0;
	for(int s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1)
    {
		if(~s&1)
            ANS+=Sum[s^1];
		if( t&1)
            ANS+=Sum[t^1];
	}
	return ANS;
}
//)区间修改
void Update(int L,int R,int C)
{
	int s,t,Ln=0,Rn=0,x=1;
	//Ln:  s一路走来已经包含了几个数
	//Rn:  t一路走来已经包含了几个数
	//x:   本层每个节点包含几个数
	for(s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1,x<<=1)
    {
		//更新Sum
		Sum[s]+=C*Ln;
		Sum[t]+=C*Rn;
		//处理Add
		if(~s&1) 
            Add[s^1]+=C,Sum[s^1]+=C*x,Ln+=x;
		if( t&1) 
            Add[t^1]+=C,Sum[t^1]+=C*x,Rn+=x;
	}
	//更新上层Sum
	for(;s;s>>=1,t>>=1)
    {
		Sum[s]+=C*Ln;
		Sum[t]+=C*Rn;
	} 
}
//区间修改下的区间查询
int Query(int L,int R)
{
	int s,t,Ln=0,Rn=0,x=1;
	int ANS=0;
	for(s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1,x<<=1)
    {
		//根据标记更新 
        ANS+=Add[s]*Ln+Add[t]*Rn;
		//常规求和 
		if(~s&1) 
            ANS+=Sum[s^1],Ln+=x;
		if( t&1) 
            ANS+=Sum[t^1],Rn+=x; 
	}
	//处理上层标记
	for(;s;s>>=1,t>>=1)
		ANS+=Add[s]*Ln+Add[t]*Rn;
	return ANS;
}
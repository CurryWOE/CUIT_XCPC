int dp[W];
int weight[N],value[N];
memset(dp,0,sizeof(dp));
for(int j=0;j<n;j++)
    cin>>weight[j];
for(int j=0;j<n;j++)
    cin>>value[j];
for(int i=0;i<n;++i)
{
    for(int j=W;j>=weight[i];--j)
        dp[j]=max(dp[j],dp[j-weight[i]]+value[i]);
}
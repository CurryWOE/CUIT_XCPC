/* 求解最长子序列的个数的核心代码 */LIS
int k = 1;
dp[k] = arr[0];
for(int i=1;i<n;i++)
{
    if(dp[k]<arr[i]) dp[++k] = arr[i]; 
    else *(lower_bound(dp + 1, dp + 1 + k, arr[i])) = arr[i]; 
}
//k是答案
//如果比最后一个元素大，那么就添加再最后末尾处
//如果比最后一个元素小，那么就替换该序列第一个比他大的数
//最长公共子序列   LCS
f[0][0] = 0;
for(int i=1;i<=N;i++) 
{
    for(int j=1;j<=M;j++) 
    {
        if(a[i] == b[j]) 
            f[i][j] = f[i-1][j-1] + 1;
        else 
            f[i][j] = max(f[i-1][j],f[i][j-1]);
    }
}
ans = f[N][M];
LIS可以排序后用LCS做
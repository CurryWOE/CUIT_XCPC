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
using ll = long long;
using P = pair<int,int>;
using Graph = vector<vector<int>>;
using mint = modint998244353;
 
int main()
{
  int n;
  cin >> n;
  vector<P> p(n);
  rep(i, 0, n) cin >> p[i].first;
  rep(i, 0, n) cin >> p[i].second;
  sort(p.begin(), p.end());
  int maxi = 5000;
  vector<mint> dp(maxi + 1, 1);
  mint ans = 0;
  rep(i, 0, n)
  {
    auto [a, b] = p[i];
    if (a >= b) ans += dp[a - b];
    for (int j = maxi - b; j >= 0; j--)
      dp[j + b] += dp[j];
  }
  cout << ans.val() << endl;
  return 0;
}
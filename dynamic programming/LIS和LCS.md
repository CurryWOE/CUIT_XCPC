#! https://zhuanlan.zhihu.com/p/557880407

# LIS\&LCS

# 最长上升子序列 LIS
ans[i] 表示长度 $i+1$ 的 LIS 的末尾最小元素

$O(nlogn)$
```cpp
int lis(const vector<int>& arr)
{
    vector<int> ans{arr[0]};
    ans.reserve(arr.size());
    for (int i = 1; i < arr.size(); ++i)
    {
        if (ans.back() < arr[i])
            ans.push_back(arr[i]);
        else
            *(upper_bound(ans.begin(), ans.end(), arr[i])) = arr[i];
    }
    return ans.size();
}
```
# 最长公共子序列 LCS
ans[i][j] 表示a的前i个元素，b的前j个元素，的LCS

$O(nm)$
```cpp
int lcs(vector<int> a,vector<int> b)//a,b均为1-indexed，这样方便实现
{
    vector<vector<int>> ans(a.size(),vector<int>(b.size(),0));
    for(int i=1;i<a.size();++i)
        for(int j=1;j<b.size();++j)
            ans[i][j]=(a[i]==b[j]?ans[i-1][j-1]+1:max(ans[i-1][j],ans[i][j-1]));
    return ans[a.size()-1][b.size()-1];
}
```
## 特殊情况的优化
如果a和b均有的数字，在a和b里都只出现一次，可以将a做一个映射，f[a[i]]=i，b做一个映射，g[i]=f[b[i]]，这样LCS就变成了g的LIS

解释一下为什么可以转换：

1. 如果a[y]==b[x]（假设1）  
  那么f[a[y]]==f[b[x]]（推论1）
2. 因为f[a[y]]==y（定义）和推论1  
  所以f[b[x]]==y（推论2）
3. 因为g[x]==f[b[x]]（定义）和推论2  
  所以g[x]==y（推论3）
4. 因为推论3  
  所以a[g[x]]==a[y]（推论4）
5. 因为a[y]==b[x]（假设1）和推论4  
  所以a[g[x]]==b[x]（推论5）  
6. 如果不是a和b公有的数字，不满足LCS定义，因此它们不参与计算不影响答案
7. 所以剔除非公有数字后，任意x，推论5都满足
8. 如果i上升（假设2）  
  那么b[i]是b的子序列（推论6）
9. 如果g[i]上升（假设3）  
  那么a[g[i]]是a的子序列（推论7）
10. 如果假设2和假设3都满足，且根据推论5  
  那么g的上升子序列（i，g[i]）能表示a和b的公共子序列
11. 所以g的LIS能表示a和b的LCS

$O(nlogn)$
```cpp
int lcs(const vector<int>& a,const vector<int>& b)
{
    unordered_map<int, int> f;
    for(int i=0;i<a.size();++i)
        f[a[i]]=i;
    vector<int> ans;
    for(int i=0;i<b.size();++i)
    {
        auto it = f.find(b[i]);
        if(it==f.end())
            continue;
        int g=it->second;
        if(ans.empty() || ans.back()<g)
            ans.push_back(g);
        else
            *(upper_bound(ans.begin(), ans.end(), g)) = g;
    }
    return ans.size();
}
```

queue<int>q;
int in[MAXN];
vector<int>edge[n];
for(int i=0;i<n;i++)  //n  节点的总数
    if(in[i]==0) q.push(i);  //将入度为0的点入队列
bool tpsort()
{
    int cnt=0,p;
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        ++cnt;
        for(auto u:e[p])
        {
            if(--in[u]==0)
                q.push(u);
        }
    }
    return cnt==n;
}
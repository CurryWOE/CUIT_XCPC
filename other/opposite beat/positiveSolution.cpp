#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,f0,f1,f2;
    // freopen("data.txt","r",stdin);
    scanf("%d",&n);
    f0=1;
    f1=1;
    if(n<2)
        printf("1");
    else
    {
        for(;n>=2;--n)
        {
            f2=f0+f1;
            f0=f1;
            f1=f2;
        }
        printf("%d",f2);
    }
    return 0;
}
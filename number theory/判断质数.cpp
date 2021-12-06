/*
试除法：
判断素数
时间复杂度O(sqrt(n))
*/
int isprime(int i)
{
    if((i&1)==0 && i!=2 || i<2)
        return 0;
    int sq=sqrt(i),k;
    for(k=3;k<=sq;k+=2)
    {
        if(i%k==0)
            return 0;
    }
    return 1;
}
/*
拉宾米勒等其他判断大数是否是素数的算法：
施工中
*/
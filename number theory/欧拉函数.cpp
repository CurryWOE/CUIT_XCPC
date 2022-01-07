/*性质1：质数p,φ(p^n)=(p-1)*p^(n-1)
质因数分解，x=p1^a1 * …… * pk^ak
φ(x)=p1^(a1-1)*(a1-1) * …… * pk^(ak-1)*(ak-1)
=x*(a1-1)/a1 * …… *(ak-1)/ak
时间复杂度O(sqrt(n))
*/
int phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            res = res / i * (i - 1); // 先除再乘防止溢出
        while (n % i == 0)
            n /= i;
    }
    if (n > 1)
        res = res / n * (n - 1);
    return res;
}
//筛求法见线性筛part 2，用到readme提到的3个性质
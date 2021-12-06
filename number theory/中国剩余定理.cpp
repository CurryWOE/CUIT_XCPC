/*
中国剩余定理CRT（Chinese remainder theorem)
时间复杂度O(nlog n)
求解如下形式的一元线性同余方程组（其中ni两两互质）：
x=a1(mod n1)
x=a2(mod n2)
.
.
.
x=ak(mod nk)
算法流程
1.计算所有模数的积n
2.对于第i个方程：
    a.计算mi=n/ni;
    b.计算mi在模ni意义下的逆元mi^-1;
    c.计算ci=mi*mi^-1(不要对ni取模)
                    k
3.方程组的唯一解为x= Σ    ai*ci(mod n)
                   i=1
*/
/*
证明：
证明 x = ai (mod ni)
      k
mj =( ∏  ni) / nj
     i=1
∏为求积符号，Σ为求和符号
所以当 i ≠ j 时，mj = 0 (mod ni)
①cj = mj = 0 (mod ni)
②ci = mi * mi^-1
    = 1 (mod ni)
 k
 Σ  ai*ci = t*n+x
i=1

 k
 Σ  ai*ci = 0 + x (mod ni)
i=1

    k
x = Σ  aj*cj   (mod ni)
   j=1
  = ai * ci  (mod ni)  由①得
  = ai     (mod ni)  由②得
*/
long long CRT(int number,long long* remainder,long long* modulus) 
{
    long long m,x,y,product = 1, ans = 0;
    for (int i = 1; i <= number; i++) 
        product = product * modulus[i];
    for (int i = 1; i <= number; i++)
    {
        m = product / modulus[i];
        exgcd(m, modulus[i], x, y);
        ans = (ans + remainder[i] * m * x % product) % product;
    }
    return (ans % product + product) % product;
}
/*
模数不互质的情况
两个方程
设两个方程分别是 x=a1 (mod m1),x=a2(mod m2)
将它们转化为不定方程：x=m1*p+a1=m2*q+a2
其中p,q是整数,则有m1*p-m2*q=a2-a1
由裴蜀定理，当a2-a1不能被gcd(m1,m2) 整除时，无解
其他情况下，可以通过扩展欧几里得算法解出来一组可行解(p,q)
则原来的两方程组成的模方程组的解为x=b(mod M)
其中b=m1*p+a1,M=lcm(m1,m2)
多个方程
用上面的方法两两合并即可
*/
long long CRT(int number,long long* remainder,long long* modulus)
{
    long long lcm = modulus[1],sum = remainder[1],x,y,gcd;
    int fail = 0;
    for(int i = 2;i <= number;++i)
    {
        remainder[i] = ((remainder[i] - sum) % modulus[i] + modulus[i]) % modulus[i];
        gcd = exgcd(lcm,modulus[i],x,y);
        if(remainder[i] % gcd == 0)
            x = x * (remainder[i] / gcd) % modulus[i];
        else
        {
            fail = 1;
            break;
        }
        sum += x * lcm;
        lcm = lcm / gcd * modulus[i];
        sum = (sum % lcm + lcm) % lcm;
    }
    return fail ? -1 : sum;
}
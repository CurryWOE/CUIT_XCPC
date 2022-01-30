# CRT
中国剩余定理（Chinese remainder theorem)

## 时间复杂度
$O(nlog n)$

求解如下形式的一元线性同余方程组

$x\equiv a_1 \pmod {n_1}$

$x\equiv a_2 \pmod {n_2}$

.

.

.

$x\equiv a_k \pmod {n_k}$

## 限制条件
$n_i$两两互质

## 算法流程

1. 计算所有模数的积 $n=\prod\limits_{i=1}^k n_i$
   
2. 对于第 $i$ 个方程：
   
    a. 计算 $m_i=n/n_i$ ;

    b. 计算 $m_i$ 在模 $n_i$ 意义下的逆元 $m_i^{-1}$;

    c. 计算 $c_i=m_i*m_i^{-1}$ (不要对 $n_i$ 取模)


3. 方程组的唯一解为 $x=\sum\limits_{i=1}^k a_i*c_i \pmod n$

```c++
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
```

# excrt
解决模数不互质的情况

设两个方程分别是 

$x=a_1 \pmod {n_1}$

$x=a_2 \pmod {n_2}$

将它们转化为不定方程：

$x=n_1*p+a_1=n_2*q+a_2$

其中 $p$ , $q$ 是整数,则有 $n_1*p-n_2*q=a_2-a_1$

由裴蜀定理，当 $a_2-a_1$ 不能被 $gcd(n1,n2)$ 整除时，无解

其他情况下，可以通过扩展欧几里得算法解出来一组可行解$(p,q)$

则原来的两方程组成的模方程组的解为

$x=n_1*p+a_1 \pmod {lcm(m1,m2)}$

多个方程,用上面的方法两两合并即可

```c++
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
```
$\sum\limits_{i=1}^n i=n(n+1)/2$

$\sum\limits_{i=1}^n i^2=n(n+1)(2n+1)/6$

$\sum\limits_{i=1}^n i^3=n^2(n+1)^2/4$

$\sum\limits_{i=1}^n i^4=n(n+1)(6n^3+9n^2+n-1)/30$

$\sum\limits_{i=1}^n i^5=n^2(n+1)(2n^3+4n^2+n-1)/12$

# 递推式推导
设 $f_n^p=\sum\limits_{i=1}^n i^{p}$

$(n+1)^p-n^p=C_p^1n^{p-1}+C_p^2n^{p-2}+...+1$

$\sum\limits_{n=1}^m(n+1)^p-n^p=\sum\limits_{n=1}^mC_p^1n^{p-1}+C_p^2n^{p-2}+...+1$

$(m+1)^p-1=C_p^1f_m^{p-1}+C_p^2f_m^{p-2}+...+m$

$f_m^{p-1}=((m+1)^p-1-(C_p^2f_m^{p-2}+...+m))/C_p^1$

$f_m^{p}=((m+1)^{p+1}-1-(C_{p+1}^2f_m^{p-1}+...+m))/(p+1)$
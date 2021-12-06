//快读
inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while(c < '0' || c > '9') 
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
//快写
inline void write(int n)
{
	if (n < 0)
	{
		putchar('-');
		n *= -1;
	}
	if (n > 9)
	{
		write(n / 10);
	}
	putchar(n % 10 + '0');
}
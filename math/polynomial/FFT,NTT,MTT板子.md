```cpp
// #define mod998244353
// #define ntt_prime_mod
// #define prime_mod
// #define arbitrary_mod
#define none_mod
// #define use_mtt
// #define dynamic_mod
const int LIM = 1 << 21;
// 2 val define:
// use_mtt/no define(fft)
// 2 modulus define(dynamic/static):
// dynamic_mod/no define(static_mod)
// 5 modulus define(feature):
// 1.mod998244353(ntt)
// 2.ntt_prime_mod(ntt)
// 3.prime_mod(mtt/fft)
// 4.arbitrary_mod(mtt/fft)
// 5,none_mod(mtt/fft)
namespace poly
{
    const int SZL = LIM | 5;
    using T = int;
    using cT = const T;
#ifdef mod998244353
    const int mod = 998244353;
#elif defined(dynamic_mod)
    T mod;
#elif !defined(none_mod)
    const T mod = ::mod;
#endif
#ifdef dynamic_mod
    using ull = unsigned long long;
    using u128 = __uint128_t;
    struct FastMod
    {
        ull b, m;
        FastMod(ull b = 2) : b(b), m(ull((u128(1) << 64) / b)) {}
        inline ull R(ull x)
        {
            ull q = ull(u128(m) * x >> 64), r = x - q * b;
            return r >= b ? r - b : r;
        }
    } M;
    inline T mul(cT x, cT y) { return M.R(1ull * x * y); }
    inline void Mul(T &x, cT y) { x = M.R(1ull * x * y); }
#elif !defined(none_mod)
    inline T mul(cT x, cT y)
    {
        return 1ll * x * y % mod;
    }
    inline void Mul(T &x, cT y) { x = 1ll * x * y % mod; }
#endif
#ifndef none_mod
    inline T inc(cT x, cT y)
    {
        return x + y < mod ? x + y : x + y - mod;
    }
    inline T dec(cT x, cT y) { return x >= y ? x - y : x - y + mod; }
    inline void Inc(T &x, cT y) { ((x += y) <= mod) && (x -= mod); }
    inline void Dec(T &x, cT y) { ((x -= y) < 0) && (x += mod); }
    inline T pow(T x, T y)
    {
        T res = 1;
        for (; y; y >>= 1, Mul(x, x))
            (y & 1) && (Mul(res, x), 1);
        return res;
    }
    inline T Inv(cT x) { return pow(x, mod - 2); }
#endif
#ifdef mod998244353
    const int G = 3, iG = 332748118;
#elif defined(ntt_prime_mod)
    T G, iG;
#endif
    inline void Minit(
#ifdef dynamic_mod
        T MOD
#endif
    )
    {
#ifdef dynamic_mod
        mod = MOD;
        M = FastMod(mod);
#endif
#ifdef ntt_prime_mod
        static T fc[105] = {0}, cnt = 0;
        cT phi = mod - 1;
        for (T i = 2, x = phi; 1ll * i * i <= x; ++i)
            if (!(x % i))
            {
                fc[++cnt] = x;
                for (; x % i == 0; x /= i)
                    ;
            }
        for (G = 2;; ++G)
        {
            if (pow(G, phi) ^ 1)
                continue;
            bool fl = 1;
            for (int i = 1; i <= cnt && fl; ++i)
                fl &= (pow(G, phi / fc[i]) ^ 1);
            if (fl)
                break;
        }
        iG = Inv(G);
#endif
    }
#if defined(ntt_prime_mod) || defined(mod998244353)
    T pool[SZL << 3], *cur = pool;
    T _pl[SZL << 1], *igp[25];
    using Z = T;
    inline void init(const int N)
    {
        T *cr = _pl;
        for (int i = 1, ct = 0; i < N; i <<= 1, ++ct)
        {
            igp[ct] = cr;
            cr += i;
            igp[ct][0] = 1;
            if (i > 1)
                igp[ct][1] = pow(iG, (mod - 1) / (i << 1));
            for (int j = 2; j < i; ++j)
                Mul(igp[ct][j] = igp[ct][j - 1], igp[ct][1]);
        }
    }
    inline void NTT(T *f, const int N)
    {
        if (N == 1)
            return;
        for (int i = N >> 1, ct = __builtin_ctz(i); i >= 2; i >>= 2, ct -= 2)
        {
            const int o = i >> 1;
            for (int j = 0; j < N; j += (i << 1))
            {
                T *f0 = f + j, *f1 = f0 + o, *f2 = f1 + o, *f3 = f2 + o;
                const int *w0 = igp[ct], *w1 = w0 + o, *w2 = igp[ct - 1];
                for (int k = 0; k < o; ++k)
                {
                    cT A = inc(*f0, *f2), B = mul(*w0++, dec(*f0, *f2));
                    cT C = inc(*f1, *f3), D = mul(*w1++, dec(*f1, *f3));
                    *f0++ = inc(A, C);
                    *f2++ = inc(B, D);
                    *f1++ = mul(*w2, dec(A, C));
                    *f3++ = mul(*w2, dec(B, D));
                    ++w2;
                }
            }
        }
        if (!(__builtin_ctz(N >> 1) & 1))
        {
            for (int j = 0; j < N; j += 2)
            {
                T &f0 = f[j], &f1 = f[j + 1];
                cT A = inc(f0, f1), B = dec(f0, f1);
                f0 = A;
                f1 = B;
            }
        }
    }
    inline void INTT(T *f, const int N)
    {
        if (N == 1)
            return;
        for (int i = 1, ct = 0; i << 1 < N; i <<= 2, ct += 2)
        {
            for (int j = 0; j < N; j += (i << 2))
            {
                T *f0 = f + j, *f1 = f0 + i, *f2 = f1 + i, *f3 = f2 + i;
                const int *w0 = igp[ct], *w1 = igp[ct + 1], *w2 = w1 + i;
                for (int k = 0; k < i; ++k)
                {
                    cT v0 = mul(*w0, *f1), v1 = mul(*w0, *f3);
                    ++w0;
                    cT A = inc(*f0, v0), B = dec(*f0, v0);
                    cT C = mul(*w1++, inc(*f2, v1)), D = mul(*w2++, dec(*f2, v1));
                    *f0++ = inc(A, C);
                    *f1++ = inc(B, D);
                    *f2++ = dec(A, C);
                    *f3++ = dec(B, D);
                }
            }
        }
        if (!(__builtin_ctz(N >> 1) & 1))
        {
            const int *w = igp[__builtin_ctz(N >> 1)];
            for (int j = 0; j < N >> 1; ++j)
            {
                T &f0 = f[j], &f1 = f[j + (N >> 1)];
                cT A = f0, B = mul(*w++, f1);
                f0 = inc(A, B);
                f1 = dec(A, B);
            }
        }
        std::reverse(f + 1, f + N);
        cT iN = Inv(N);
        for (int i = 0; i < N; ++i)
            Mul(f[i], iN);
    }
    inline void Gconv(cT *const f, const int n, cT *const g, const int m, T *h)
    {
        int N = 1;
        const int Len = n + m - 1;
        for (; N < Len; N <<= 1)
            ;
        init(N);
        T *A, *B;
        A = cur;
        cur += N;
        B = cur;
        cur += N;
        for (int i = 0; i < N; ++i)
            A[i] = B[i] = 0;
        for (int i = 0; i < n; ++i)
            A[i] = f[i];
        for (int i = 0; i < m; ++i)
            B[i] = g[i];
        NTT(A, N);
        NTT(B, N);
        for (int i = 0; i < N; ++i)
            Mul(A[i], B[i]);
        INTT(A, N);
        for (int i = 0; i < Len; ++i)
            h[i] = A[i];
        cur -= N;
        cur -= N;
    }
#else
    using db = double;
    using cdb = const db;
    struct cpl
    {
        db x, y;
        cpl() = default;
        cpl(cdb X, cdb Y) : x(X), y(Y) {}
        inline cpl operator+(const cpl &rhs) const { return cpl(x + rhs.x, y + rhs.y); }
        inline cpl operator-(const cpl &rhs) const { return cpl(x - rhs.x, y - rhs.y); }
        inline cpl operator*(const cpl &rhs) const { return cpl(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
        inline cpl operator*=(const cpl &rhs) { return *this = *this * rhs; }
    };
    using Z = cpl;
    using cZ = const Z;
    Z _pl[SZL << 1], *igp[25];
    constexpr db pi = acos(-1);
    Z pool[SZL << 3], *cur = pool;
    inline void init(const int N)
    {
        Z *cr = _pl;
        for (int i = 1, ct = 0; i < N; i <<= 1, ++ct)
        {
            igp[ct] = cr;
            cr += i;
            igp[ct][0] = cpl(1, 0);
            for (int j = 1; j < i; ++j)
                igp[ct][j] = cpl(cos(pi * j / i), -sin(pi * j / i));
        }
    }
    inline void DFT(Z *f, const int N)
    {
        if (N == 1)
            return;
        for (int i = N >> 1, ct = __builtin_ctz(i); i >= 2; i >>= 2, ct -= 2)
        {
            const int o = i >> 1;
            for (int j = 0; j < N; j += (i << 1))
            {
                Z *f0 = f + j, *f1 = f0 + o, *f2 = f1 + o, *f3 = f2 + o;
                cZ *w0 = igp[ct], *w1 = w0 + o, *w2 = igp[ct - 1];
                for (int k = 0; k < o; ++k)
                {
                    cZ A = *f0 + *f2, B = *w0++ * (*f0 - *f2), C = *f1 + *f3, D = *w1++ * (*f1 - *f3);
                    *f0++ = A + C;
                    *f2++ = B + D;
                    *f1++ = *w2 * (A - C);
                    *f3++ = *w2 * (B - D);
                    ++w2;
                }
            }
        }
        if (!(__builtin_ctz(N >> 1) & 1))
        {
            for (int j = 0; j < N; j += 2)
            {
                Z &f0 = f[j], &f1 = f[j + 1];
                cZ A = f0 + f1, B = f0 - f1;
                f0 = A;
                f1 = B;
            }
        }
    }
    inline void IDFT(Z *f, const int N)
    {
        if (N == 1)
            return;
        for (int i = 1, ct = 0; i << 1 < N; i <<= 2, ct += 2)
        {
            for (int j = 0; j < N; j += (i << 2))
            {
                Z *f0 = f + j, *f1 = f0 + i, *f2 = f1 + i, *f3 = f2 + i;
                cZ *w0 = igp[ct], *w1 = igp[ct + 1], *w2 = w1 + i;
                for (int k = 0; k < i; ++k)
                {
                    cZ v0 = *w0 * *f1, v1 = *w0 * *f3;
                    ++w0;
                    cZ A = *f0 + v0, B = *f0 - v0, C = *w1++ * (*f2 + v1), D = *w2++ * (*f2 - v1);
                    *f0++ = A + C;
                    *f1++ = B + D;
                    *f2++ = A - C;
                    *f3++ = B - D;
                }
            }
        }
        if (!(__builtin_ctz(N >> 1) & 1))
        {
            cZ *w = igp[__builtin_ctz(N >> 1)];
            for (int j = 0; j < N >> 1; ++j)
            {
                Z &f0 = f[j], &f1 = f[j + (N >> 1)];
                cZ A = f0, B = *w++ * f1;
                f0 = A + B;
                f1 = A - B;
            }
        }
        std::reverse(f + 1, f + N);
        for (int i = 0; i < N; ++i)
            f[i].x /= N, f[i].y /= N;
    }
#ifdef use_mtt
    const int Bl = 65535, lgB = 16, lgB2 = 32;
    inline T _to_range(cdb x)
    {
        return ((ll)(x + 0.5))
#ifndef none_mod
               % mod
#endif
            ;
    }
    inline void Gconv(cT *const f, const int n, cT *const g, const int m, T *h)
    {
        int N = 1;
        const int Len = n + m - 1;
        for (; N < Len; N <<= 1)
            ;
        init(N);
        Z *A, *B, *T;
        A = cur;
        cur += N;
        B = cur;
        cur += N;
        T = cur;
        cur += N;
        for (int i = 0; i < N; ++i)
            A[i] = B[i] = T[i] = cpl(0, 0);
        for (int i = 0; i < n; ++i)
            A[i].x = f[i] & Bl, B[i].x = f[i] >> lgB;
        for (int i = 0; i < m; ++i)
            T[i] = cpl(g[i] & Bl, g[i] >> lgB);
        DFT(A, N);
        DFT(B, N);
        DFT(T, N);
        for (int i = 0; i < N; ++i)
            A[i] *= T[i], B[i] *= T[i];
        IDFT(A, N);
        IDFT(B, N);
        for (int i = 0; i < Len; ++i)
            h[i] = (_to_range(A[i].x) + (1ll * (_to_range(A[i].y) + _to_range(B[i].x)) << lgB) + (1ll * _to_range(B[i].y) << lgB2))
#ifndef none_mod
                   % mod
#endif
                ;
        cur -= N;
        cur -= N;
        cur -= N;
    }
#else
    inline void Gconv(cT *const f, const int n, cT *const g, const int m, T *h)
    {
        int N = 1;
        const int Len = n + m - 1;
        for (; N < Len; N <<= 1)
            ;
        init(N);
        Z *A;
        A = cur;
        cur += N;
        for (int i = 0; i < N; ++i)
            A[i] = cpl(0, 0);
        for (int i = 0; i < n; ++i)
            A[i].x = f[i];
        for (int i = 0; i < m; ++i)
            A[i].y = g[i];
        DFT(A, N);
        for (int i = 0; i < N; ++i)
            A[i] *= A[i];
        IDFT(A, N);
        cur -= N;
#ifdef none_mod
        for (int i = 0; i < Len; ++i)
            h[i] = (A[i].y + 0.5) / 2;
#elif defined(dynamic_mod)
        for (int i = 0; i < Len; ++i)
            h[i] = M.R((A[i].y + 0.5) / 2ull);
#else
        for (int i = 0; i < Len; ++i)
            h[i] = ((A[i].y + 0.5) / 2) % mod;
#endif
    }
#endif
#endif
}
```
## 常见原根
r * 2^k + 1 (mod)	r	k (模数大小规模)	原根  
7681	15	9	17  
65537	1	16	3  
998244353	119	23	3  
1004535809	479	21	3  
75161927681	35	31	3  
206158430209	3	36	22  
180143985094819841	5	55	6  
1945555039024054273	27	56	5  
4179340454199820289	29	57	3  
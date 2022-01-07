//---------------------------------------------------//
template <typename T>inline void read(T& x){
    T sum = 0, f = 1;
    char c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {sum=sum*10+c-'0';c=getchar();}
    x=sum*f;
}

inline void read(double &x){
    double z=0,t=0;int s=0,f=1;char c=getchar();
    while (!isdigit(c)) {if (c=='-') f=-1; if(c=='.') goto readt; c=getchar();}
    while (isdigit(c)&&c!='.') {z=z*10+c-'0';c=getchar();}
    readt:while (c=='.') c=getchar();  
    while (isdigit(c)) {t=t*10+c-'0';++s; c=getchar();}
    x=(z+t/pow(10,s))*f;
}

inline void read(string& x){
    x="";
    char ch=getchar();
    while(ch==' ' || ch=='\n' || ch=='\r')ch=getchar(); 
    while(ch!=' ' && ch!='\n' && ch!='\r') x+=ch,ch=getchar();
}

inline void readline(string& x){
    x="";
    char ch=getchar();
    while(ch==' ' || ch=='\n' || ch=='\r')ch=getchar(); 
    while(ch!='\n' && ch!='\r') x+=ch,ch=getchar();
}

template <typename T,typename... Args> inline void read(T& t, Args&... args){
    read(t);read(args...);
}

template<typename T> inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

inline void write(double x,int k=6){
    ll n=pow(10,k + 1);
    if (x==0) {putchar('0'),putchar('.');for (int i=1;i<=k;++i) putchar('0');return;}
    if (x<0) putchar('-'),x=-x;
    ll y=(ll)(x*n)%n;x=(ll)x;
    write((ll)x),putchar('.');
    int bit[20], p=0,i;
    if(y % 10 >= 5) y = y/10+1;
    else y = y/10;
    for (;p<k;y/=10) bit[++p]=y%10;
    for (i=p;i>0;i--) putchar(bit[i]+48);
}

inline void write(string x){
    for(int i=0; x[i]!='\0'; i++) putchar(x[i]);
}

template <typename T> inline void write(const char ch, T x){
    write(x);putchar(ch);
}

template <typename T, typename... Args> inline void write(const char ch, T x, Args... args){
    write(ch, x);
    write(ch, args...);
}
//_____________________________________________________//
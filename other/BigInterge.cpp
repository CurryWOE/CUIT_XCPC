//This file provides four operation for big-intgers
//You can use class 'BigN' to define a variable.
//Follow operators are available
//+ - * / % = += -= *= /= %= > < >= <= == !=
//these operators can used between BigN and BigN or BigN and int.

//You can use function print() to print a BigN to stdout.
//printn() will print a '\n' at the end.
//Function getstr() and str() will return a std::string-type string.

//IN SAFE MODE, you can access k-th digit, from 0-th high digits, by [].
//Or you can also modify x-th digit by modify(x,y).

//In this template, multipy operator is implicated by fast_Fourier_transform,
//Which can calculate convolution of to n-vectors in O(nlogn) time.
//When number is small, this code still use O(n^2) algorithm.
//and divide operator is implicated by dichotomy.

//-O2 or -O3 optimize option is recomended.

//**********************************************************************//
//If you delete the follow definition,the calc speed will improve
//but when number become huge, especially over 2000000 digits,
//it may NOT work correctly.
//So, to make sure that you answer is correct, do NOT delete this line.

    //#define SAFE_CALC_MODE

//**********************************************************************//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <complex>

const double _pi=acos(-1);

class _fast_Fourier_transform
{
    typedef std::complex<double> Cmplx;
    typedef std::vector<Cmplx>    E;
    typedef std::vector<int> Vec;
    private:
    int _n,_m,_N;
    Vec R;

    //butterfly operation
    inline void    Expand(int temp)
    {
        int    L=0; for(_N=1;_N<=temp;_N<<=1,L++);
        R.resize(_N+1);
        for(int i=0;i<_N;++i) R[i]=R[i>>1]>>1|(i&1)<<(L-1);
        return ;
    }

    //Fast Fourier Transform
    void    FFT(E& A,int f)
    {
        for(int i=0;i<_N;++i) if(i<R[i]) swap(A[i],A[R[i]]);
        for(int i=1;i<_N;i<<=1)
        {
            Cmplx wn(cos(_pi/i),f*sin(_pi/i));
            for(int j=0;j<_N;j+=i<<1)
            {
                Cmplx w(1,0);
                for(int k=0;k<i;++k,w*=wn)
                {
                    Cmplx x=A[j+k],y=w*A[i+j+k];
                    A[j+k]=x+y; A[i+j+k]=x-y;
                }
            }
        } return ;
    }

    inline Vec Mul(E& A,E& B)
    {
        Expand(_n+_m); A.resize(_N+1); B.resize(_N+1);
        FFT(A,1); FFT(B,1);//DFT
        for(int i=0;i<=_N;++i) A[i]*=B[i];//MUL
        FFT(A,-1);//IDFT
        std::vector<int> vec;
        for(int i=0;i<_n+_m-1;++i)
            vec.push_back((int)(A[i].real()/_N+0.5));
                    //fix deviation
        return vec;
    }



    public:
    inline Vec multi(Vec& AA,Vec& BB)
    {
        E A,B;
        _n=AA.size(); _m=BB.size();
        //turn two vectors to complex
        A.resize(_n); B.resize(_m);
        for(int i=0;i<_n;++i) A[i]=AA[i];
        for(int i=0;i<_m;++i) B[i]=BB[i];
        return Mul(A,B);
    }
};

class    _normal_mul
{
    //O(n^2) multiply
    typedef std::vector<int> Vec;
    private:
    inline Vec mul(Vec& A,Vec& B)
    {
        Vec vec; int _n,_m;
        _n=(int)A.size(),_m=(int)B.size();
        vec.resize(_n+_m);
        for(int i=0;i<_n;++i) for(int j=0;j<_m;++j)
            vec[i+j]+=A[i]*B[j];
        return vec;
    }
    public:
    inline Vec multi(Vec& AA,Vec& BB) { return mul(AA,BB); }
};

#ifndef SAFE_CALC_MODE
#define DIGITS 1000
#else
#define DIGITS 10
#endif

class Divide_By_Zero_Error { };

class _data_container_of_BigN
{
    private:
    bool sym;//0 positive,1 negetive
    unsigned int length;//total length of the number
    std::vector<int> vec;//vector of data

    public:
    typedef _data_container_of_BigN _this_class;
    inline void    _set_zero()
        { sym=0; length=1; vec.clear(); vec.push_back(0); }
    _data_container_of_BigN() { _set_zero();}
    _data_container_of_BigN(int x)
    {
        //turn int to BigN
        _set_zero();
        if(x) vec.pop_back();
        if(x<0) sym=true,x=-x;
        while(x)
        {
            vec.push_back(x%DIGITS);
            x/=DIGITS;
        }
        update_length();
    }
    _data_container_of_BigN(const char* str)
    {
        int    _n=strlen(str),data=0,base=1,t=0;
        vec.clear(); if(str[0]=='-') sym=true,t=1;
        for(int i=_n-1; i>=t; --i)
        {
            data=data+(str[i]-48)*base;
#ifndef SAFE_CALC_MODE
            if((_n-i)%3==0)
#endif
            {
                vec.push_back(data),data=0,base=1;
                continue;
            }
            base*=10;
        }
        vec.push_back(data);
        update_length();
    }

    inline _this_class operator=(const char* str)
    {
        //turn char* to BigN
        int    _n=strlen(str),data=0,base=1,t=0;
        vec.clear(); if(str[0]=='-') sym=true,t=1;
        for(int i=_n-1; i>=t; --i)
        {
            data=data+(str[i]-48)*base;
#ifndef SAFE_CALC_MODE
            if((_n-i)%3==0)
#endif
            {
                vec.push_back(data),data=0,base=1;
                continue;
            }
            base*=10;
        }
        vec.push_back(data);
        update_length();
        return *this;
    }

    inline _this_class operator =(int x)
    {
        //turn int to BigN
        _set_zero();
        if(x) vec.pop_back();
        if(x<0) sym=true,x=-x;
        while(x)
        {
            vec.push_back(x%DIGITS);
            x/=DIGITS;
        }
        update_length();
        return *this;
    }

    inline _this_class operator -()
    {
        _this_class C=*this;
        C.sym=!C.sym;
        return C;
    }


    inline int&    operator[](int x) { return vec[x]; }

    inline bool    is_positive() { return !sym; }
    inline bool    is_negetive() { return sym; }

    //Fix -0 to 0
    inline void    fix_zero()
    { if(sym && length==1 && vec[0]==0) sym=!sym; }

    //get k-th digit
    inline int    getkth(const int x)
    {
        if(x>=(int)length) return -1;
        return vec[length-x-1];
    }
    //Modify
    inline bool    modify(const int x,const int y)
    {
        if(x>=(int)length) return false;
        vec[length-x-1]=y; update_length(); return true;
    }


    inline _this_class operator+(_this_class& B)
    {
        if(!sym && !B.sym) return positive_add(B);
        if(sym && B.sym) return -positive_add(B);
        if(sym && !B.sym)
        {
            if(compare_abs(B)>0) return -positive_minus(B);
            return B.positive_minus(*this);
        }
        if(compare_abs(B)>0) return positive_minus(B);
        return -B.positive_minus(*this);
    }

    inline _this_class operator-(_this_class& B)
    {
        if(!sym && !B.sym)
        {
            if(compare_abs(B)>0) return positive_minus(B);
            return -B.positive_minus(*this);
        }
        if(sym && B.sym)
        {
            if(compare_abs(B)>0) return -positive_minus(B);
            return B.positive_minus(*this);
        }
        if(!sym && B.sym) return positive_add(B);
        return -B.positive_add(*this);
    }

    inline _this_class operator*(_this_class& B)
    {
        return sym^B.sym?-positive_muliply(B):
            positive_muliply(B);
    }

    inline _this_class operator/(_this_class& B)
    {
        try
        {
            return sym^B.sym?-positive_divide(B):
            positive_divide(B);
        }catch(...)
        {
            std::cerr << std::endl;
            std::cerr << "\tError: Division is 0." << std::endl;
        }
        return B;
    }

    inline _this_class operator%(_this_class& B)
    {
        try
        {
            return sym^B.sym?-positive_mod(B):
            positive_mod(B);
        }catch(...)
        {
            std::cerr << std::endl;
            std::cerr << "\tError: Division is 0." << std::endl;
        }
        return *this;
    }

    inline _this_class operator+(int B){ _this_class t=B; return *this+t; }
    inline _this_class operator-(int B){ _this_class t=B; return *this-t; }
    inline _this_class operator*(int B){ _this_class t=B; return *this*t; }
    inline _this_class operator/(int B){ _this_class t=B; return *this/t; }
    inline _this_class operator%(int B){ _this_class t=B; return *this%t; }

    inline _this_class operator+=(_this_class& B) { return *this=*this+B; }
    inline _this_class operator-=(_this_class& B) { return *this=*this-B; }
    inline _this_class operator*=(_this_class& B) { return *this=*this*B; }
    inline _this_class operator/=(_this_class& B) { return *this=*this/B; }
    inline _this_class operator%=(_this_class& B) { return *this=*this%B; }
    inline _this_class operator+=(int B) { return *this=*this+B; }
    inline _this_class operator-=(int B) { return *this=*this-B; }
    inline _this_class operator*=(int B) { return *this=*this*B; }
    inline _this_class operator/=(int B) { return *this=*this/B; }
    inline _this_class operator%=(int B) { return *this=*this%B; }

    //Print func will print the number to stdout in casual format
    void    print()
    {
        if(is_negetive()) printf("-");
#ifdef SAFE_CALC_MODE
        for(int i=vec.size()-1;i>=0;--i)
            printf("%d",vec[i]);
#else
        printf("%d",vec[vec.size()-1]);
        for(int i=vec.size()-2;i>=0;--i)
            printf("%03d",vec[i]);
#endif
        return ;
    }
    //Print func will print the number to 'str' in casual format
    void    print_to_str(std::string& str)
    {
        str="";
        char tempstr[4];
        if(is_negetive()) str="-";
#ifdef SAFE_CALC_MODE
        for(int i=vec.size()-1;i>=0;--i)
            sprintf(tempstr,"%d",vec[i]),
                str+=tempstr;
#else
        sprintf(tempstr,"%d",vec[vec.size()-1]);
        str+=tempstr;
        for(int i=vec.size()-2;i>=0;--i)
            sprintf(tempstr,"%03d",vec[i]),
                str+=tempstr;
#endif
        return ;
    }

    inline unsigned int size() { return vec.size(); }

    /*
        *     this func
        *     returns 1 if *this>B
        *     returns -1 if *this<B
        *     return 0 if *this==B
    */
    inline int    compare_abs(_this_class& B)
    {
        if(length>B.length) return 1;
        if(length<B.length) return -1;
        for(int i=vec.size()-1;i>=0;--i)
            if(vec[i]>B[i])return 1;
            else if(vec[i]<B[i]) return -1;
        return 0;
    }

    protected:

    inline void    clear_zero()
    //This func deletes leading zero
    {
        while(!vec[vec.size()-1] && vec.size()!=1)
            vec.pop_back();
        return ;
    }

    /***************************************************************/
    //CALL THIS FUNCTION AFTER EVERY OPERATION TO MAKE ANSWER CORRECT
#ifndef SAFE_CALC_MODE
    inline void    update_length()
    //fixup length and leading zero
    {
        clear_zero();
        if(vec.size()==1 && vec[0]==0) length=1;
        else if(vec[vec.size()-1]/100)length=vec.size()*3;
        else if(vec[vec.size()-1]/10)length=vec.size()*3-1;
        else length=vec.size()*3-2;
        return ;
    }
#else
    //fixup length and leading zero
    inline void    update_length()
    {
        clear_zero();
        length=vec.size(); return ;
    }
#endif
    /***************************************************************/

    //carry the vec
    //notice: call update_length() after calling this func
    inline void    Go_up()
    {
        int t=vec.size();
        for(int i=0;i<t-1;++i)
        {
            vec[i+1]+=vec[i]/DIGITS;
            vec[i]%=DIGITS;
        }
        while(vec[t-1]>=DIGITS)
            vec.push_back(vec[t-1]/DIGITS),vec[t-1]%=DIGITS,t++;
        return ;
    }

    //resize the vector
    inline void    resize(int x) { vec.resize(x); }

    inline int    get_quotient(_this_class& R,_this_class& B,
            _this_class* Map)
    //This func get a quotient for divide operator by dichotomy
    {
        if(R.compare_abs(B)<0) return 0;
        int l=0,r=DIGITS,mid;
        while(l<r-1)
        {
            mid=l+((r-l)>>1);
            if(mid && Map[mid].size()==1 && Map[mid][0]==0)
                Map[mid]=B*mid;
            int t=R.compare_abs(Map[mid]);
            if(t>0)l=mid;
            else if(t<0)r=mid;
            else { l=mid; break; }
        }
        if(mid && Map[l].size()==1 && Map[l][0]==0) Map[l]=B*l;
        R=R-Map[l];
        return l;
    }


    private:

    inline _this_class positive_add(_this_class& B)
    //This func returns Abs(*this)+Abs(B)
    //calling this func must garantee '*this' and 'B' are both positive
    {
        _this_class C;//ans
        bool _Longer_vec;

        if(vec.size()>B.size())    _Longer_vec=1;
        else            _Longer_vec=0;

        //if B is shorter
        if(_Longer_vec)
        {
            C.resize(vec.size()+1);
            //add shorter digits first
            for(int i=0;i<(int)B.size();++i)
            {
                C[i+1]=(C[i]+vec[i]+B[i])/DIGITS;
                C[i]=(C[i]+vec[i]+B[i])%DIGITS;
            }//each saves 3 digits

            //calc rest digits
            for(int i=B.size();i<(int)vec.size();++i)
            {
                C[i+1]=(C[i]+vec[i])/DIGITS;
                C[i]=(C[i]+vec[i])%DIGITS;
            }
        }
        //if B is longer
        else
        {
            C.resize(B.size()+1);
            //add shorter digits first
            for(int i=0;i<(int)vec.size();++i)
            {
                C[i+1]=(C[i]+vec[i]+B[i])/DIGITS;
                C[i]=(C[i]+vec[i]+B[i])%DIGITS;
            }//each saves 3 digits

            //calc rest digits
            for(int i=vec.size();i<(int)B.size();++i)
            {
                C[i+1]=(C[i]+B[i])/DIGITS;
                C[i]=(C[i]+B[i])%DIGITS;
            }
        }
        C.update_length();
        return C;
    }

    inline _this_class positive_minus(_this_class& B)
    //This func returns Abs(*this)-Abs(B)
    //calling this func must garantee '*this > B'
    {
        _this_class C;//ans
        C.resize(vec.size());
        //calc first B.size() digits
        for(int i=0;i<(int)B.size();++i)
        {
            if(vec[i]+C[i]<B[i])C[i]+=DIGITS+vec[i]-B[i],C[i+1]--;
            else C[i]+=vec[i]-B[i];
        }
        //copy the rest digits
        for(int i=B.size();i<(int)vec.size();++i)
            C[i]+=vec[i];
        C.update_length();
        return C;
    }

    inline _this_class positive_muliply(_this_class& B)
    //This func returns Abs(*this)*Abs(B)
    {
        _this_class C=*this;

        double temp=log(vec.size()+B.size())/log(2);

        if((vec.size()+B.size())*temp<vec.size()*B.size())
        //Using fast Fourier transform if (n+m)log(n+m)<n*m
        //to speed mul operation when data become huge
        {
            _fast_Fourier_transform F;
            C.vec=F.multi(C.vec,B.vec);
        }
        else
        //Using normal O(n*m) algorithm when n,m is small
        {
            _normal_mul F;
            if(vec.size()<B.size())C.vec=F.multi(C.vec,B.vec);
            else C.vec=F.multi(B.vec,C.vec);
        }

        C.Go_up();
        C.update_length();
        return C;
    }

    inline _this_class positive_divide(_this_class& B)
    //This func returns Abs(*this)/Abs(B)
    {
        if(B.length==1 && B.vec[0]==0) throw Divide_By_Zero_Error();
        _this_class C;
        _this_class r;//Remainder

        _this_class Map[DIGITS+2];
        //save B*x to save time.

        //if dividend is less return 0
        if(compare_abs(B)<0) return C;

        //if dividend is equal to divisor return 1
        if(compare_abs(B)==0) { C[0]=1; return C; }

        C.resize(vec.size());
        r.resize(B.size());
        for(int i=B.size()-2;i>=0;--i)
            r[i]=vec[vec.size()-B.size()+1+i];
        r.update_length();

        for(int i=vec.size()-B.size();i>=0;--i)
        {
            r*=DIGITS; r[0]+=vec[i]; r.update_length();
            //dichotomy
            int t=get_quotient(r,B,Map);
            C[i]=t;
        }
        C.update_length();
        return C;
    }

    inline _this_class positive_mod(_this_class& B)
    //This func returns Abs(*this)%Abs(B)
    {
        if(B.length==1 && B.vec[0]==0) throw Divide_By_Zero_Error();
        _this_class r;//Remainder

        _this_class Map[DIGITS+2];
        //save B*x to save time.

        //if dividend is less return vec
        if(compare_abs(B)<0) return *this;

        //if dividend is equal to divisor return 1
        if(compare_abs(B)==0) return r;

        r.resize(B.size());
        for(int i=B.size()-2;i>=0;--i)
            r[i]=vec[vec.size()-B.size()+1+i];
        r.update_length();

        for(int i=vec.size()-B.size();i>=0;--i)
        {
            r*=DIGITS; r[0]+=vec[i]; r.update_length();
            //dichotomy
            get_quotient(r,B,Map);
        }
        return r;
    }
};

//Use This Class in your program.
class BigN
{
    public:
#ifdef    SAFE_CALC_MODE
    //You may NOT modify the digits directly.
    //if number has NO x-th number, function will return -1
    inline int    operator[](const int x) { return _data.getkth(x); }
    //This Func change x-th digit to y.(start from 0th,high digit)
    //Returns false for failure, true for success.
    inline bool    modify(const int x,const int y)
    { return _data.modify(x,y); }
#endif

    //Fix -0 to 0
    inline void    Fix_zero() { _data.fix_zero(); }

    inline BigN    operator = (const int B)
    { _data=B; Fix_zero(); return *this;}
    inline BigN    operator = (const char* B)
    { _data=B; Fix_zero(); return *this;}

    inline BigN    operator + (BigN B)
    { B._data=_data+B._data; B.Fix_zero(); return B; }
    inline BigN    operator - (BigN B)
    { B._data=_data-B._data; B.Fix_zero(); return B; }
    inline BigN    operator * (BigN B)
    { B._data=_data*B._data; B.Fix_zero(); return B; }
    inline BigN    operator / (BigN B)
    { B._data=_data/B._data; B.Fix_zero(); return B; }
    inline BigN    operator % (BigN B)
    { B._data=_data%B._data; B.Fix_zero(); return B; }
    inline BigN    operator + (int B)
    { BigN C=B; C._data=_data+C._data; C.Fix_zero(); return C; }
    inline BigN    operator - (int B)
    { BigN C=B; C._data=_data-C._data; C.Fix_zero(); return C; }
    inline BigN    operator * (int B)
    { BigN C=B; C._data=_data*C._data; C.Fix_zero(); return C; }
    inline BigN    operator / (int B)
    { BigN C=B; C._data=_data/C._data; C.Fix_zero(); return C; }
    inline BigN    operator % (int B)
     { BigN C=B; C._data=_data%C._data; C.Fix_zero(); return C; }
    inline BigN operator+=(BigN B)
    { _data+=B._data; Fix_zero(); return *this; }
    inline BigN operator-=(BigN B)
    { _data-=B._data; Fix_zero(); return *this; }
    inline BigN operator*=(BigN B)
    { _data*=B._data; Fix_zero(); return *this; }
    inline BigN operator/=(BigN B)
    { _data/=B._data; Fix_zero(); return *this; }
    inline BigN operator%=(BigN B)
    { _data%=B._data; Fix_zero(); return *this; }
    inline BigN operator+=(int B)
    { _data+=B; Fix_zero(); return *this; }
    inline BigN operator-=(int B)
    { _data-=B; Fix_zero(); return *this; }
    inline BigN operator*=(int B)
    { _data*=B; Fix_zero(); return *this; }
    inline BigN operator/=(int B)
    { _data/=B; Fix_zero(); return *this; }
    inline BigN operator%=(int B)
    { _data%=B; Fix_zero(); return *this; }

    inline bool    operator < (BigN B)
    {
        if(_data.is_positive() && B._data.is_positive())
            return _data.compare_abs(B._data)<0;
        if(_data.is_negetive() && B._data.is_negetive())
            return _data.compare_abs(B._data)>0;
        if(_data.is_positive() && B._data.is_negetive()) return false;
        return true;
    }
    inline bool    operator > (BigN B)
    {
        if(_data.is_positive() && B._data.is_positive())
            return _data.compare_abs(B._data)>0;
        if(_data.is_negetive() && B._data.is_negetive())
            return _data.compare_abs(B._data)<0;
        if(_data.is_positive() && B._data.is_negetive()) return true;
        return false;
    }
    inline bool    operator == (BigN B)
    {
        if(_data.is_positive()!=B._data.is_positive()) return 0;
        else return _data.compare_abs(B._data)==0;
    }
    inline bool    operator <= (BigN B) { return *this<B || *this==B; }
    inline bool    operator >= (BigN B) { return *this>B || *this==B; }
    inline bool    operator != (BigN B) { return !(*this==B); }

    inline bool    operator < (int B) { return *this<(BigN)B; }
    inline bool    operator > (int B) { return *this>(BigN)B; }
    inline bool    operator <= (int B) { return *this<=(BigN)B; }
    inline bool    operator >= (int B) { return *this>=(BigN)B; }
    inline bool    operator != (int B) { return *this!=(BigN)B; }
    inline bool    operator == (int B) { return *this==(BigN)B; }


    inline void    print() { _data.print(); }
    inline void    printn() { _data.print(); printf("\n"); }


    //These two functions both return std::string-type of the number.
    //If it is the first time you try to get the string after an operation,
    //you should use getstr(), for function str() will return the old
    //string.
    //Each time you call getstr(), the string will up-to-date.
    //And you can use str(), after calling getstr() to save time.
    inline std::string getstr(){ _data.print_to_str(_Str); return _Str; }
    inline std::string str() { return _Str; }

    protected:
    std::string _Str;
    inline void    refresh_str() { _data.print_to_str(_Str); }

    private:
    //this class contains real data and does the exact calculation
    typedef _data_container_of_BigN _data_class;
    _data_class _data;
    public:
    BigN() {}
    BigN(const int x) { _data=x; }
    BigN(const char* x) { _data=x; }
};

BigN operator + (int A,BigN B) { return B+A; }
BigN operator * (int A,BigN B) { return B*A; }

/***************************************************************************/

char     a[1100000],b[1100000];

int main()
{
    scanf("%s%s",a,b);
    BigN x=a,y=b,T;
    printf("a+b="); (x+y).printn();
    printf("a-b="); (x-y).printn();
    printf("a*b="); (x*y).printn();
    printf("a/b="); (x/y).printn();
    printf("a%%b="); (x%y).printn();
    printf("a*1000+b="); (T=x*1000+y).printn();
    printf("2nd digit=%c\n",T.getstr().c_str()[2]);

    //These operation need definition of SAFE_CALC_MODE in line 33

    //T.modify(3,9);
    //printf("after modify 3rd digit to 9="); T.printn();
    //printf("3rd digit=");printf("%d\n",T[3]);
    //printf("after unavailable operatorion="); T.modify(100,9);
    //T.printn();
    //printf("unavailable access="); printf("%d\n",T[100]);

    /*****************************************************/
    //      Input:                                       //
    //              123 45                               //
    //      Output:                                      //
    //              a+b=168                              //
    //              a-b=78                               //
    //              a*b=5535                             //
    //              a/b=2                                //
    //              a%b=33                               //
    //              a*1000+b=123045                      //
    //              2nd digit=3                          //
    //              after modify 3rd digit to 9=123945   //
    //              3rd digit=9                          //
    //              after unavailable operatorion=123945 //
    //              unavailable access=-1                //
    /*****************************************************/
    return 0;
}
# bitset
```cpp
//整数，string和char数组可以强制类型转换成bitset
//不支持迭代器
//类似string，可以存入unordered_set/map，可以用cin/cout输入输出
//转化为整数时0为最低位，转化为字符串时顺序与原先顺序相同，输出时从高位到低位输出

bitset<N>b;//定义初始值全为0的bitset，N为整型常量
bitset<N>b(x);//用无符号整型x初始化bitset，不超过unsigned long long范围
bitset<N>b(s);//用s初始化b，s可以是basic_string类型或bitset类型，若为basic_string类型则s中只能包含'0'或'1'
bitset<N>b(s,p);//用s从p位置开始到末尾初始化b，此处s只能为basic_string类型，下同
bitset<N>b(s,p,n);//用s从p开始的n个数初始化b，p和n都是整数

b=b2,b==b2,b!=b2;//b赋值为b2，b与b2是否相等，是否不等
b&b2,b|b2,b^b2,b<<n,b>>n,~b;//位运算，返回bitset类型
b&=b2,b|=b2,b^=b2,b<<=n,b>>=n;//位运算赋值

b[p],b.test(p);//下标访问。test会检查越界抛出异常，但返回为右值不能修改
b.flip(p),b.set(p),b.set(p,x),b.reset(p);//取反第p位，第p位设为1，第p位设为x，第p位设为0，O(1)
b.flip(),b.set(),b.reset();//所有位取反，所有位设为1，所有位设为0，O(n/w)
b.to_ulong(),b.to_ullong();//分别返回unsigned long和unsigned long long类型，表示将bitset转为整数，to_ullong需要C++11
b.to_string();//bitset转字符串
b.size(),b.any(),b.none(),b.all();//b的大小，是否存在1，是否全为0，是否全为1，all需要C++11，复杂度均为O(1)
b.count();//b中1的个数，O(n/w)
b._Find_first(),b._Find_next(p);//返回b中第一个1的位置，返回b中p以后不含p第一个1的位置，若不存在返回b的大小，O(n/w)
```
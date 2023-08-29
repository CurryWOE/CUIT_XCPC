构造函数是 $O(n)$，比空队列插入 $O(nlogn)$ 好
```cpp
int myints[]= {10,60,50,20};
std::priority_queue<int> second (myints,myints+4);
```
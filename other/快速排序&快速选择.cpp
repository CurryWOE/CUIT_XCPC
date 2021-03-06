void Quicksort(int a[], int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int first = low;
	int last = high;
	int key = a[first];
	while (first<last)
	{
		while (first < last && a[last] >= key)
		{
			--last;
		}
		a[first] = a[last];
		while (first < last && a[first] <= key)
		{
			++first;
		}
		a[last] = a[first];
	}
	a[first] = key;
	Quicksort(a, low, first - 1);
	Quicksort(a, last + 1, high);
}
#include<stdlib.h>
int cmp(const void *a, const void *b) 
{ 
    return(*(int *)a-*(int *)b);  //升序 
    return(*(int *)b-*(int *)a); //降序 
}
qsort(s,n,sizeof(s[0]),cmp);
//s数组名或开始排序的首地址，n被排序的元素个数
int cmp(const void * a, const void * b)
{ 
     return((*(double*)a-*(double*)b>0)?1:-1);
}
/*这里做个注释，本来是因为要判断如果a==b返回0的，
但是严格来说，两个double数是不可能相等的，
只能说fabs(a-b)<1e-6之类的这样来判断，所以这里只返回了1和-1*/
//求第K个最大的元素
int findKthLargest(vector<int>& v, int k)
{
    srand(time(NULL));
    return findKthLargest(v,0,v.size()-1,k);
}
int findKthLargest(vector<int>& v,int l,int r,int k)
{
    int index=partition(v,l,r);
    if(index+1==k) return v[index];
    else if(index+1>k) return findKthLargest(v,l,index-1,k);
    else return findKthLargest(v,index+1,r,k);
}
int partition(vector<int>& v,int l,int r)
{
    swap(v[l],v[rand()%(r-l+1)+l]);
    int first=l,last=l+1;
    for(;last<=r;++last)
    {
        if(v[last]>v[l])
            swap(v[++first],v[last]);
    }
    swap(v[first],v[l]);
    return first;
}
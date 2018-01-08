// A[]已排序
// [x,y)
// 在已经排序的数组里找v
int bsearch(int A[],int x,int y,int v)
{
	int m;
	while(x<y)
	{
		m = x+(y-x)/2;
		if(A[m] == v)
		{
			return m;
		}
		else if(A[m] > v)
		{
			y = m;
		}
		else
		{
			x = m+1;
		}
	}
	return -1;
}

//如果数组中有多个v 能不能求出v的完整区间?

//当v存在 返回它出现的第一个位置 
//如果不存在 返回这样一个下标 在此处插入v (原来的A[i] A[i+1]..全部后移一个位置) 后端序列仍然有序
int lower_bound(int A[],int x,int y,int v)
{
	int m;
	while(x<y)
	{
		m = x + (y-x)/2;
		if(A[m] >= v)
		{
			y = m;
		}
		else
		{
			x = m+1;
		}
	}
	return x;
}

//当v存在 返回它出现的最后一个位置的 后面一个位置
//如果不存在 返回这样一个下标 在此处插入v (原来的A[i] A[i+1]..全部后移一个位置) 后端序列仍然有序
int upper_bound(int A[],int x,int y,int v)
{
	int m;
	while(x<y)
	{
		m = x + (y-x)/2;
		if(A[m] <= v)
		{
			x = m+1;
		}
		else
		{
			y = m;
		}
	}
	return x;
}

//设lower_bound返回L, upper_bound返回R
//则v出现的子序列为 [L,R)
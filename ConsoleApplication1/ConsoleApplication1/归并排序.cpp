//A[] [x,y) T temp
void merge_sort(int* A,int x,int y,int* T)
{
	if(y-x > 1)
	{
		int m = x + (y-x)/2;//划分
		int p = x;
		int q = m;
		int i = x;
		merge_sort(A,x,m,T);//递归求解[x,m)
		merge_sort(A,m,y,T);//递归求解[m,y)
		while(p<m || q<y)//只要一个序列非空 就要继续合并
		{
			if(q>=y || (p<m && A[p] <= A[q]))//1.如果第二个序列为空(此时第一个序列一定非空) 2.第二个序列非空 当且仅当第一个序列也非空 且A[p]<=A[q]
				T[i++] = A[p++];//从左半数组 复制到临时空间
			else
				T[i++] = A[q++];//从右半数组 复制到临时空间
		}
		for(i=x;i<y;i++)
			A[i] = T[i];//从辅助空间 复制回A数组
	}
}
//A[] [x,y) T temp
void merge_sort(int* A,int x,int y,int* T)
{
	if(y-x > 1)
	{
		int m = x + (y-x)/2;//����
		int p = x;
		int q = m;
		int i = x;
		merge_sort(A,x,m,T);//�ݹ����[x,m)
		merge_sort(A,m,y,T);//�ݹ����[m,y)
		while(p<m || q<y)//ֻҪһ�����зǿ� ��Ҫ�����ϲ�
		{
			if(q>=y || (p<m && A[p] <= A[q]))//1.����ڶ�������Ϊ��(��ʱ��һ������һ���ǿ�) 2.�ڶ������зǿ� ���ҽ�����һ������Ҳ�ǿ� ��A[p]<=A[q]
				T[i++] = A[p++];//��������� ���Ƶ���ʱ�ռ�
			else
				T[i++] = A[q++];//���Ұ����� ���Ƶ���ʱ�ռ�
		}
		for(i=x;i<y;i++)
			A[i] = T[i];//�Ӹ����ռ� ���ƻ�A����
	}
}
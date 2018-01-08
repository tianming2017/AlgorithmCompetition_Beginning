// A[]������
// [x,y)
// ���Ѿ��������������v
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

//����������ж��v �ܲ������v����������?

//��v���� ���������ֵĵ�һ��λ�� 
//��������� ��������һ���±� �ڴ˴�����v (ԭ����A[i] A[i+1]..ȫ������һ��λ��) ���������Ȼ����
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

//��v���� ���������ֵ����һ��λ�õ� ����һ��λ��
//��������� ��������һ���±� �ڴ˴�����v (ԭ����A[i] A[i+1]..ȫ������һ��λ��) ���������Ȼ����
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

//��lower_bound����L, upper_bound����R
//��v���ֵ�������Ϊ [L,R)
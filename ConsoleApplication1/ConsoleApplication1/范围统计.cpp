//��Χͳ��
//����N������Xi m��ѯ�� ����ÿ��ѯ��(a,b) ���������[a,b]������xi�ĸ���
//xi >= a ��a�״γ��ֵ�λ��
//xi <= b ��b�����ֵ�λ��
#include<iostream>
#include<algorithm>
using namespace std;
int v[10000];
int main()
{
	int n,m,a,b;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	sort(v,v+n);
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;//[a,b]
		cout << upper_bound(v,v+n,b) - lower_bound(v,v+n,a) << endl;
		//(���һ�γ���b��λ��+1) - (�״γ���a��λ��)
		//xi [a,b] �״γ���a��λ��  �� ���һ�γ���b��λ�� �м�ĸ���
	}
	getchar();
	getchar();
	return 0;
}
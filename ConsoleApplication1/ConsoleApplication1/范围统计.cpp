//范围统计
//给出N个整数Xi m个询问 对于每个询问(a,b) 输出闭区间[a,b]内整数xi的个数
//xi >= a 找a首次出现的位置
//xi <= b 找b最后出现的位置
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
		//(最后一次出现b的位置+1) - (首次出现a的位置)
		//xi [a,b] 首次出现a的位置  到 最后一次出现b的位置 中间的个数
	}
	getchar();
	getchar();
	return 0;
}
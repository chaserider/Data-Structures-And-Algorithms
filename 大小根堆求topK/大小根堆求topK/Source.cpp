#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;

//���ظ�������С  topk  �͹�ϣ���
int main()
{

	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 1000; i++)
		vec.push_back(rand() % 10000);

	unordered_map<int, int> map;
	for (int& num : vec)
		map[num]++;
	using Type = pair<int, int>;
	priority_queue < Type, vector<Type>, function<bool(Type&, Type&)>> maxheap(
		[](Type& a, Type& b)->bool {return a.second < b.second; });
	int k = 5;
	auto it = map.begin();
	for (int i=0;i<k; i++,it++)
	{
		maxheap.push(*it);
	}
	for (; it != map.end(); it++)
	{
		if (maxheap.top().second > it->second)
		{
			maxheap.pop();
			maxheap.push(*it);
		}
	}
	while (!maxheap.empty())
	{
		std::cout << maxheap.top().first << std::endl;
		maxheap.pop();
	}
}











#if 0
int main()
{
	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 1000; i++)
		vec.push_back(rand() % 10000);

	//��vec��ֵ��С��ǰ5��Ԫ��
	priority_queue<int> maxheap;
	int k = 5;
	for (int i = 0; i < k; i++)
	{
		maxheap.push(vec[i]);
	}
	for (int i = 5; i < vec.size(); i++)
	{
		if (maxheap.top() > vec[i])
		{
			maxheap.pop();
			maxheap.push(vec[i]);
		}
	}
	while (!maxheap.empty())
	{
		std::cout << maxheap.top() << std::endl;
		maxheap.pop();
	}
	std::cin.get();

	//��vec��ֵ��С��ǰ5��Ԫ��
	priority_queue<int,vector<int>,greater<int>> maxheap;
	int k = 5;
	for (int i = 0; i < k; i++)
	{
		maxheap.push(vec[i]);
	}
	for (int i = 5; i < vec.size(); i++)
	{
		if (maxheap.top() > vec[i])
		{
			maxheap.pop();
			maxheap.push(vec[i]);
		}
	}
	while (!maxheap.empty())
	{
		std::cout << maxheap.top() << std::endl;
		maxheap.pop();
	}
	std::cin.get();
	//�����

}
#endif
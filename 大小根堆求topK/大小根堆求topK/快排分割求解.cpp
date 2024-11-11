#include <iostream>
#include <vector>
using namespace std;
int Partation(vector<int> &vec, int begin, int end)
{

	int n = vec.size();
	int i = begin, j = end ;
	int key = vec[begin];
	while (i<j)
	{
		while (i<j&&vec[j] > key)
			j--;
		if (j > i)
		{
			vec[i] = vec[j];
			i++;
		}
		while (i<j&&vec[i] < key)
			i++;
		if (i < j)
		{
			vec[j] = vec[i];
			j--;
		}
	
	}
	vec[i] = key;
	return  i;
}
void  SelectTopk(vector<int> &vec,int begin,int end,int k)
{
	int pos = Partation(vec, begin, end);
	if (pos == k - 1)
	{
		return;
	}
	else if (pos > k - 1)
	{
		SelectTopk(vec, begin, pos - 1, k);
	}
	else SelectTopk(vec, pos + 1, end, k);
}


int main()
{
	srand(time(nullptr));
	vector<int> vec = {64,45,52,80,66,68,0,2,18,75};


	SelectTopk(vec, 0, vec.size() - 1, 3);
	for (int i = 0; i < 3; i++)
	{
		std::cout << vec[i] << "  ";
	}

std:: cin.get();
}

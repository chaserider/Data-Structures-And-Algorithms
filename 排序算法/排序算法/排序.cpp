#include <iostream>
#include<stdlib.h>
#include <time.h>
#include <functional>
#include <string>
#include <vector>
using namespace std;

//ð�������㷨,Ч����ͣ����ݽ��������ࣻƽ�����ʱ�临�Ӷ�O��n^2�� ���O��n �� �ռ临�Ӷ�O��1�� �ȶ��ԣ��ȶ� 
void BubbleSort(int arr[], int size)
{
	for (int j = 0; j < size - 1; j++)
	{
		bool flag = false;
		for (int i = 0; i < size - j - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				flag = true;
			}
		}
		if (!flag)
			return;
	}

}


//ѡ������   ʱ�临�Ӷȶ���O��n^2��  �ռ临�Ӷ�O��1��   �ȶ��ԣ����ȶ�
void ChoiceSort(int arr[], int size)
{

	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		if (min != i)
		{
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}

}

//��������  ����������������������Ч�����   ��������  ���롷ð��&&ѡ��   �ȶ��ԣ��ȶ�
//ʱ�临�Ӷ�  �ƽ��O��n^2�� ���O��n��
void InsertSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int val = arr[i];
		int j = i - 1;
		for (; j >= 0; j--)
		{
			if (arr[j] <= val)
				break;
			arr[j + 1] = arr[j];

		}
		arr[j+1] = val;
	}

}

//ϣ������  �Բ���������Ż���������������ȶ�����������Ч����ߣ�
//�����ݷ����������
//ƽ��ʱ�临�Ӷ�O��n^1.3�� �O��n^2�����O��n��  �ռ临�Ӷ�O��1�� �ȶ��ԣ����ȶ�
void ShellSort(int arr[], int size)
{
	for (int gap=size/2;gap>0;gap/=2)
	for (int i = gap; i < size; i++)
	{
		int val = arr[i];
		int j = i - gap;
		for (; j >= 0; j-=gap)
		{
			if (arr[j] <= val)
				break;
			arr[j + gap] = arr[j];

		}
		arr[j + gap] = val;
	}
}

//���ŷָ�
void Partation(int arr[], int left, int right)
{
	int val = arr[left];
	while (left < right)
	{
		while (left<right&&arr[right] >val)
			right--;
		if(left<right)
		{
			arr[left] = arr[right];
			left++;
		}
		while (left < right && arr[left] < val)
		{
			left++;
		}
		if (left < right)
		{
			arr[right] = arr[left];
			right--;
		}
	}

	arr[left] = val;
}
//��������  ð����������  ѡȡ��׼��   ����logn ÿ��O(n)  ʱ����ú�ƽ�����Ӷ�O(nlogn) �O��n^2��      ���˵ݹ飬�ռ俼�ǵݹ���� �ռ临�Ӷ����ƽ��O(longn)�ݹ���� �O(n)         �ȶ��ԣ����ȶ�
void QuickSort(int arr[],int left,int right)
{
	if (left == right)
		return;

//���������㷨�Ż�     
//�Ż�һ   ����������������Ѿ������������Ч�����
//���ſ��� ����Խ��Խ��������   ��һ����Χ�ڿ��Բ��ò������������������
	//if (rigth - left <= 50)
	//{
	//	InsertSort(arr, left, right);
	//}


//�Ż�2  ѡ����ʻ�׼��  ��֤��������������ƽ��   ��������ȡ�з� �Һ��ʻ�׼��


	Partation(arr, left, right);

	QuickSort(arr, left, right - 1);
	QuickSort(arr, left + 1, right);
}
void QuickSort(int arr[], int size)
{
	return QuickSort(arr, 0, size - 1);
}



//�鲢����  Ҳ���÷���˼��  �ݹ� ����С����  �鷵�ظ��������   �ڹ�Ĺ����н�������
//����ƽ��ʱ�临�Ӷȶ�ΪO(nlongn)    �ռ临�Ӷ�  �ݹ�ջO��longn��+��������O��n��  �ȶ�
void  MergeSort(int arr[], int left, int right)
{
	if (left == right)
		return;

	int mid = (left + right) / 2;

	//�ȵݹ�
	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);


	//�ٺϲ�  ������С�����кϲ�
	int *temp=new int[right-left+1];
	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i < mid + 1 && j < right + 1)
	{
		if (arr[i] <= arr[j])
	
			temp[k] = arr[i];
		
		else
			temp[k] = arr[j];
		k++;
	}
	while (i <= mid)
	{
		temp[k++] = arr[i++];
	}
	while (j <= right)
	{
		temp[k++] = arr[j++];
	}



	//�ٿ�����arr��
	for (i = left, j = 0; i <= right; i++, j++)
	{
		arr[i] = temp[j];
	}

	delete[]temp;
 }



//������   ����������洢  ���㺢�ӽڵ�  ��ԭ���鿴��������
//���ȼ�����   �����priority_queue
class PriorityQueue
{
public:
	using Comp = function<bool(int, int)>;
	PriorityQueue(int cap = 20, Comp comp = greater<int>())
		:size(0)
		,cap(cap)
		,comp(comp)
	{
		m_que = new int[cap];
	}
	PriorityQueue( Comp comp = greater<int>())
		:size(0)
		, cap(20)
		, comp(comp)
	{
		m_que = new int[cap];
	}
	~PriorityQueue()
	{
		delete[]m_que;
		m_que = nullptr;
	}

public:
	//��Ѳ���
	void push(int val)
	{
		if (size == cap)
		{
			int* p = new int[2 * cap];
			memcpy(p, m_que, cap * sizeof(int));
			delete[]m_que;
			m_que = p;
			cap *= 2;
		}
		if (size == 0)
			m_que[size] = val;
		else
		{

			siftUp(size,val);//�ϸ�
			
		}
		size++;
	}

	void pop()
	{
		if (size == 0)
			throw "empty";
		size--;
		if (size > 0)
		{
			//ɾ���Ѷ�Ԫ�أ�����ʣ���Ԫ�أ�Ҫ���жѵ��³�
			siftDown(0,m_que[size]);
		}
	}
	bool empty()const
	{
		return size == 0;
	}
	int top()const
	{
		if (empty())
			throw " empty";
		return m_que[0];
	}
private:
	void siftDown(int i, int val)//�³�����
	{
		while (i <= (size - 1 - 1) / 2)//����³����ܳ������һ���к��ӵĽڵ�
		{
			int child = 2 * i + 1;//��i���ڵ������
			if (child + 1 < size&&comp(m_que[child+1],m_que[child]))
			{
				child = child + 1;//�Һ��Ӵ�������
			}
			if (comp(m_que[child], val))
			{
				m_que[i] = m_que[child];
				i = child;
			}
			else
				break;
		}
		m_que[i] = val;
	}
	void siftUp(int i, int val)//����ϸ�����
	{
		while (i > 0)//�����㵽���ڵ�
		{
			int father = (i - 1) / 2;
			if (comp(val, m_que[father]))
			{
				m_que[i] = m_que[father];
				i = father;
			}
			else {
				break;
			}
		}
		//��val�ŵ�i��λ��
		m_que[i] = val;
	}
private:
	int* m_que;//ָ��̬���ݵ�����
	int size;//Ԫ�ظ���
	int cap;//������С
	Comp comp;//�Ƚ���
};

void HeapSort(int arr[],int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		int parent = (i - 1) / 2;
		if (arr[i] < arr[parent])
		{
			int temp = arr[i];
			arr[i] = arr[parent];
			arr[parent] = temp;
		}
	}

}

//������   �ӵ�һ����Ҷ�ӽڵ� �Ѷ���ѵ���Ϊ�����  �ӵڣ�n-1��/2���Ѷ������³�  ���ȶ�
void siftDown(int arr[], int i, int size)
{
	int val = arr[i];
	while (i <= (size - 1 - 1) / 2)
	{
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}
		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child;
		}
		else
			break;


	}
	arr[i] = val;
}
void Heap(int arr[], int i, int size)
{
	int n = size - 1;
	for (int i = (n - 1) / 2; i > 0; i++)
	{
		siftDown(arr, i, size);
	}
	//�ѶѶ�Ԫ�غ�ĩβԪ�ؽ��� �����³�����
	for (int i = n; i > 0; i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		siftDown(arr, 0, i);
	}

}

//��������Ͱ����
void RadixSort(int arr[], int size)
{
	int maxData = arr[0];
	for (int i = 1; i < size; i++)
		if (maxData < arr[i])
			maxData = arr[i];
	int len = to_string(maxData).size();

	vector<vector<int>> vecs;
	int mod = 10;
	int dev = 1;

	for (int i = 0; i < len; mod *= 10; dev *= 10, i++)
	{
		vecs.resize(10);
		for (int j = 0; j < size; j++)
		{
			//�õ���i������
			int index = arr[i] % mod / dev;
			vecs[index].push_back(arr[j]);
		}

		//���α������е�tong
		int idex = 0;
		for (auto vec : vecs)
		{
			for (int v : vec)
			{
				arr[idex++] = v;
			}
		}
		vecs.clear();
	}
}

int main()
{
	int arr[10];
	srand(time(nullptr));
	for (int i = 0; i < 10; i++)
	{

		arr[i] = rand() % 100 + 1;
	}
	for (int v : arr)
		std::cout << v << " ";

	std::cout << std::endl;
	//BubbleSort(arr, 10);
	//ChoiceSort(arr, 10);
	//ShellSort(arr, 10);
	QuickSort(arr,10);
	for (int v : arr)
		std::cout << v << " ";
	std::cout << std::endl;
	std::cin.get();
}

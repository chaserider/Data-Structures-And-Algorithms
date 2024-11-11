#include <iostream>
#include<stdlib.h>
#include <time.h>
#include <functional>
#include <string>
#include <vector>
using namespace std;

//冒泡排序算法,效率最低，数据交换次数多；平均和最坏时间复杂度O（n^2） 最好O（n ） 空间复杂度O（1） 稳定性：稳定 
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


//选择排序   时间复杂度都是O（n^2）  空间复杂度O（1）   稳定性：不稳定
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

//插入排序  如果数据趋于有序插入排序效率最高   基础排序  插入》冒泡&&选择   稳定性：稳定
//时间复杂度  最坏平均O（n^2） 最好O（n）
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

//希尔排序  对插入排序的优化（如果数据趋于稳定，插入排序效率最高）
//对数据分组插入排序
//平均时间复杂度O（n^1.3） 最坏O（n^2）最好O（n）  空间复杂度O（1） 稳定性：不稳定
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

//快排分割
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
//快速排序  冒泡排序升级  选取基准数   层数logn 每层O(n)  时间最好和平均复杂度O(nlogn) 最坏O（n^2）      用了递归，空间考虑递归深度 空间复杂度最好平均O(longn)递归深度 最坏O(n)         稳定性：不稳定
void QuickSort(int arr[],int left,int right)
{
	if (left == right)
		return;

//快速排序算法优化     
//优化一   当数据趋于有序或已经有序插入排序效率最高
//随着快排 数据越来越趋于有序   在一定范围内可以采用插入排序替代快速排序
	//if (rigth - left <= 50)
	//{
	//	InsertSort(arr, left, right);
	//}


//优化2  选择合适基准数  保证二叉树左右两边平衡   采用三数取中法 找合适基准数


	Partation(arr, left, right);

	QuickSort(arr, left, right - 1);
	QuickSort(arr, left + 1, right);
}
void QuickSort(int arr[], int size)
{
	return QuickSort(arr, 0, size - 1);
}



//归并排序  也采用分治思想  递归 递缩小问题  归返回更大的问题   在归的过程中进行排序
//最好最坏平均时间复杂度都为O(nlongn)    空间复杂度  递归栈O（longn）+辅助数组O（n）  稳定
void  MergeSort(int arr[], int left, int right)
{
	if (left == right)
		return;

	int mid = (left + right) / 2;

	//先递归
	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);


	//再合并  把两个小段序列合并
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



	//再拷贝到arr内
	for (i = left, j = 0; i <= right; i++, j++)
	{
		arr[i] = temp[j];
	}

	delete[]temp;
 }



//堆排序   都是用数组存储  计算孩子节点  将原数组看作二叉树
//优先级队列   库里的priority_queue
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
	//入堆操作
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

			siftUp(size,val);//上浮
			
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
			//删除堆顶元素，还有剩余的元素，要进行堆的下沉
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
	void siftDown(int i, int val)//下沉调整
	{
		while (i <= (size - 1 - 1) / 2)//最多下沉不能超过最后一个有孩子的节点
		{
			int child = 2 * i + 1;//第i个节点的左孩子
			if (child + 1 < size&&comp(m_que[child+1],m_que[child]))
			{
				child = child + 1;//右孩子大于左孩子
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
	void siftUp(int i, int val)//入堆上浮调整
	{
		while (i > 0)//最多计算到根节点
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
		//把val放到i的位置
		m_que[i] = val;
	}
private:
	int* m_que;//指向动态扩容的数组
	int size;//元素个数
	int cap;//容量大小
	Comp comp;//比较器
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

//堆排序   从第一个非叶子节点 把二叉堆调整为大根堆  从第（n-1）/2到堆顶进行下沉  不稳定
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
	//把堆顶元素和末尾元素交换 进行下沉操作
	for (int i = n; i > 0; i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		siftDown(arr, 0, i);
	}

}

//基数排序（桶排序）
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
			//得到第i个数字
			int index = arr[i] % mod / dev;
			vecs[index].push_back(arr[j]);
		}

		//依次遍历所有的tong
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

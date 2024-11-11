#include <iostream>
//˳��ջ  C++����stack  push pop top empty size

class SeqStack
{
public:
	SeqStack(int size = 10) 
		:mtop(0), mcap(size) 
	{
		mpStack = new int[mcap];
	}
	~SeqStack()
	{
		delete []mpStack;
		mpStack = nullptr;
	}

public:
	//��ջ
	void push(int val)
	{
		if (mtop == mcap)
		{
			//ջ����
			expand(2*mcap);
		}
		mpStack[mtop++] = val;
	}


	//��ջ
	void pop()
	{
		if (mtop == 0)
			throw "stack is empty";
		mtop--;
	}

	//��ȡջ��Ԫ��
	const int& top() const 
	{
		if (mtop == 0)
			throw "stack is empty";
		return mpStack[mtop-1];
	}

	//ջ��
	bool empty() const
	{
		return !mtop;
	}

	//ջԪ�ظ���
	int size()const
	{
		return mtop;
	}
private:
	void expand(int size)
	{

		int* temp = new int[size];
		memcpy(temp, mpStack, mtop*sizeof(int));
		mcap = size;
		delete[]mpStack;
		mpStack = temp;
	}

private:
	int* mpStack;
	int mtop;//ջ��λ��
	int mcap;//ջ�Ĵ�С

};


int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	SeqStack s;
	for (int v : arr)
	{
		s.push(v);
	}
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}

	std::cin.get();
}
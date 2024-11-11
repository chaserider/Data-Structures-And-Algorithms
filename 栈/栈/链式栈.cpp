#include <iostream>

struct Node
{
	Node(int data = 0) :val(data), next(nullptr) {};
	Node(int data,Node *next) :val(data), next(next) {};
	int val;
	Node* next;
};

class LinkStack
{
private:
	Node* head;
public:
	LinkStack()
	{
		head = new Node();
	}

	~LinkStack()
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			head = head->next;
			delete temp;
			temp = head;
		}

	}

public:
	void push(int val)
	{
		Node* temp = new Node(val,head->next);
		head->next = temp;
		(head->val)++;
	}
	void pop()
	{
		if (head->next == nullptr)
			throw "Stack is empty";
		Node* temp = head->next;
		head->next = temp->next;
		delete temp;
	}
	const int& top() const
	{
		if (head->next == nullptr)
			throw "Stack is empty";
		return head->next->val;
	}
	bool empty()const
	{
		return head->next==nullptr;
	}
	int size()const
	{
		return head->val;
	}
};


int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkStack s;
	for (int v : arr)
	{
		s.push(v);
	}
	std::cout << s.size() << std::endl;
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}

	std::cin.get();
}
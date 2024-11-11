#include<iostream>
#include<vector>
#include <functional>
using namespace std;
template<typename T,typename Compare=less<T>>
class BSTree
{
public:
	BSTree() :root(nullptr) {}
	~BSTree () {}

	//�ǵݹ�������
	void n_insert(const T& val)
	{
		if (root == nullptr)
		{
			root = new Node(val);
			return;
		}
		Node* p = root;
		Node* parent = nullptr;
		while(p != nullptr)
		{
			parent = p;
			if (!comp_(p->data_,val))
			{
				p = p->left_;
			}
			else if (comp_(p->data_, val))
			{
				p = p->right_;
			}
			else
			{
				//������Ԫ����ͬ��ֵ
				return;
			}
		}
		p = new Node(val);
		if (comp_(p->data_, val))

			parent->left_ = p;
		else parent->right_ = p;
	}
	void n_remove(const T& val)
	{
		if (root == nullptr)
			return;
		Node* p = root;
		Node* parent = nullptr;
		while (p != nullptr)
		{
			
			if (p->data_ == val)
				break;
			else if (!comp_(p->data_, val))
			{
				parent = p;
				p = p->left_;
			}
			else if (comp_(p->data_, val))
			{
				parent = p;
				p = p->right_;
			}
		}
		if (p == nullptr)
			return;//û�ҵ�
		if(p->left_!=nullptr&&p->right_!=nullptr)
		{
			parent = p;
			Node* pre = p->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			p->data_ = pre->data_;
			p = pre;//��Ϊ����β�ڵ�
		}

		//ͳһ����ֻ��һ������
		Node* child = p->left_;
		if (child == nullptr)
			child = p->right_;

		if (parent == nullptr)//��ʾɾ�����Ǹ��ڵ�
			root = child;
		else
		{
			if (parent->left_ == p)
				parent->left_ = child;
			else parent->right_ = child;
		}
		delete p;
	}
private:
	//struct 
	struct Node
	{
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			,right_(nullptr)
		{};
		T data_;
		Node* left_;
		Node* right_;
	};
	Node* root;//���ڵ�
	Comp comp_;//����һ����������
};
int main()
{
	BSTree<int>  bst;
	int arr[] = { 58,6,45,34,234,23 };
	for(auto &a:arr)
	bst.n_insert(a);
	std::cin.get();
}
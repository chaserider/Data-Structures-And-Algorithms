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

	//非递归插入操作
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
				//不插入元素相同的值
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
			return;//没找到
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
			p = pre;//化为处理尾节点
		}

		//统一处理只有一个孩子
		Node* child = p->left_;
		if (child == nullptr)
			child = p->right_;

		if (parent == nullptr)//表示删除的是根节点
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
	Node* root;//根节点
	Comp comp_;//定义一个函数对象
};
int main()
{
	BSTree<int>  bst;
	int arr[] = { 58,6,45,34,234,23 };
	for(auto &a:arr)
	bst.n_insert(a);
	std::cin.get();
}
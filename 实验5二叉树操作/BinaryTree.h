#pragma once
#include<iostream>
#include<string>
template<class T>
struct BinaryNode											//定义二叉树节点
{
	T data;													//数据域
	BinaryNode<T> *left;									//左节点
	BinaryNode<T> *right;									//右节点
	bool rightArrived;										//后序遍历判断右节点是否被访问
	BinaryNode() {
		left = right = NULL;
		rightArrived = false;
	}
	BinaryNode(T other) {									//构造函数
		left = right = NULL;
		data = other;
		rightArrived = false;
	}
};
template <class T>
struct LinkNode												//定义链表节点模版
{
	T data;													//T类型数据
	LinkNode<T> *next;										//节点后继指针
	LinkNode(LinkNode<T> *ptr = NULL) { next = ptr; }		//构造函数	
	LinkNode(const T &item, LinkNode<T> *ptr = NULL) {
		next = ptr;
		data = item;
	}
};

template<class T>											//定义链栈类模版
class Stack
{
public:
	Stack() {												//构造函数
		top = NULL;
	}
	void Clear() {											//清空栈函数
		LinkNode<T> *p = NULL;
		while (top != NULL)									//循环删除栈顶元素
		{
			p = top;
			top = top->next;
			delete p;
		}
	}
	void Push(const T x) {									//入栈函数
		top = new LinkNode<T>(x, top);
	}

	bool Pop(T & x) {										//出栈函数 并用x接收
		if (isEmpty())return false;
		LinkNode<T> *p = top;
		top = top->next;
		x = p->data;
		return true;
	}
	int GetSize() {											//获取栈长度
		int k = 0;
		LinkNode<T> *p = top;
		while (p != NULL)
		{
			++k;
			p = p->next;
		}
		return k;
	}
	bool isEmpty() {										//判断栈是否为空
		if (top)return false;
		else return true;
	}
	~Stack() {
	}
private:
	LinkNode<T> *top = NULL;								//栈顶指针
};

															/*链二叉树类模板*/
template<class T>
class BinaryTree
{
public:
	BinaryTree() {											//默认构造函数
		root = NULL;
	}

	~BinaryTree() {											//默认析构函数
		Stack<BinaryNode<T>*> s;							//建立栈对象s
		BinaryNode<T> *p = root, *q;						//定义两个指针 期中p赋值为根节点
		q = new BinaryNode<T>();
		while (p || !s.isEmpty())							//如果p的值不为空或者栈不为空则循环以下操作
		{
			if (p) {										//如果p的值不为空
				if (!p->rightArrived) {						//如果右子树没有被访问则  p入栈   并让p进入左子树
					s.Push(p);
					p = p->left;
				}
				else										
				{
					p = NULL;								//否则 p赋值为空
				}
			}
			else											//或者p的值为空 s出栈q
			{
				s.Pop(q);
				if (q->rightArrived) { delete q; }			//如果q的右子树访问过了 清空p
				else
				{
					s.Push(q);								//或者s出栈赋值q
				}
				p = q->right;								//让p进入q的右子树
				q->rightArrived = true;						//右子树访问标志为真
			}
		}
	}
	void Creat(T spaceSign = '#') {							//调用前序创建函数
		PreOrderCreat(root, spaceSign);
	}
	int Depth() {											//计算深度函数
		return TreeDepth(root);
	}
	int Count() {											//计算节点数函数
		return NodeCount(root);
	}


	void InOrderTraverse() {
		Stack<BinaryNode<T>*> s;						//建立栈对象s
		BinaryNode<T> *p=root,*q;						//定义两个指针 期中p赋值为根节点
		q = new BinaryNode<T>();
		while (p||!s.isEmpty())							//如果p的值不为空或者栈不为空则循环以下操作
		{
			if (p) {									//如果p的值不为空  p入栈   并让p进入左子树
				s.Push(p);
				p = p->left;
			}
			else										//或者p的值为空 s出栈q 输出p中数据  让p进入q的右子树
			{
				s.Pop(q);
				cout << q->data;
				p = q->right;
			}
		}
	}
	void PreOrderTraverse() {
		Stack<BinaryNode<T>*> s;						//建立栈对象s
		BinaryNode<T> *p = root, *q;					//定义两个指针 期中p赋值为根节点
		q = new BinaryNode<T>();
		while (p || !s.isEmpty())						//如果p的值不为空或者栈不为空则循环以下操作
		{
			if (p) {									//如果p的值不为空  p入栈  输出p中数据  并让p进入左子树
				s.Push(p);
				cout << p->data;
				p = p->left;
			}
			else										//或者p的值为空 s出栈q 让p进入q的右子树
			{
				s.Pop(q);
				p = q->right;
			}
		}
	}
	void PostOrderTraverse() {
		Stack<BinaryNode<T>*> s;							//建立栈对象s
		BinaryNode<T> *p = root, *q;						//定义两个指针 期中p赋值为根节点
		q = new BinaryNode<T>();
		while (p || !s.isEmpty())							//如果p的值不为空或者栈不为空则循环以下操作
		{
			if (p) {										//如果p的值不为空
				if (!p->rightArrived) {
					s.Push(p);								//如果右子树没有被访问则  p入栈   并让p进入左子树
					p = p->left;
				}
				else
				{
					p = NULL;								//否则 p赋值为空
				}
				
				
			}
			else											//或者p的值为空 s出栈q
			{
				s.Pop(q);									//如果q的右子树访问过了 输出p中数据 
				if (q->rightArrived) { cout << q->data; q->rightArrived = false; }		
				else
				{
					s.Push(q);								//或者s出栈赋值q

				}
				p = q->right;								//让p进入q的右子树
				q->rightArrived = true;						//右子树访问标志为真
			}
		}
	}
private:
										/*前序创建二叉树递归函数*/
	void PreOrderCreat(BinaryNode<T> *(&TreeRoot), T spaceSign = '#') {
		T ch;
		cin >> ch;											//获取输入字符
		if (ch == spaceSign) { TreeRoot = NULL;  }			//如果输入字符等于空节点标志 该节点为空
		else {
			TreeRoot = new BinaryNode<T>();					//或者创建空间让数据等于字符
			TreeRoot->data = ch;
			PreOrderCreat(TreeRoot->left, spaceSign);		//创建左子树
			PreOrderCreat(TreeRoot->right, spaceSign);		//创建右子树
		}
	}
	int TreeDepth(BinaryNode<T> *(&TreeRoot) ) {
		
		if (TreeRoot == NULL)return 0;						//如果节点为空 反回0
		else
		{													//或者
			int m = TreeDepth(TreeRoot->left);				//结算左子树
			int n = TreeDepth(TreeRoot->right);				//结算右子树
			if (m > n)return m + 1;							//反悔m n中的数值大的加1
			else return n + 1;
		}
	}
	int NodeCount(BinaryNode<T> *(&TreeRoot)) {				
		
		if (TreeRoot == NULL)return 0;						//如果节点 为空 返回0
		else return NodeCount(TreeRoot->left) + NodeCount(TreeRoot->right) + 1;
	}														//或者返回左右子树的和
	BinaryNode<T> *root;
	
};


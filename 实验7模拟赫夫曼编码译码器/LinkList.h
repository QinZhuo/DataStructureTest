#pragma once
#include<iostream>
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

template <class T>
class LinkList												//定义链表类模版
{
public:
	LinkList() {											//定义构造函数
		head = new LinkNode<T>;
		length = 0;
	}
	LinkList(const T &item) {
		head = new LinkNode<T>(item);
		length = 1;
	}
	LinkList(LinkList<T> &List) {

	}
	~LinkList() {
		Clear();
		delete head;
	}
	LinkList<T>& operator=(LinkList<T> &List) {

	}

	LinkNode<T>* Locate(int position) {						//定义定位函数 参数为第几个数据
		int i = 0;
		LinkNode<T> *p = head;
		if (position < 0)return NULL;
		while (NULL != p&&i<position)
		{
			p = p->next;
			i++;
		}
		return p;
	}

	bool Insert(T &item, int position) {					//定义按位置插入数据函数 在第position个节点后面加入新节点
		LinkNode<T> *p = Locate(position);
		if (NULL == p)return false;
		LinkNode<T> *node = new LinkNode<T>(item);
		if (NULL == node) {
			cerr << "分配内存失败！！！" << endl;
			exit(1);
		}
		node->next = p->next;
		p->next = node;
		length++;
		return true;
	}

	bool Remove(int position) {								//删除节点函数
		LinkNode<T> *p = Locate(position);
		if (NULL == p || NULL == p->next) { return false; }
		LinkNode<T> *del = p->next;
		p->next = del->next;
		delete del;
		length--;
		return true;
	}
	void Clear() {											//情空链表模版函数
		LinkNode<T> *p = NULL;
		while (NULL != head->next)
		{
			p = head->next;
			head->next = p->next;
			delete p;
		}
	}
	void Print()const										//打印函数 将数据按顺序打印
	{
		int count = 0;
		LinkNode<T> *p = head;
		while (NULL != p->next)
		{
			p = p->next;
			p->data.Print();
		}
	}



	bool Insert(T &item, LinkNode<T> *pre) {					//定义按节点插入数据函数 在pre节点后面插入新的节点
		LinkNode<T> *node = new LinkNode<T>(item);
		if (NULL == node) {
			cerr << "分配内存失败！！！" << endl;
			exit(1);
		}
		node->next = pre->next;
		pre->next = node;
		length++;
		return true;
	}
	bool Insert(LinkNode<T> &node, LinkNode<T> *pre) {		//定义按节点插入节点函数 在pre节点后面插入已有新的节点
		node->next = pre->next;
		pre->next = node;
		length++;
		return true;
	}
	void Add(T item) {										//在链末尾插入数据函数
		Insert(item, Length());

	}
	void AddInTrun(T &item) {								//按线性表递增顺序插入数据
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;
		if (head->next) {
			prePtr = p;
			p = p->next;
		}
		while (p->next&&item > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (!p->next&&item>p->data)Insert(item, p);			//寻找比新数据大的节点 在该节点前插入数据 或者插入末尾
		else Insert(item, prePtr);

	}
	void Pop(T &item) {
		
		item = Locate(length)->data;
			Remove(length -1);
			
		
	}
	void AddNodeInTrun(LinkNode<T> &node) {					//按线性表递增顺序插入已有节点
		
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;

		while (p->next&&node.data > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (!p->next&&node.data>p->data)Insert(node.data, p);//寻找比已有节点数据大的节点 在该节点前插入数据 或者插入末尾
		else Insert(node.data, prePtr);
	}
	int Length() {											//获取链表长度	
		int count = 0;
		LinkNode<T> *p = head->next;
		while (NULL != p)
		{
			p = p->next;
			++count;
		}
		return count;
	}
	void Reverse() {										//逆至函数
		LinkNode<T> *pre = head->next;
		LinkNode<T> *curr = pre->next;
		LinkNode<T> *next = NULL;
		head->next->next = NULL;
		while (curr)										//从前往后逐位逆至
		{
			next = curr->next;
			curr->next = pre;
			pre = curr;
			curr = next;
		}
		head->next = pre;
	}
	LinkList<T>& operator+=(LinkList<T> & list) {			//重载+=操作符 将链表a b按线性顺序和并
		LinkNode<T> *p = list.head->next;
		if (!p)return *this;
		LinkNode<T> *nextP = p->next;
		while (p->next)
		{
			AddNodeInTrun(*p);
			p = nextP;
			nextP = p->next;
		}
		if (p)AddNodeInTrun(*p);

		return *this;
	}
	int length;
	LinkNode<T> *head;
private:

	
	
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

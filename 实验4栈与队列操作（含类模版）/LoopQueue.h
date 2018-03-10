#pragma once
#include<iostream>
#include"LinkNode.h"


template <class T>
class LoopList												//定义循环队列链表类模版
{
public:
	LoopList() {											//定义构造函数
		head = new LinkNode<T>;
		head->next = head;
	}
	LoopList(const T &item) {
		head = new LinkNode<T>(item);
	}
	LoopList(LoopList<T> &List) {

	}
	~LoopList() {
		Clear();
		delete head;
	}
	LoopList<T>& operator=(LoopList<T> &List) {

	}

	LinkNode<T>* Locate(int position) {						//定义定位函数 参数为第几个数据
		int i = 0;
		LinkNode<T> *p = head;
		if (position < 0)return NULL;
		while (NULL != p&&i<position)
		{
			p = p->next;
			
			if (p == head)continue;
			i++;
		}
		//cout << "************测试输出定位：" << p->data << endl;
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
		return true;
	}

	bool Remove(int position) {								//删除节点函数
		LinkNode<T> *p = Locate(position);
		if (NULL == p || NULL == p->next || head == p->next) { return false; }
		LinkNode<T> *del = p->next;
		//cout << "测试输出 要删除的数据为：" << del->data<<endl;
		p->next = del->next;
		//cout << "************测试输出删除：" << del->data << endl;
		delete del;
		return true;
	}
	bool RemovePriorNode(LinkNode<T> *node) {
		int i = 0, temp = 0;
		if (head->next == node)temp = 1;
		while (i<Length() - temp)
		{
			node = node->next;
			i++;
		}
		RemoveNextNode(node);
		return true;
	}
	bool RemoveNextNode(LinkNode<T> *node) {								//删除节点函数
		LinkNode<T> *del = node->next;
		node->next = del->next;
		delete del;
		return true;
	}
	void Clear() {											//情空链表模版函数
		LinkNode<T> *p = NULL;
		while (NULL != head->next)
		{
			p = head->next;
			head->next = p->next;
			if (head->next = head)break;
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
			if (p == head)break;
			std::cout << p->data << " ";

			//if (++cout % 10 == 0)std::cout << std::endl;
		}
	}
	bool Insert(T item, LinkNode<T> *pre) {					//定义按节点插入数据函数 在pre节点后面插入新的节点
		LinkNode<T> *node = new LinkNode<T>(item);
		if (NULL == node) {
			cerr << "分配内存失败！！！" << endl;
			exit(1);
		}
		node->next = pre->next;
		pre->next = node;
		return true;
	}
	bool Insert(LinkNode<T> &node, LinkNode<T> *pre) {		//定义按节点插入节点函数 在pre节点后面插入已有新的节点
		node->next = pre->next;
		pre->next = node;
		return true;
	}
	void Add(T item) {										//在链末尾插入数据函数
		Insert(item, Length());

	}
	void Push(T item) {										//入队函数
		Insert(item, Length());
	}
	void Pop(T &item) {										//出队函数 并用item接收数据
		item = (*Locate( 1 )).data;
		Remove(0);
		//cout <<"***************************************测试输出链长："<< Length()<<endl;
	}
	void AddInTrun(T item) {								//按线性表递增顺序插入数据
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;
		while (p->next&&item > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (p->next != head&&item>p->data)Insert(item, p);			//寻找比新数据大的节点 在该节点前插入数据 或者插入末尾
		else Insert(item, prePtr);

	}
	void AddNodeInTrun(LinkNode<T> &node) {					//按线性表递增顺序插入已有节点
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;
		while (p->next&&node.data > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (p->next != head&&node.data>p->data)Insert(node.data, p);//寻找比已有节点数据大的节点 在该节点前插入数据 或者插入末尾
		else Insert(node.data, prePtr);
	}
	int Length() {											//获取链表长度	
		int count = 0;
		LinkNode<T> *p = head->next;
		while (head != p)
		{
			p = p->next;
			//if (head == p)break;
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
	LoopList<T>& operator+=(LoopList<T> & list) {			//重载+=操作符 将链表a b按线性顺序和并
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
	LinkNode<T> *GetS() {
		if (Length() > 2) {
			return head->next->next->next;
			//return head->next;
		}
		else
		{
			return head->next;
		}
	}
private:
	LinkNode<T> *head;


};


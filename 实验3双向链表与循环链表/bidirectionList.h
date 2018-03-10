#pragma once
#include<iostream>
#include<string>
using namespace std;
template <class T>
struct BidirectionNode												//定义循环频率链表节点模版
{
	T data;															//T类型数据
	BidirectionNode<T> *next;										//节点后继指针
	BidirectionNode<T> *prior;										//节点前驱指针
	int freq;
	BidirectionNode(BidirectionNode<T> *ptr = NULL) { next = ptr; freq = 0;}		//构造函数	
	BidirectionNode(const T &item, BidirectionNode<T> *ptr = NULL) {
		next = ptr;
		data = item;
		freq = 0;
	}
};

template <class T>
class BidirectionList												//定义链表类模版
{
public:
	BidirectionList() {											//定义构造函数
		head = new BidirectionNode<T>;
		head->prior = NULL;
	}
	BidirectionList(const T &item) {
		head = new BidirectionNode<T>(item);
	}
	BidirectionList(BidirectionList<T> &List) {

	}
	~BidirectionList() {
		Clear();
		delete head;
	}
	BidirectionList<T>& operator=(BidirectionList<T> &List) {

	}

	BidirectionNode<T>* Locate(int position) {						//定义定位函数 参数为第几个数据
		int i = 0;
		BidirectionNode<T> *p = head;
		if (position < 0)return NULL;
		while (NULL != p&&i<position)
		{
			p = p->next;
			i++;
		}
		return p;
	}

	bool Insert(T &item, int position) {					//定义按位置插入数据函数 在第position个节点后面加入新节点
		BidirectionNode<T> *p = Locate(position);
		if (NULL == p)return false;
		BidirectionNode<T> *node = new BidirectionNode<T>(item);
		if (NULL == node) {
			cerr << "分配内存失败！！！" << endl;
			exit(1);
		}
		node->next = p->next;
		node->prior = p;
		p->next = node;
		return true;
	}

	bool Remove(int position) {								//删除节点函数
		BidirectionNode<T> *p = Locate(position);
		if (NULL == p || NULL == p->next) { return false }
		BidirectionNode<T> *del = p->next;
		p->next = del->next;
		del->next->prior = p;
		delete del;
		return true;
	}
	void Clear() {											//情空链表模版函数
		BidirectionNode<T> *p = NULL;
		while (NULL != head->next)
		{
			p = head->next;
			head->next = p->next;
			delete p;
		}
	}
	void LOCATE(T x) {
		BidirectionNode<T> *p=head->next;
		for (int i = 0; i < Length(); i++)
		{
			if (p->data == x)break;
			p = p->next;
		}
		if (p != NULL)p->freq++;
		//cout << p->freq << p->data << endl;
		
		for (int i = 0; i < Length()&&p->prior->prior&&p&&p->prior; i++)
		{
			
			if (p->freq > p->prior->freq) {
				if (p == NULL)break;
				if (!Rise(*p))break;
				//p = p->prior;
			}
			else break;
			
			//Print(); cout << "测试输出" << endl;
		}
	}
	bool Rise(BidirectionNode<T> &node) {
		if (node.prior == NULL)return false;
		BidirectionNode<T> *p=node.prior;
		p->prior -> next = &node;
		node.prior = p->prior;
		p->next = node.next;
		if(p->next)p->next->prior = p;
		node.next = p;
		p->prior = &node;
		return true;
	}
	void Print()const										//打印函数 将数据按顺序打印
	{

		BidirectionNode<T> *p = head;
		while (NULL != p->next)
		{
			p = p->next;
			std::cout <<"			"<< p->data << " freq="<<p->freq<<"      "<<endl;

		}
	}
	void Travel(void trl(BidirectionNode<T> &node)) {
		int count = 0;
		BidirectionNode<T> *p = head;
		while (NULL != p->next)
		{
			p = p->next;
			trl(*p);

		}
	}
	bool Insert(T item, BidirectionNode<T> *pre) {					//定义按节点插入数据函数 在pre节点后面插入新的节点
		BidirectionNode<T> *node = new BidirectionNode<T>(item);
		if (NULL == node) {
			cerr << "分配内存失败！！！" << endl;
			exit(1);
		}
		node->next = pre->next;
		node->prior = p;
		pre->next = node;
		return true;
	}
	bool Insert(BidirectionNode<T> &node, BidirectionNode<T> *pre) {		//定义按节点插入节点函数 在pre节点后面插入已有新的节点
		node->next = pre->next;
		node->prior = p;
		pre->next = node;
		return true;
	}
	void Add(T item) {										//在链末尾插入数据函数
		Insert(item, Length());

	}
	void AddInTrun(T item) {								//按线性表递增顺序插入数据
		BidirectionNode<T> *p = head;
		BidirectionNode<T> *prePtr = p;
		while (p->next&&item > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (!p->next&&item>p->data)Insert(item, p);			//寻找比新数据大的节点 在该节点前插入数据 或者插入末尾
		else Insert(item, prePtr);

	}
	void AddNodeInTrun(BidirectionNode<T> &node) {					//按线性表递增顺序插入已有节点
		BidirectionNode<T> *p = head;
		BidirectionNode<T> *prePtr = p;
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
		BidirectionNode<T> *p = head->next;
		while (NULL != p)
		{
			p = p->next;
			++count;
		}
		return count;
	}
	void Reverse() {										//逆至函数
		BidirectionNode<T> *pre = head->next;
		BidirectionNode<T> *curr = pre->next;
		BidirectionNode<T> *next = NULL;
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
	BidirectionList<T>& operator+=(BidirectionList<T> & list) {			//重载+=操作符 将链表a b按线性顺序和并
		BidirectionNode<T> *p = list.head->next;
		if (!p)return *this;
		BidirectionNode<T> *nextP = p->next;
		while (p->next)
		{
			AddNodeInTrun(*p);
			p = nextP;
			nextP = p->next;
		}
		if (p)AddNodeInTrun(*p);

		return *this;
	}
	BidirectionNode<T> *head;
private:

	

};


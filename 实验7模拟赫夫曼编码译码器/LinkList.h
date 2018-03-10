#pragma once
#include<iostream>
template <class T>
struct LinkNode												//��������ڵ�ģ��
{
	T data;													//T��������
	LinkNode<T> *next;										//�ڵ���ָ��
	LinkNode(LinkNode<T> *ptr = NULL) { next = ptr; }		//���캯��	
	LinkNode(const T &item, LinkNode<T> *ptr = NULL) {
		next = ptr;
		data = item;
	}
};

template <class T>
class LinkList												//����������ģ��
{
public:
	LinkList() {											//���幹�캯��
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

	LinkNode<T>* Locate(int position) {						//���嶨λ���� ����Ϊ�ڼ�������
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

	bool Insert(T &item, int position) {					//���尴λ�ò������ݺ��� �ڵ�position���ڵ��������½ڵ�
		LinkNode<T> *p = Locate(position);
		if (NULL == p)return false;
		LinkNode<T> *node = new LinkNode<T>(item);
		if (NULL == node) {
			cerr << "�����ڴ�ʧ�ܣ�����" << endl;
			exit(1);
		}
		node->next = p->next;
		p->next = node;
		length++;
		return true;
	}

	bool Remove(int position) {								//ɾ���ڵ㺯��
		LinkNode<T> *p = Locate(position);
		if (NULL == p || NULL == p->next) { return false; }
		LinkNode<T> *del = p->next;
		p->next = del->next;
		delete del;
		length--;
		return true;
	}
	void Clear() {											//�������ģ�溯��
		LinkNode<T> *p = NULL;
		while (NULL != head->next)
		{
			p = head->next;
			head->next = p->next;
			delete p;
		}
	}
	void Print()const										//��ӡ���� �����ݰ�˳���ӡ
	{
		int count = 0;
		LinkNode<T> *p = head;
		while (NULL != p->next)
		{
			p = p->next;
			p->data.Print();
		}
	}



	bool Insert(T &item, LinkNode<T> *pre) {					//���尴�ڵ�������ݺ��� ��pre�ڵ��������µĽڵ�
		LinkNode<T> *node = new LinkNode<T>(item);
		if (NULL == node) {
			cerr << "�����ڴ�ʧ�ܣ�����" << endl;
			exit(1);
		}
		node->next = pre->next;
		pre->next = node;
		length++;
		return true;
	}
	bool Insert(LinkNode<T> &node, LinkNode<T> *pre) {		//���尴�ڵ����ڵ㺯�� ��pre�ڵ������������µĽڵ�
		node->next = pre->next;
		pre->next = node;
		length++;
		return true;
	}
	void Add(T item) {										//����ĩβ�������ݺ���
		Insert(item, Length());

	}
	void AddInTrun(T &item) {								//�����Ա����˳���������
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
		if (!p->next&&item>p->data)Insert(item, p);			//Ѱ�ұ������ݴ�Ľڵ� �ڸýڵ�ǰ�������� ���߲���ĩβ
		else Insert(item, prePtr);

	}
	void Pop(T &item) {
		
		item = Locate(length)->data;
			Remove(length -1);
			
		
	}
	void AddNodeInTrun(LinkNode<T> &node) {					//�����Ա����˳��������нڵ�
		
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;

		while (p->next&&node.data > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (!p->next&&node.data>p->data)Insert(node.data, p);//Ѱ�ұ����нڵ����ݴ�Ľڵ� �ڸýڵ�ǰ�������� ���߲���ĩβ
		else Insert(node.data, prePtr);
	}
	int Length() {											//��ȡ������	
		int count = 0;
		LinkNode<T> *p = head->next;
		while (NULL != p)
		{
			p = p->next;
			++count;
		}
		return count;
	}
	void Reverse() {										//��������
		LinkNode<T> *pre = head->next;
		LinkNode<T> *curr = pre->next;
		LinkNode<T> *next = NULL;
		head->next->next = NULL;
		while (curr)										//��ǰ������λ����
		{
			next = curr->next;
			curr->next = pre;
			pre = curr;
			curr = next;
		}
		head->next = pre;
	}
	LinkList<T>& operator+=(LinkList<T> & list) {			//����+=������ ������a b������˳��Ͳ�
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

template<class T>											//������ջ��ģ��
class Stack
{
public:
	Stack() {												//���캯��
		top = NULL;
	}
	void Clear() {											//���ջ����
		LinkNode<T> *p = NULL;
		while (top != NULL)									//ѭ��ɾ��ջ��Ԫ��
		{
			p = top;
			top = top->next;
			delete p;
		}
	}
	void Push(const T x) {									//��ջ����
		top = new LinkNode<T>(x, top);
	}

	bool Pop(T & x) {										//��ջ���� ����x����
		if (isEmpty())return false;
		LinkNode<T> *p = top;
		top = top->next;
		x = p->data;
		return true;
	}
	int GetSize() {											//��ȡջ����
		int k = 0;
		LinkNode<T> *p = top;
		while (p != NULL)
		{
			++k;
			p = p->next;
		}
		return k;
	}
	bool isEmpty() {										//�ж�ջ�Ƿ�Ϊ��
		if (top)return false;
		else return true;
	}
	~Stack() {
	}
private:
	LinkNode<T> *top = NULL;								//ջ��ָ��
};

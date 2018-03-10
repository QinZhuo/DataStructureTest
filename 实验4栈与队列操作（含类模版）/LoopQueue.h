#pragma once
#include<iostream>
#include"LinkNode.h"


template <class T>
class LoopList												//����ѭ������������ģ��
{
public:
	LoopList() {											//���幹�캯��
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

	LinkNode<T>* Locate(int position) {						//���嶨λ���� ����Ϊ�ڼ�������
		int i = 0;
		LinkNode<T> *p = head;
		if (position < 0)return NULL;
		while (NULL != p&&i<position)
		{
			p = p->next;
			
			if (p == head)continue;
			i++;
		}
		//cout << "************���������λ��" << p->data << endl;
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
		return true;
	}

	bool Remove(int position) {								//ɾ���ڵ㺯��
		LinkNode<T> *p = Locate(position);
		if (NULL == p || NULL == p->next || head == p->next) { return false; }
		LinkNode<T> *del = p->next;
		//cout << "������� Ҫɾ��������Ϊ��" << del->data<<endl;
		p->next = del->next;
		//cout << "************�������ɾ����" << del->data << endl;
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
	bool RemoveNextNode(LinkNode<T> *node) {								//ɾ���ڵ㺯��
		LinkNode<T> *del = node->next;
		node->next = del->next;
		delete del;
		return true;
	}
	void Clear() {											//�������ģ�溯��
		LinkNode<T> *p = NULL;
		while (NULL != head->next)
		{
			p = head->next;
			head->next = p->next;
			if (head->next = head)break;
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
			if (p == head)break;
			std::cout << p->data << " ";

			//if (++cout % 10 == 0)std::cout << std::endl;
		}
	}
	bool Insert(T item, LinkNode<T> *pre) {					//���尴�ڵ�������ݺ��� ��pre�ڵ��������µĽڵ�
		LinkNode<T> *node = new LinkNode<T>(item);
		if (NULL == node) {
			cerr << "�����ڴ�ʧ�ܣ�����" << endl;
			exit(1);
		}
		node->next = pre->next;
		pre->next = node;
		return true;
	}
	bool Insert(LinkNode<T> &node, LinkNode<T> *pre) {		//���尴�ڵ����ڵ㺯�� ��pre�ڵ������������µĽڵ�
		node->next = pre->next;
		pre->next = node;
		return true;
	}
	void Add(T item) {										//����ĩβ�������ݺ���
		Insert(item, Length());

	}
	void Push(T item) {										//��Ӻ���
		Insert(item, Length());
	}
	void Pop(T &item) {										//���Ӻ��� ����item��������
		item = (*Locate( 1 )).data;
		Remove(0);
		//cout <<"***************************************�������������"<< Length()<<endl;
	}
	void AddInTrun(T item) {								//�����Ա����˳���������
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;
		while (p->next&&item > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (p->next != head&&item>p->data)Insert(item, p);			//Ѱ�ұ������ݴ�Ľڵ� �ڸýڵ�ǰ�������� ���߲���ĩβ
		else Insert(item, prePtr);

	}
	void AddNodeInTrun(LinkNode<T> &node) {					//�����Ա����˳��������нڵ�
		LinkNode<T> *p = head;
		LinkNode<T> *prePtr = p;
		while (p->next&&node.data > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (p->next != head&&node.data>p->data)Insert(node.data, p);//Ѱ�ұ����нڵ����ݴ�Ľڵ� �ڸýڵ�ǰ�������� ���߲���ĩβ
		else Insert(node.data, prePtr);
	}
	int Length() {											//��ȡ������	
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
	LoopList<T>& operator+=(LoopList<T> & list) {			//����+=������ ������a b������˳��Ͳ�
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


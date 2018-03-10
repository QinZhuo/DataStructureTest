#pragma once
#include<iostream>
#include<string>
using namespace std;
template <class T>
struct BidirectionNode												//����ѭ��Ƶ������ڵ�ģ��
{
	T data;															//T��������
	BidirectionNode<T> *next;										//�ڵ���ָ��
	BidirectionNode<T> *prior;										//�ڵ�ǰ��ָ��
	int freq;
	BidirectionNode(BidirectionNode<T> *ptr = NULL) { next = ptr; freq = 0;}		//���캯��	
	BidirectionNode(const T &item, BidirectionNode<T> *ptr = NULL) {
		next = ptr;
		data = item;
		freq = 0;
	}
};

template <class T>
class BidirectionList												//����������ģ��
{
public:
	BidirectionList() {											//���幹�캯��
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

	BidirectionNode<T>* Locate(int position) {						//���嶨λ���� ����Ϊ�ڼ�������
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

	bool Insert(T &item, int position) {					//���尴λ�ò������ݺ��� �ڵ�position���ڵ��������½ڵ�
		BidirectionNode<T> *p = Locate(position);
		if (NULL == p)return false;
		BidirectionNode<T> *node = new BidirectionNode<T>(item);
		if (NULL == node) {
			cerr << "�����ڴ�ʧ�ܣ�����" << endl;
			exit(1);
		}
		node->next = p->next;
		node->prior = p;
		p->next = node;
		return true;
	}

	bool Remove(int position) {								//ɾ���ڵ㺯��
		BidirectionNode<T> *p = Locate(position);
		if (NULL == p || NULL == p->next) { return false }
		BidirectionNode<T> *del = p->next;
		p->next = del->next;
		del->next->prior = p;
		delete del;
		return true;
	}
	void Clear() {											//�������ģ�溯��
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
			
			//Print(); cout << "�������" << endl;
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
	void Print()const										//��ӡ���� �����ݰ�˳���ӡ
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
	bool Insert(T item, BidirectionNode<T> *pre) {					//���尴�ڵ�������ݺ��� ��pre�ڵ��������µĽڵ�
		BidirectionNode<T> *node = new BidirectionNode<T>(item);
		if (NULL == node) {
			cerr << "�����ڴ�ʧ�ܣ�����" << endl;
			exit(1);
		}
		node->next = pre->next;
		node->prior = p;
		pre->next = node;
		return true;
	}
	bool Insert(BidirectionNode<T> &node, BidirectionNode<T> *pre) {		//���尴�ڵ����ڵ㺯�� ��pre�ڵ������������µĽڵ�
		node->next = pre->next;
		node->prior = p;
		pre->next = node;
		return true;
	}
	void Add(T item) {										//����ĩβ�������ݺ���
		Insert(item, Length());

	}
	void AddInTrun(T item) {								//�����Ա����˳���������
		BidirectionNode<T> *p = head;
		BidirectionNode<T> *prePtr = p;
		while (p->next&&item > p->data)
		{
			prePtr = p;
			p = p->next;

		}
		if (!p->next&&item>p->data)Insert(item, p);			//Ѱ�ұ������ݴ�Ľڵ� �ڸýڵ�ǰ�������� ���߲���ĩβ
		else Insert(item, prePtr);

	}
	void AddNodeInTrun(BidirectionNode<T> &node) {					//�����Ա����˳��������нڵ�
		BidirectionNode<T> *p = head;
		BidirectionNode<T> *prePtr = p;
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
		BidirectionNode<T> *p = head->next;
		while (NULL != p)
		{
			p = p->next;
			++count;
		}
		return count;
	}
	void Reverse() {										//��������
		BidirectionNode<T> *pre = head->next;
		BidirectionNode<T> *curr = pre->next;
		BidirectionNode<T> *next = NULL;
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
	BidirectionList<T>& operator+=(BidirectionList<T> & list) {			//����+=������ ������a b������˳��Ͳ�
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


#pragma once
#include<iostream>
#include<string>
template<class T>
struct BinaryNode											//����������ڵ�
{
	T data;													//������
	BinaryNode<T> *left;									//��ڵ�
	BinaryNode<T> *right;									//�ҽڵ�
	bool rightArrived;										//��������ж��ҽڵ��Ƿ񱻷���
	BinaryNode() {
		left = right = NULL;
		rightArrived = false;
	}
	BinaryNode(T other) {									//���캯��
		left = right = NULL;
		data = other;
		rightArrived = false;
	}
};
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

															/*����������ģ��*/
template<class T>
class BinaryTree
{
public:
	BinaryTree() {											//Ĭ�Ϲ��캯��
		root = NULL;
	}

	~BinaryTree() {											//Ĭ����������
		Stack<BinaryNode<T>*> s;							//����ջ����s
		BinaryNode<T> *p = root, *q;						//��������ָ�� ����p��ֵΪ���ڵ�
		q = new BinaryNode<T>();
		while (p || !s.isEmpty())							//���p��ֵ��Ϊ�ջ���ջ��Ϊ����ѭ�����²���
		{
			if (p) {										//���p��ֵ��Ϊ��
				if (!p->rightArrived) {						//���������û�б�������  p��ջ   ����p����������
					s.Push(p);
					p = p->left;
				}
				else										
				{
					p = NULL;								//���� p��ֵΪ��
				}
			}
			else											//����p��ֵΪ�� s��ջq
			{
				s.Pop(q);
				if (q->rightArrived) { delete q; }			//���q�����������ʹ��� ���p
				else
				{
					s.Push(q);								//����s��ջ��ֵq
				}
				p = q->right;								//��p����q��������
				q->rightArrived = true;						//���������ʱ�־Ϊ��
			}
		}
	}
	void Creat(T spaceSign = '#') {							//����ǰ�򴴽�����
		PreOrderCreat(root, spaceSign);
	}
	int Depth() {											//������Ⱥ���
		return TreeDepth(root);
	}
	int Count() {											//����ڵ�������
		return NodeCount(root);
	}


	void InOrderTraverse() {
		Stack<BinaryNode<T>*> s;						//����ջ����s
		BinaryNode<T> *p=root,*q;						//��������ָ�� ����p��ֵΪ���ڵ�
		q = new BinaryNode<T>();
		while (p||!s.isEmpty())							//���p��ֵ��Ϊ�ջ���ջ��Ϊ����ѭ�����²���
		{
			if (p) {									//���p��ֵ��Ϊ��  p��ջ   ����p����������
				s.Push(p);
				p = p->left;
			}
			else										//����p��ֵΪ�� s��ջq ���p������  ��p����q��������
			{
				s.Pop(q);
				cout << q->data;
				p = q->right;
			}
		}
	}
	void PreOrderTraverse() {
		Stack<BinaryNode<T>*> s;						//����ջ����s
		BinaryNode<T> *p = root, *q;					//��������ָ�� ����p��ֵΪ���ڵ�
		q = new BinaryNode<T>();
		while (p || !s.isEmpty())						//���p��ֵ��Ϊ�ջ���ջ��Ϊ����ѭ�����²���
		{
			if (p) {									//���p��ֵ��Ϊ��  p��ջ  ���p������  ����p����������
				s.Push(p);
				cout << p->data;
				p = p->left;
			}
			else										//����p��ֵΪ�� s��ջq ��p����q��������
			{
				s.Pop(q);
				p = q->right;
			}
		}
	}
	void PostOrderTraverse() {
		Stack<BinaryNode<T>*> s;							//����ջ����s
		BinaryNode<T> *p = root, *q;						//��������ָ�� ����p��ֵΪ���ڵ�
		q = new BinaryNode<T>();
		while (p || !s.isEmpty())							//���p��ֵ��Ϊ�ջ���ջ��Ϊ����ѭ�����²���
		{
			if (p) {										//���p��ֵ��Ϊ��
				if (!p->rightArrived) {
					s.Push(p);								//���������û�б�������  p��ջ   ����p����������
					p = p->left;
				}
				else
				{
					p = NULL;								//���� p��ֵΪ��
				}
				
				
			}
			else											//����p��ֵΪ�� s��ջq
			{
				s.Pop(q);									//���q�����������ʹ��� ���p������ 
				if (q->rightArrived) { cout << q->data; q->rightArrived = false; }		
				else
				{
					s.Push(q);								//����s��ջ��ֵq

				}
				p = q->right;								//��p����q��������
				q->rightArrived = true;						//���������ʱ�־Ϊ��
			}
		}
	}
private:
										/*ǰ�򴴽��������ݹ麯��*/
	void PreOrderCreat(BinaryNode<T> *(&TreeRoot), T spaceSign = '#') {
		T ch;
		cin >> ch;											//��ȡ�����ַ�
		if (ch == spaceSign) { TreeRoot = NULL;  }			//��������ַ����ڿսڵ��־ �ýڵ�Ϊ��
		else {
			TreeRoot = new BinaryNode<T>();					//���ߴ����ռ������ݵ����ַ�
			TreeRoot->data = ch;
			PreOrderCreat(TreeRoot->left, spaceSign);		//����������
			PreOrderCreat(TreeRoot->right, spaceSign);		//����������
		}
	}
	int TreeDepth(BinaryNode<T> *(&TreeRoot) ) {
		
		if (TreeRoot == NULL)return 0;						//����ڵ�Ϊ�� ����0
		else
		{													//����
			int m = TreeDepth(TreeRoot->left);				//����������
			int n = TreeDepth(TreeRoot->right);				//����������
			if (m > n)return m + 1;							//����m n�е���ֵ��ļ�1
			else return n + 1;
		}
	}
	int NodeCount(BinaryNode<T> *(&TreeRoot)) {				
		
		if (TreeRoot == NULL)return 0;						//����ڵ� Ϊ�� ����0
		else return NodeCount(TreeRoot->left) + NodeCount(TreeRoot->right) + 1;
	}														//���߷������������ĺ�
	BinaryNode<T> *root;
	
};


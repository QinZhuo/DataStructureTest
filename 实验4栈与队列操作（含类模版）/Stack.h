#pragma once
#include<iostream>
#include"LinkNode.h"

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


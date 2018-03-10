#pragma once
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
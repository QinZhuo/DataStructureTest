#pragma once
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
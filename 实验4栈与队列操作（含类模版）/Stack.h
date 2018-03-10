#pragma once
#include<iostream>
#include"LinkNode.h"

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


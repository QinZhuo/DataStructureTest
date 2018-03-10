/********************************************************************************************************************
作者：琴卓
日期：2016-9-20-12:40
文件：test.cpp LinkList.h
功能：单链表上的操作（第二次实验）（包含线性链类模版）
1、已知带头结点的动态单链表L中的结点是按整数值递增排序的，试写一算法将值为x的结点插入到表L中，使L仍然有序。
2、设计一算法，逆置带头结点的动态链表L。要求利用原表的结点空间，            并要求用尽可能少的时间完成。
3、假设有两个按元素值递增有序的线性表A和B，均以单链表作存储结构，试编写算法将A表和B表归并成一个按元素值递减有序的线性表性表C，并要求利用原表的空间存放C。
*********************************************************************************************************************/




#include<iostream>
#include"LinkList.h"						//包含线性链类模版
using namespace std;
int main() {

	LinkList<int> list,list2;				//声明两个链对象
	int a = 5;
	int i=0;
	cout << " 请 输 入 第 一 条 链 表 数 据 ：" << endl;
	while (i<3)								//向list链中加入三个数据 检测顺序是否正常
	{
		cin >> a;
		list.AddInTrun(a);
		i++;
	}
	cout << " 第 一 条 链 表数 据 打 印 结 果 ：" << endl;
	list.Print();							//打印list数据
	cout << endl;
	cout << " 请 输 入 第 二 条 链 表 数 据 ：" << endl;
	i = 0;
	while (i<3)								//想list2中加入三个数据
	{
		cin >> a;
		list2.AddInTrun(a);
		i++;
	}
	cout << " 第 二 条 链 表 数 据 打 印 结 果 ：" << endl;
	list2.Print();							//打印list2数据
	cout << endl;
	cout << endl;
	list += list2;							//将list和list2拼接并赋值list
	cout << " 两 条 链 表 数 据 合 并 后 打 印 结 果 ：" << endl;
	list.Print();
	cout << endl;
	list.Reverse();							//逆至list并打印
	cout << " 两 条 链 表 数 据 合 并 并 逆 至 后 打 印 结 果：" << endl;
	list.Print();
	return 0;
}
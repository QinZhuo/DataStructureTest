/********************************************************************************************************************
作者：琴卓
日期：2016-10-12-22:40
文件：test.cpp  BinaryTree.h (需要在C++11的环境)
功能：二叉树操作
1、以二叉链表作存储结构，设计求二叉树高度的算法。
2、一棵n个结点的完全二叉树用向量作存储结构，用非递归算法实现对该二叉树进行前序遍历。
3、以二叉链表作存储结构，编写非递归的前序、中序、后序遍历算法。
*********************************************************************************************************************/

#include<iostream>
#include"BinaryTree.h"
using namespace std;

											/*向量储存的满二叉树前序遍历*/
void PreOrderTraverse(char *index,int size) {												
	Stack<int > s;														//建立栈对象s
	int p = 1 , q=0;													//两个int储存角标量
	while (p<size || !s.isEmpty())										//如果p的值小于数组长度或者栈不为空则循环以下炒作
	{
		if (p<size) {													//如果p的值小于数组长度 p入栈 输出index【p】结果 并让p进入左子树
			s.Push(p);
			cout << index[p];
			p = p*2;
		}
		else															//或者 s出栈q中 让p进入右子树
		{
			s.Pop(q);
			p = q*2+1;
		}
	}
}


int main() {
	// ABC##DE#G##F###
	BinaryTree<char> bTree;												//建立二叉树对象bTree
	cout << "	请 按 前 序 输 入 创 建 二 叉 树 （ # 字 符 代 表 空 节 点 ）：" << endl;
	bTree.Creat();														//前序顺序建立二叉树 #代表空节点
	cout <<"	此 二 叉 树 的 节 点 数 目 为 ："<< bTree.Count()<<endl << "	此 二 叉 树 的 深 度 为 ：" << bTree.Depth()<<endl;
	cout << "	前 序 遍 历 输 出 ：" << endl<<"\t\t";					//调用前序遍历
	bTree.PreOrderTraverse();
	cout <<endl<< "	中 序 遍 历 输 出 ：" << endl << "\t\t";			//调用中序遍历
	bTree.InOrderTraverse();
	cout <<endl<< "	后 序 遍 历 输 出 ：" << endl << "\t\t";			//调用后序遍历
	bTree.PostOrderTraverse();
	cout << endl<<"	满 二 叉 树 前 序 遍 历 输 出 ："<<endl<<"\t\t";	//调用满二叉树前序遍历
	string s= "#0123456789ABCDE";
	PreOrderTraverse(&s[0], s.length());
	cout << endl;
	return 0;
}
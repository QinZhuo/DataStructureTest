/********************************************************************************************************************
作者：琴卓
日期：2016-9-26-12:40
文件：test.cpp Stack.h LoopQueue.h LinkNode.h
功能：栈与队列操作（含类模版）
1、设单链表中存放着n个字符，设计算法，判断该字符串中是否有中心对称关系。例如：xyzzyx、xyzyx都算是中心对称的字符串。
2、设计算法判断一个算术表达式的圆括号是否配对。（提示：对表达式进行扫描，遇‘(’进栈，遇‘)’退掉栈顶的‘(’，表达式被扫描完毕，栈为空)
3、假设以带头结点的循环链表表示队列，并只设一个指针指向队尾，编写相应的置队空、入队和出队算法。
*********************************************************************************************************************/


#include"Stack.h"										//包含链栈模版头文件
#include<iostream>
#include"LoopQueue.h"
#include<string>
using namespace std;
int main() {
	char c;
	string s;											//声明字符串s
	Stack<char> stack;									//建立字符栈
	cout << "请输入要检测的文本（英文或者数字）" << endl;
	cin >> s;											//输入为s赋值
												//声明字符c
	int len = s.length() / 2;							//赋值len为字符串s长度的一半
	for (int i = 0; i < len; i++) {						//让s后一半循环入栈
		stack.Push(s[s.length() - 1 - i]);
	}
	bool flag = true;										//设立标志flag为true
	for (int i = 0; i < len; i++) {						//循环出栈和s前一半对比 如若不同将flag标志设为false
		stack.Pop(c);
		if (c != s[len - i - 1])flag = false;
	}
	if (flag)cout << "是回文" << endl;					//输出是否为回文
	else cout << "不是回文 " << endl;

	cout << "请输入括号匹配段" << endl;				
	cin >> s;											//输入检测文本
	
	for (  int  i = 0; i<=(int)s.length(); i++) {		//对表达式进行扫描，遇‘(’进栈，遇‘)’退掉栈顶的‘(’，表达式被扫描完毕，栈为空
		if (s[i] == '(') { stack.Push(s[i]); cout << "("; }
		else if (s[i] == ')') { stack.Pop(c); cout << ")";
		}
	}
	if (stack.isEmpty())cout << "匹配" << endl;			//如果栈空匹配成功
	else
	{
		cout << "不匹配" << endl;
	}

	cout << "请输入5个入队数据" << endl;
	LoopList<char> looplist1;							//定义循环队列对象
	int i=0,j; 
	
	while (i<5)											//循环入队5个数据
	{
		cin >> c;
		looplist1.Push(c);
		i++;
	}
	cout << "出队数据输出结果：" << endl;
	//cout << looplist1.Length();
	int length= looplist1.Length();
	for (int i=0; i <length; i++) {						//出队并输出
		looplist1.Pop(c);
		cout << c << endl;
	}
}
/********************************************************************************************************************
作者：琴卓
日期：2016-9-22-19:40
文件：test.cpp LinkList.h LoopList.h bidirectionList.h LinkNode.h
功能：双向链表与循环链表（第三次实验）（包含线性链类模版）
1、假设在长度大于1的单循环链表中，既无头结点也无头指针。s为指向某个结点的指针，试编写算法删除结点*s的直接前驱结点。
2、已知由单链表表示的线性表中，含有三类字符的数据元素（如：字母、数字和其它字符），设计算法构造三个以循环链表示的线性表，使每一个表中只含同一类的字符，且利用原表中的结点空间作为这三个表的空间。（头结点可以另辟空间）
3、有一双链表，每个结点中除有prior、data和next域外，还有一访问频度域freq，在链表被启用前，其值均初始化为零。每当在链表上进行一次LOCATE(L,x)运算，元素值为x的结点中freq域的值增1，并使此链表中结点保持按freq递减的顺序排列，以便使频繁访问的结点总是靠近表头。设计满足上述要求的LOCATE算法。
*********************************************************************************************************************/

#include"LoopList.h"
#include"LinkList.h"
#include"bidirectionList.h"
#include<string>
#include<iostream>
using namespace std;																	
LoopList<char> letterList, numberList, elseList;										//定义三个循环链表 分别 字母 数字 其他
void Fun1(LinkNode<char> &node) {														//定义区分字符的函数
	if (node.data <= '9'&&node.data >= '0') {
		numberList.Add(node.data);
	}
	else if ((node.data <= 'z'&&node.data >= 'a') || (node.data <= 'Z'&&node.data>='A'))
	{
		letterList.Add(node.data);
	}
	else
	{
		elseList.Add(node.data);
	}
}

int main() {
	LoopList<char> lp;																	//循环链表
	lp.Add('a');
	lp.Add('b');
	lp.Add('c');
	lp.Add('d');
	LinkNode<char> *s = lp.GetS();
	cout << " 输 出 循 环 链 表 数 据 ：" << endl;
	lp.Print();						
	cout << endl<<" 指 针 s 所 指 数 据 为 ：" << s->data << endl;
	
	lp.RemovePriorNode(s);																//调用删除节点函数
	
	cout << " 删 除 前 驱 节 点 后 打 印 结 果 为 ：" << endl;
	lp.Print();
	cout << endl;
	string temp;
	
	LinkList<char> ll;																	//定义一个单链表对象 并进行数值输入
	int i = 0;
	char tempc;
	cout << " 请 输 入 10 个 字 符 " << endl;
	while (i<10)
	{
		cin >> tempc;
		ll.Add(tempc);																	//循环加入单链表中
		i++;
	}
	ll.Travel(Fun1);																	//对单链表遍历调用 Fun1函数
	
	cout <<endl<< " 字 母 有 :" << endl;
	letterList.Print();																	//打印字母循环链表
	cout << endl << " 数 字 有 :" << endl;
	numberList.Print();																	//打印数字循环链表
	cout << endl << " 其 他 字 符 有 :" << endl;
	elseList.Print();																	//打印其他字符循环链表
	cout << endl;
	cout << "5秒后进行下一个测试" << endl;
	_sleep(5000);
	system("cls");
	BidirectionList<string> bl;															//定义一个含freq双链表对象
	bl.Add("======微微一笑很倾城======");
	bl.Add("=========跨界歌王=========");
	bl.Add("=========北京折叠=========");
	bl.Add("=====傅园慧、洪荒之力=====");
	bl.Add("==2016年里约热内卢奥运会==");
	bl.Add("====中国国家女子排球队====");
	cout <<endl<< "			 双 向 含 频 率 域 链 表 数 据 打 印 结 果 为 ：" << endl << endl << endl;
	bl.Print();
	for (int i = 0; i < 5; i++)															
	{
		bl.LOCATE("====中国国家女子排球队====");
	}
	for (int i = 0; i < 10; i++)
	{
		bl.LOCATE("==2016年里约热内卢奥运会==");
	}
	
	cout <<endl<< endl << endl << "				 进 行 部 分 LOCATE 数 据 打 印 结 果 为 ：" << endl << endl << endl;
	bl.Print();																		
	for (int i = 0; i <6; i++)														//对双链表中的数据进行不同次的LOCATE函数调用
	{
		bl.LOCATE("=====傅园慧、洪荒之力=====");
	}
	for (int i = 0; i < 3; i++)
	{
		bl.LOCATE("=========北京折叠=========");
	}
	for (int i = 0; i <2; i++)
	{
		bl.LOCATE("=========跨界歌王=========");
	}
	cout << endl << endl << endl << "				 进 行 部 分 LOCATE 数 据 打 印 结 果 为 ：" << endl << endl << endl;
	bl.Print();																		//输出按freq进行排序后的数据
	return 0;
}
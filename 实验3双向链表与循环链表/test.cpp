/********************************************************************************************************************
���ߣ���׿
���ڣ�2016-9-22-19:40
�ļ���test.cpp LinkList.h LoopList.h bidirectionList.h LinkNode.h
���ܣ�˫��������ѭ������������ʵ�飩��������������ģ�棩
1�������ڳ��ȴ���1�ĵ�ѭ�������У�����ͷ���Ҳ��ͷָ�롣sΪָ��ĳ������ָ�룬�Ա�д�㷨ɾ�����*s��ֱ��ǰ����㡣
2����֪�ɵ������ʾ�����Ա��У����������ַ�������Ԫ�أ��磺��ĸ�����ֺ������ַ���������㷨����������ѭ������ʾ�����Ա�ʹÿһ������ֻ��ͬһ����ַ���������ԭ���еĽ��ռ���Ϊ��������Ŀռ䡣��ͷ��������ٿռ䣩
3����һ˫����ÿ������г���prior��data��next���⣬����һ����Ƶ����freq������������ǰ����ֵ����ʼ��Ϊ�㡣ÿ���������Ͻ���һ��LOCATE(L,x)���㣬Ԫ��ֵΪx�Ľ����freq���ֵ��1����ʹ�������н�㱣�ְ�freq�ݼ���˳�����У��Ա�ʹƵ�����ʵĽ�����ǿ�����ͷ�������������Ҫ���LOCATE�㷨��
*********************************************************************************************************************/

#include"LoopList.h"
#include"LinkList.h"
#include"bidirectionList.h"
#include<string>
#include<iostream>
using namespace std;																	
LoopList<char> letterList, numberList, elseList;										//��������ѭ������ �ֱ� ��ĸ ���� ����
void Fun1(LinkNode<char> &node) {														//���������ַ��ĺ���
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
	LoopList<char> lp;																	//ѭ������
	lp.Add('a');
	lp.Add('b');
	lp.Add('c');
	lp.Add('d');
	LinkNode<char> *s = lp.GetS();
	cout << " �� �� ѭ �� �� �� �� �� ��" << endl;
	lp.Print();						
	cout << endl<<" ָ �� s �� ָ �� �� Ϊ ��" << s->data << endl;
	
	lp.RemovePriorNode(s);																//����ɾ���ڵ㺯��
	
	cout << " ɾ �� ǰ �� �� �� �� �� ӡ �� �� Ϊ ��" << endl;
	lp.Print();
	cout << endl;
	string temp;
	
	LinkList<char> ll;																	//����һ����������� ��������ֵ����
	int i = 0;
	char tempc;
	cout << " �� �� �� 10 �� �� �� " << endl;
	while (i<10)
	{
		cin >> tempc;
		ll.Add(tempc);																	//ѭ�����뵥������
		i++;
	}
	ll.Travel(Fun1);																	//�Ե������������ Fun1����
	
	cout <<endl<< " �� ĸ �� :" << endl;
	letterList.Print();																	//��ӡ��ĸѭ������
	cout << endl << " �� �� �� :" << endl;
	numberList.Print();																	//��ӡ����ѭ������
	cout << endl << " �� �� �� �� �� :" << endl;
	elseList.Print();																	//��ӡ�����ַ�ѭ������
	cout << endl;
	cout << "5��������һ������" << endl;
	_sleep(5000);
	system("cls");
	BidirectionList<string> bl;															//����һ����freq˫�������
	bl.Add("======΢΢һЦ�����======");
	bl.Add("=========������=========");
	bl.Add("=========�����۵�=========");
	bl.Add("=====��԰�ۡ����֮��=====");
	bl.Add("==2016����Լ����¬���˻�==");
	bl.Add("====�й�����Ů�������====");
	cout <<endl<< "			 ˫ �� �� Ƶ �� �� �� �� �� �� �� ӡ �� �� Ϊ ��" << endl << endl << endl;
	bl.Print();
	for (int i = 0; i < 5; i++)															
	{
		bl.LOCATE("====�й�����Ů�������====");
	}
	for (int i = 0; i < 10; i++)
	{
		bl.LOCATE("==2016����Լ����¬���˻�==");
	}
	
	cout <<endl<< endl << endl << "				 �� �� �� �� LOCATE �� �� �� ӡ �� �� Ϊ ��" << endl << endl << endl;
	bl.Print();																		
	for (int i = 0; i <6; i++)														//��˫�����е����ݽ��в�ͬ�ε�LOCATE��������
	{
		bl.LOCATE("=====��԰�ۡ����֮��=====");
	}
	for (int i = 0; i < 3; i++)
	{
		bl.LOCATE("=========�����۵�=========");
	}
	for (int i = 0; i <2; i++)
	{
		bl.LOCATE("=========������=========");
	}
	cout << endl << endl << endl << "				 �� �� �� �� LOCATE �� �� �� ӡ �� �� Ϊ ��" << endl << endl << endl;
	bl.Print();																		//�����freq��������������
	return 0;
}
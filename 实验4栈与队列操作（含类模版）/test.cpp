/********************************************************************************************************************
���ߣ���׿
���ڣ�2016-9-26-12:40
�ļ���test.cpp Stack.h LoopQueue.h LinkNode.h
���ܣ�ջ����в���������ģ�棩
1���赥�����д����n���ַ�������㷨���жϸ��ַ������Ƿ������ĶԳƹ�ϵ�����磺xyzzyx��xyzyx���������ĶԳƵ��ַ�����
2������㷨�ж�һ���������ʽ��Բ�����Ƿ���ԡ�����ʾ���Ա��ʽ����ɨ�裬����(����ջ������)���˵�ջ���ġ�(�������ʽ��ɨ����ϣ�ջΪ��)
3�������Դ�ͷ����ѭ�������ʾ���У���ֻ��һ��ָ��ָ���β����д��Ӧ���öӿա���Ӻͳ����㷨��
*********************************************************************************************************************/


#include"Stack.h"										//������ջģ��ͷ�ļ�
#include<iostream>
#include"LoopQueue.h"
#include<string>
using namespace std;
int main() {
	char c;
	string s;											//�����ַ���s
	Stack<char> stack;									//�����ַ�ջ
	cout << "������Ҫ�����ı���Ӣ�Ļ������֣�" << endl;
	cin >> s;											//����Ϊs��ֵ
												//�����ַ�c
	int len = s.length() / 2;							//��ֵlenΪ�ַ���s���ȵ�һ��
	for (int i = 0; i < len; i++) {						//��s��һ��ѭ����ջ
		stack.Push(s[s.length() - 1 - i]);
	}
	bool flag = true;										//������־flagΪtrue
	for (int i = 0; i < len; i++) {						//ѭ����ջ��sǰһ��Ա� ������ͬ��flag��־��Ϊfalse
		stack.Pop(c);
		if (c != s[len - i - 1])flag = false;
	}
	if (flag)cout << "�ǻ���" << endl;					//����Ƿ�Ϊ����
	else cout << "���ǻ��� " << endl;

	cout << "����������ƥ���" << endl;				
	cin >> s;											//�������ı�
	
	for (  int  i = 0; i<=(int)s.length(); i++) {		//�Ա��ʽ����ɨ�裬����(����ջ������)���˵�ջ���ġ�(�������ʽ��ɨ����ϣ�ջΪ��
		if (s[i] == '(') { stack.Push(s[i]); cout << "("; }
		else if (s[i] == ')') { stack.Pop(c); cout << ")";
		}
	}
	if (stack.isEmpty())cout << "ƥ��" << endl;			//���ջ��ƥ��ɹ�
	else
	{
		cout << "��ƥ��" << endl;
	}

	cout << "������5���������" << endl;
	LoopList<char> looplist1;							//����ѭ�����ж���
	int i=0,j; 
	
	while (i<5)											//ѭ�����5������
	{
		cin >> c;
		looplist1.Push(c);
		i++;
	}
	cout << "����������������" << endl;
	//cout << looplist1.Length();
	int length= looplist1.Length();
	for (int i=0; i <length; i++) {						//���Ӳ����
		looplist1.Pop(c);
		cout << c << endl;
	}
}
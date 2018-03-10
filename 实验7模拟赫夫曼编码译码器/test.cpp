/********************************************************************************************************************
���ߣ���׿
���ڣ�2016-10-26-21:00
�ļ���test.cpp  LinkList.h 
���ܣ�ģ��շ�������������
�������������һ���շ�������/����ϵͳ����һ���ı��ļ���.txt���е��ַ����кշ������룬����txt�ļ����ɱ����ļ���.cod�������������ɽ�һ�������ļ���.cod����ԭΪһ���ı��ļ���.txt����
Ҫ��	��1������һ����Ҫѹ�����ı��ļ�����ͳ�Ƹ��ļ��и��ַ��ĸ�����ΪȨֵ�����ɺշ�������
		��2�����ı��ļ����úշ�����Ϊÿ���ַ����б��룬���ɱ����ļ����ļ���չ��Ϊ.cod����
		��3������һ������ѹ����ѹ���ļ�������������Ӧ�ĺշ������������������루���룩��
		��4����ʾָ���ı����ļ����ı��ļ���
		��5���Ѻշ��������ö�����λ������һ�������У�����λ�����������������ѹ��������ѹ���ȡ�����ѡ���ѡ����
*********************************************************************************************************************/






#include<iostream>								//���������
#include<fstream>								//�ļ�������7\
 
#include<string>								
#include<conio.h>								//getch���ÿ�
#include<math.h>								//��ѧ������
#include"LinkList.h"							//����ͷ�ļ�
using namespace std;							//��׼�����ռ�


typedef struct HFMnode							//����������������ṹ��
{
	int rate;									//����Ƶ��
	unsigned char data;							//����
	string code;								//���ݶ����Ʊ���
	HFMnode *zero;								//������--������
	HFMnode *one;								//һ����--������
	bool isCode;								//�Ƿ�Ϊ���ݽڵ�

	HFMnode(unsigned data=-1, int rate=-1) {	//Ĭ�Ϲ��캯��
		this->data = data;						
		this->rate = rate;
		this->code = "-1";
		isCode = false;
		zero = NULL;
		one = NULL;
	}

	HFMnode(HFMnode &other) {					//���ƹ��캯��
		this->code = other.code;				
		this->data = other.data;
		this->one = other.one;
		this->zero = other.zero;
		isCode = other.isCode;
		this->rate = other.rate;
	}

	bool operator >(HFMnode &otherNode) {		//>�������غ���
		return this->rate < otherNode.rate;
	}

	void Print() {								//��ӡ�ڵ㺯��
		cout << " �ַ���" << data << " Ƶ�ʣ�" << rate << endl;
	}

}HFMroot;


struct HFMdecode								//����������ṹ��
{
	string code;								//�����Ʊ���
	string txt;									//�ı���Ϣ
	HFMroot *root;								//����������
	string file;								//ѹ���ļ���
	string endFlag;								//����ʱ�����Ʊ���

	HFMdecode(string fileName) {				//Ĭ�Ϲ��캯��
		file = fileName;
		code = "";
		txt = "";
		tempString = "";
		root = NULL;
	}

	void RunDecode() {							//�������뺯��
		unsigned char ch;
		ifstream fin(file, ios::binary);		//�����ļ�����
		if (!fin) {
			cout << "error!!!�ļ���ʧ�ܣ�����" << endl;
			exit(0);
		}
		Creat(fin);								//���д���������������
		cout << "��������������ɣ�" << endl;	
		PreOrderTraverse();						//ǰ���������������������Ϣ

		while (fin.peek()!=EOF)					//��ȡ�ļ�������ʣ����Ϣ
		{
			ch = 0;
			fin.read((char*)&ch, sizeof(char));	
			PushChar(ch);						
		//	cout << ch << endl;
		}
		fin.close();
		if(code.length()<10000)cout << "������룺" << endl << code <<endl<< "byte��" << code.length() << endl;
		else
		{
			cout << "������룺" << endl   << code.length() << "byte��" << endl;
		}
		FileDecode();							//����Ϣ��������
	}
	
private :

	void PushChar(unsigned char ch) {			//��ȡ�ı���ת����������Ϣ
		for (int i = 7; i >= 0; i--)
		{
			code.push_back(ch / (int)pow(2, i) + '0');
			ch = ch % (int)pow(2, i);
		}

	}

	void FileDecode() {							//���뺯��
		while (code.length()) {
			tempSum = 0;
			cout << "����ʣ�ࣺ" << code.length() / (8 * 1028.0) << "kb" << endl;
			if (Decode(root, code[0]))break;	//���õݹ����뺯��
		}
		cout << "������ϣ�" << endl << "���������" << endl << txt << endl;
	}

	void Creat(ifstream &fin, char spaceSign = '~') {						//����ǰ�򴴽�����
		PreOrderCreat(fin, root, spaceSign);								//����ѭ��ǰ�򴴽�������������
	}

	int tempSum;					//����������

	string tempString;				//��ʱ���������

	bool Decode(HFMnode *node,char ch) {
		


		//cout << endl << "debug:׼���ַ�����" << tempString << "   �ܱ��룺" << code << "	  �ڵ���룺" << node->code << "    �ַ���" << ch << "    �ı���" << txt << endl;//////////////////////////////	
		//cout << endl << "debug:�ַ��������" << tempString << "	  �ܱ��룺" << code << "	  �ڵ���룺" << node->code << "    �ַ���" << ch << endl;//////////////////////////////
		//cout << "��������" <<ch<<"|"<<(int)ch<<"|"<< endl;
		//cout << code.length() << endl;


		if (tempString == node->code&&node->isCode) {			//�����ǰ����Ϊ�����������ݽ������
			if (tempString == endFlag) {  return true; }		//��ǰ����Ϊ���������˳�����


		//	cout << endl << "debug:ƥ��ɹ���" << node->data << endl;//////////////////////////////
		//	cout << "���������"<<endl<<txt << endl;


			txt += node->data;									//�����ݸ���
		
			tempString = "";
			
			if (code.length()) {
				if (++tempSum > 500)return false;				//���������ݴ���500ʱ �˳�����--��ֹѹջ����������
				Decode(root, code[0]);							//�ݹ����
			}
			else { cout << "�ޱ��룡" << endl; }

		}
		else if (ch == '0') {									//��ch==��0������0����
			if (code.length()) {
		//		cout << endl << "debug:����0����" << endl;//////////////////////////////
				tempString += ch;
				code.erase(0, 1);								//���������һ���ַ�
				
				if (!node->zero) {								//���д�����
					cout << "��0����" << endl;
					
				}Decode(node->zero, code[0]);
			}
			else { cout << "�ޱ��룡" << endl; }
		}
		else if (ch == '1') {									//��ch==��1������1����
			if (code.length()) {
		//		cout << endl << "debug:����1����" << endl;//////////////////////////////
				tempString += ch;
				code.erase(0, 1);								//���������һ���ַ�
				
				if (!node->one) {								//���д�����
					cout << "��1����" << endl;
					
				}Decode(node->one, code[0]);
			}
			else { cout << "�ޱ��룡" << endl; }
		}
		else													//���д�����
		{
			cout << "������������ļ���" << endl; return true;
		}
		//cout << "������ɣ�" << endl;
	}

	void PreOrderTraverse() {					//ǰ���������
		

		Stack<HFMnode *> s;						//����ջ����s
		HFMnode *p = root, *q;					//��������ָ�� ����p��ֵΪ���ڵ�
		q = new HFMnode();
		string tempcode = "";
		while (p || !s.isEmpty())						//���p��ֵ��Ϊ�ջ���ջ��Ϊ����ѭ�����²���
		{
			if (p) {									//���p��ֵ��Ϊ��  p��ջ  ���p������  ����p����������
				s.Push(p);
				p->code = tempcode;
				if (!p->one&&!p->zero) {
					p->isCode = true;
					if (p->data == 3) {
						endFlag = p->code;
					}
					cout << p->data << " ���룺" << p->code << endl;
				}
				else
				{
					p->isCode = false;
				}
				p = p->zero;
				tempcode += '0';
			}
			else										//����p��ֵΪ�� s��ջq ��p����q��������
			{
				s.Pop(q);
				tempcode = q->code;
				p = q->one;
				tempcode += '1';
			}
		}
	}

	bool PreOrderCreat(ifstream &fin, HFMnode *(&TreeRoot), char spaceSign = '~') {//ǰ�򴴽�������������
		char ch;
		fin.read((char*)&ch, sizeof(char));											//��ȡ�����ַ�
		cout << ch ;
		if (ch == '#')return true;
		if (ch == spaceSign) { TreeRoot = NULL; }			//��������ַ����ڿսڵ��־ �ýڵ�Ϊ��
		else {
			
			TreeRoot = new HFMnode();					//���ߴ����ռ������ݵ����ַ�
			if (ch == '*')TreeRoot->isCode = false;
			else
			{
				TreeRoot->isCode = true;
			}
			TreeRoot->data = ch;
			if (PreOrderCreat(fin, TreeRoot->zero, spaceSign))return true;		//����������
			if (PreOrderCreat(fin,TreeRoot->one, spaceSign))return true;		//����������
		}
		return false;
	}

};


struct HFMcode								//����������ṹ��
{
	string code;							//�����Ʊ���
	string file;							//ѹ���ļ���
	HFMroot *root;							//����������
	string endFlag;							//������־
	string txt;								//�ı���Ϣ
	HFMcode(string filename) {				//Ĭ�Ϲ��캯��
		file = filename;
		txt = "";
		code = "";
		root = NULL;
		NodeList.Clear();
		
		NodeList.AddInTrun(*(new HFMnode(3, 0)));
	}
	
	void OpenFile(string filename) {		//�����ƶ��ļ�����
		txt.clear();
		char tempC;							
		ifstream fin(filename);				//�����ļ�������
		if (!fin) {
			cout << "error!!!�ļ���ʧ�ܣ�����" << endl;
			exit(0);
		}
		while (fin.peek()!=EOF)
		{
			fin.get(tempC);					//��ȡ�����ı���Ϣ
			txt += tempC;
		}
		fin.close();
		cout << "��ȡ�ı��ɹ���" << endl;
		if(txt.length()<4000)cout <<"ԭ���ı���"<<endl<< txt <<endl;
		cout << "ԭ���ı���" << txt.length() * 8 << "byte" << endl;

		FileOutput();						//���ñ���д�뺯��
	}
	
private:
	void FileOutput() {						//����д�뺯��
		TxtTraverse();						//���ı���Ϣ���б���

		CodeNodeList();						//�ַ����� ������������

		ofstream fout(file, ios::binary);	//�������������
		cout << "ǰ�����" << endl;			
		PreOrderTraverse(fout);				//ǰ�����

		CodeTxt();							//���ı�����

		unsigned char ch;
		int tempI = 0;
		while (!Empty())
		{
			ch = output();					//��8����������ת��Ϊ�ַ�
			fout.write((char*)&ch, sizeof(unsigned char));//д���ַ�
			tempI++;
			if (tempI < 1024) {				
				if (tempI % 500 == 0) { cout << "�洢����" << tempI * 8 << "byte" << endl; }
			}
			else {
				if (tempI % 5000 == 0) { cout << "�洢����" << tempI / 1024 << "kb" << endl; }
			}								//�ı�д����Ƚ������
		}
		fout.close();

		cout << "���봢����ϣ�" << endl;
	}

	bool Empty() {							//�жϱ����Ƿ�Ϊ�պ���
		if (code.empty())return true;
		else
		{
			return false;
		}
	}

	void TxtTraverse() {					//�ı�����Ƶ�ʼ�¼����
		unsigned int chs[257] = { 0 };
		for (unsigned int i = 0; i < txt.length(); i++)
		{
			chs[txt[i]]++;					//�ַ�Ƶ�ʼ���
		}
		for (unsigned int i = 0; i < 256; i++)
		{
			if (chs[i]!=0) {				
				HFMnode *node = new  HFMnode(i, chs[i]);
				PushNode(*node);			//��Ƶ�ʲ�Ϊ0�����ݴ洢��������
			}
		}
		//NodeList.Print();
		//cout << "�ı���������" << endl;
		return;
	}

	void PushNode(HFMnode &node) {				//����������Ӻ���
		NodeList.AddInTrun(node);
	}

	LinkList<HFMnode> NodeList;					//������������

	void CodeTxt() {							//�ı���������
		for (int i = 0; i < txt.length(); i++)
		{
			unsigned char c = txt[i];
			LinkNode<HFMnode> *p = NodeList.head;
			while (NULL != p->next)				//Ѱ������������ƥ����
			{
				p = p->next;
				if (p->data.data == c) {
					code += p->data.code; break;//���±���
				}
			}
			//cout  << c;//<< "   ������� �޸��ַ�������" << endl;
		}
		code += endFlag;						//�ڽ�β��������ַ�
		if(code.length()<1024*8)cout <<endl<< "ѹ����������" <<code.length()<<"byte"<< endl;
		else { cout << endl << "ѹ����������" << code.length()/(1024*8) << "kb" << endl; }
		cout << "ѹ���ʣ�" << (double)code.length()/(double)(txt.length() * 8) << "%" << endl;
		if (code.length() < 10000) cout << endl << code << endl;//����ѹ���ʼ��㲢���
	}

	void CodeNodeList() {						//����������������
		HFMnode *end1, *end2 , *newNode;
		
		while (NodeList.length>1)				//��������ֻ��һ���ڵ��ǽ���
		{
		//	cout << endl;
		//	NodeList.Print();
		//	cout << endl;
			end1 = new HFMnode();
			end2 = new HFMnode();
			newNode = new HFMnode('*', 0);
			NodeList.Pop(*end1);					//ȡ��Ƶ����С�ڵ�
			NodeList.Pop(*end2);					//ȡ��Ƶ�ʵڶ�С�ڵ�
			newNode->zero = end2;
			newNode->one =end1;
			newNode->rate = end1->rate + end2->rate;//�������м�ڵ�Ƶ��
		//	cout << endl << newNode->data << "   0:" << newNode->zero->data << " 1:" << newNode->one->data << endl;
			NodeList.AddInTrun(*newNode);			//���½ڵ����������
			
		}

		root = newNode;								
	}

	void PreOrderTraverse(ofstream &fout) {		//ǰ�������д���ļ�����
		NodeList.Clear();

		Stack<HFMnode *> s;						//����ջ����s
		HFMnode *p = root, *q;					//��������ָ�� ����p��ֵΪ���ڵ�
		q = new HFMnode();
		string tempcode="";
		char c = '~';
		while (p || !s.isEmpty())						//���p��ֵ��Ϊ�ջ���ջ��Ϊ����ѭ�����²���
		{
			if (p) {									//���p��ֵ��Ϊ��  p��ջ  ���p������  ����p����������
				s.Push(p);
				p->code = tempcode;
				fout.write((char*)&(p->data), sizeof(unsigned char));;
				//cout << p->data;
				if (!p->one&&!p->zero) {
					p->isCode = true;
					if (p->rate==0) {
						endFlag = p->code;
					}
					else
					{
						NodeList.Add(*p);
					}
					NodeList.Add(*p);
					cout << p->data << " Ƶ�ʣ�" << p->rate << " ���룺"<<p->code<<endl;
			
				
				}
				else
				{
					p->isCode = false;
				}
				p = p->zero;
				tempcode += '0';
			}
			else										//����p��ֵΪ�� s��ջq ��p����q��������
			{
				
				fout.write((char*)&c, sizeof(unsigned char));;
				//cout << c;
				s.Pop(q);
				tempcode = q->code;
				p = q->one;
				tempcode += '1';
			}
		}
		c = '#';
		fout.write((char*)&c, sizeof(unsigned char));
	}
	
	unsigned char output() {						//д���ļ�����
		if (!code.length())return 0;				//���ޱ���ʱ�˳�����
		int ASCII = 0;
		unsigned char tempCh;
		for (int i = 7; i >= 0; i--) {				//ÿ8λ������ת��Ϊһ���ַ�
			if (code.length() > 0) {
				ASCII += (code[0] - '0')*pow(2, i);
				code.erase(0, 1);					//�����λ�ַ�
			}
			else
			{
				ASCII += 0 * pow(2, i);
			}
		}
		tempCh = ASCII;
		return tempCh;
	}
};


int main() {
	char n;
	string openfilename=" ";					//���ļ���
	string outputfilename=" ";					//����ļ���
	while (true)
	{
		system("cls");
		cout << "����������������      ��ѡ�����      ����������������" << endl;
		cout << "����������������      1 ѹ���ļ�      ����������������" << endl;
		cout << "����������������      2 ��ѹ�ļ�      ����������������" << endl;
		n = getch();
		
		if (n == '1') { cout << "����������������  ��������ѹ���ļ���  ����������������" << endl; cin >> openfilename; cout << "����������ļ�����" << endl; cin >> outputfilename; HFMcode code(outputfilename); code.OpenFile(openfilename); system("pause"); }
		else if (n == '2') { cout << "����������������  ���������ѹ�ļ���  ����������������" << endl; cin >> openfilename; HFMdecode decode(openfilename); decode.RunDecode(); system("pause");  }
		else { cout << "����������������  ��������  ����������������"; }

	}
	
	return 0;
}
/********************************************************************************************************************
作者：琴卓
日期：2016-10-26-21:00
文件：test.cpp  LinkList.h 
功能：模拟赫夫曼编码译码器
问题描述：设计一个赫夫曼编码/译码系统，对一个文本文件（.txt）中的字符进行赫夫曼编码，并将txt文件生成编码文件（.cod）；反过来，可将一个编码文件（.cod）还原为一个文本文件（.txt）。
要求：	（1）输入一个需要压缩的文本文件名，统计该文件中各字符的个数作为权值，生成赫夫曼树。
		（2）将文本文件利用赫夫曼树为每个字符进行编码，生成编码文件（文件扩展名为.cod）。
		（3）输入一个待解压缩的压缩文件名，并利用相应的赫夫曼树将编码序列译码（解码）。
		（4）显示指定的编码文件和文本文件。
		（5）把赫夫曼编码用二进制位紧缩到一个变量中，利用位运算进行真正的数据压缩，并求压缩比。（此选项可选作）
*********************************************************************************************************************/






#include<iostream>								//输入输出库
#include<fstream>								//文件操作库7\
 
#include<string>								
#include<conio.h>								//getch所用库
#include<math.h>								//数学函数库
#include"LinkList.h"							//链表头文件
using namespace std;							//标准命名空间


typedef struct HFMnode							//构建哈夫曼树几点结构体
{
	int rate;									//数据频率
	unsigned char data;							//数据
	string code;								//数据二进制编码
	HFMnode *zero;								//零子树--左子树
	HFMnode *one;								//一子数--右子树
	bool isCode;								//是否为数据节点

	HFMnode(unsigned data=-1, int rate=-1) {	//默认构造函数
		this->data = data;						
		this->rate = rate;
		this->code = "-1";
		isCode = false;
		zero = NULL;
		one = NULL;
	}

	HFMnode(HFMnode &other) {					//复制构造函数
		this->code = other.code;				
		this->data = other.data;
		this->one = other.one;
		this->zero = other.zero;
		isCode = other.isCode;
		this->rate = other.rate;
	}

	bool operator >(HFMnode &otherNode) {		//>符号重载函数
		return this->rate < otherNode.rate;
	}

	void Print() {								//打印节点函数
		cout << " 字符：" << data << " 频率：" << rate << endl;
	}

}HFMroot;


struct HFMdecode								//哈夫曼译码结构体
{
	string code;								//二进制编码
	string txt;									//文本信息
	HFMroot *root;								//哈夫曼树根
	string file;								//压缩文件名
	string endFlag;								//结束时二进制编码

	HFMdecode(string fileName) {				//默认构造函数
		file = fileName;
		code = "";
		txt = "";
		tempString = "";
		root = NULL;
	}

	void RunDecode() {							//进行译码函数
		unsigned char ch;
		ifstream fin(file, ios::binary);		//创建文件流类
		if (!fin) {
			cout << "error!!!文件打开失败！！！" << endl;
			exit(0);
		}
		Creat(fin);								//运行创建哈夫曼树函数
		cout << "哈夫曼树构建完成！" << endl;	
		PreOrderTraverse();						//前序输出哈夫曼数里数据信息

		while (fin.peek()!=EOF)					//读取文件中所有剩下信息
		{
			ch = 0;
			fin.read((char*)&ch, sizeof(char));	
			PushChar(ch);						
		//	cout << ch << endl;
		}
		fin.close();
		if(code.length()<10000)cout << "读入编码：" << endl << code <<endl<< "byte数" << code.length() << endl;
		else
		{
			cout << "读入编码：" << endl   << code.length() << "byte数" << endl;
		}
		FileDecode();							//对信息进行译码
	}
	
private :

	void PushChar(unsigned char ch) {			//读取文本并转化二进制信息
		for (int i = 7; i >= 0; i--)
		{
			code.push_back(ch / (int)pow(2, i) + '0');
			ch = ch % (int)pow(2, i);
		}

	}

	void FileDecode() {							//译码函数
		while (code.length()) {
			tempSum = 0;
			cout << "译码剩余：" << code.length() / (8 * 1028.0) << "kb" << endl;
			if (Decode(root, code[0]))break;	//调用递归译码函数
		}
		cout << "译码完毕！" << endl << "译码输出：" << endl << txt << endl;
	}

	void Creat(ifstream &fin, char spaceSign = '~') {						//调用前序创建函数
		PreOrderCreat(fin, root, spaceSign);								//调用循环前序创建哈夫曼树函数
	}

	int tempSum;					//计数用整形

	string tempString;				//暂时储存编码用

	bool Decode(HFMnode *node,char ch) {
		


		//cout << endl << "debug:准备字符操作" << tempString << "   总编码：" << code << "	  节点编码：" << node->code << "    字符：" << ch << "    文本：" << txt << endl;//////////////////////////////	
		//cout << endl << "debug:字符操作完成" << tempString << "	  总编码：" << code << "	  节点编码：" << node->code << "    字符：" << ch << endl;//////////////////////////////
		//cout << "函数调用" <<ch<<"|"<<(int)ch<<"|"<< endl;
		//cout << code.length() << endl;


		if (tempString == node->code&&node->isCode) {			//如果当前编码为哈夫曼树数据借点数据
			if (tempString == endFlag) {  return true; }		//当前编码为结束符号退出函数


		//	cout << endl << "debug:匹配成功：" << node->data << endl;//////////////////////////////
		//	cout << "译码输出："<<endl<<txt << endl;


			txt += node->data;									//总数据更新
		
			tempString = "";
			
			if (code.length()) {
				if (++tempSum > 500)return false;				//当编译数据大于500时 退出函数--防止压栈过多程序出错
				Decode(root, code[0]);							//递归调用
			}
			else { cout << "无编码！" << endl; }

		}
		else if (ch == '0') {									//当ch==’0‘进入0子树
			if (code.length()) {
		//		cout << endl << "debug:进入0子树" << endl;//////////////////////////////
				tempString += ch;
				code.erase(0, 1);								//数据清除第一个字符
				
				if (!node->zero) {								//进行错误检测
					cout << "无0子树" << endl;
					
				}Decode(node->zero, code[0]);
			}
			else { cout << "无编码！" << endl; }
		}
		else if (ch == '1') {									//当ch==’1‘进入1子树
			if (code.length()) {
		//		cout << endl << "debug:进入1子树" << endl;//////////////////////////////
				tempString += ch;
				code.erase(0, 1);								//数据清除第一个字符
				
				if (!node->one) {								//进行错误检测
					cout << "无1子树" << endl;
					
				}Decode(node->one, code[0]);
			}
			else { cout << "无编码！" << endl; }
		}
		else													//进行错误检测
		{
			cout << "译码出错！请检测文件！" << endl; return true;
		}
		//cout << "调用完成！" << endl;
	}

	void PreOrderTraverse() {					//前序遍历函数
		

		Stack<HFMnode *> s;						//建立栈对象s
		HFMnode *p = root, *q;					//定义两个指针 期中p赋值为根节点
		q = new HFMnode();
		string tempcode = "";
		while (p || !s.isEmpty())						//如果p的值不为空或者栈不为空则循环以下操作
		{
			if (p) {									//如果p的值不为空  p入栈  输出p中数据  并让p进入左子树
				s.Push(p);
				p->code = tempcode;
				if (!p->one&&!p->zero) {
					p->isCode = true;
					if (p->data == 3) {
						endFlag = p->code;
					}
					cout << p->data << " 编码：" << p->code << endl;
				}
				else
				{
					p->isCode = false;
				}
				p = p->zero;
				tempcode += '0';
			}
			else										//或者p的值为空 s出栈q 让p进入q的右子树
			{
				s.Pop(q);
				tempcode = q->code;
				p = q->one;
				tempcode += '1';
			}
		}
	}

	bool PreOrderCreat(ifstream &fin, HFMnode *(&TreeRoot), char spaceSign = '~') {//前序创建哈夫曼树函数
		char ch;
		fin.read((char*)&ch, sizeof(char));											//获取输入字符
		cout << ch ;
		if (ch == '#')return true;
		if (ch == spaceSign) { TreeRoot = NULL; }			//如果输入字符等于空节点标志 该节点为空
		else {
			
			TreeRoot = new HFMnode();					//或者创建空间让数据等于字符
			if (ch == '*')TreeRoot->isCode = false;
			else
			{
				TreeRoot->isCode = true;
			}
			TreeRoot->data = ch;
			if (PreOrderCreat(fin, TreeRoot->zero, spaceSign))return true;		//创建左子树
			if (PreOrderCreat(fin,TreeRoot->one, spaceSign))return true;		//创建右子树
		}
		return false;
	}

};


struct HFMcode								//哈夫曼编码结构体
{
	string code;							//二进制编码
	string file;							//压缩文件名
	HFMroot *root;							//哈夫曼树根
	string endFlag;							//结束标志
	string txt;								//文本信息
	HFMcode(string filename) {				//默认构造函数
		file = filename;
		txt = "";
		code = "";
		root = NULL;
		NodeList.Clear();
		
		NodeList.AddInTrun(*(new HFMnode(3, 0)));
	}
	
	void OpenFile(string filename) {		//编码制定文件函数
		txt.clear();
		char tempC;							
		ifstream fin(filename);				//创建文件流对象
		if (!fin) {
			cout << "error!!!文件打开失败！！！" << endl;
			exit(0);
		}
		while (fin.peek()!=EOF)
		{
			fin.get(tempC);					//获取所有文本信息
			txt += tempC;
		}
		fin.close();
		cout << "读取文本成功！" << endl;
		if(txt.length()<4000)cout <<"原文文本："<<endl<< txt <<endl;
		cout << "原文文本：" << txt.length() * 8 << "byte" << endl;

		FileOutput();						//调用编码写入函数
	}
	
private:
	void FileOutput() {						//编码写入函数
		TxtTraverse();						//对文本信息进行遍历

		CodeNodeList();						//字符编码 哈夫曼树构建

		ofstream fout(file, ios::binary);	//创建输出流对象
		cout << "前序输出" << endl;			
		PreOrderTraverse(fout);				//前序输出

		CodeTxt();							//对文本编码

		unsigned char ch;
		int tempI = 0;
		while (!Empty())
		{
			ch = output();					//将8个二进制数转化为字符
			fout.write((char*)&ch, sizeof(unsigned char));//写入字符
			tempI++;
			if (tempI < 1024) {				
				if (tempI % 500 == 0) { cout << "存储进度" << tempI * 8 << "byte" << endl; }
			}
			else {
				if (tempI % 5000 == 0) { cout << "存储进度" << tempI / 1024 << "kb" << endl; }
			}								//文本写入进度进行输出
		}
		fout.close();

		cout << "编码储存完毕！" << endl;
	}

	bool Empty() {							//判断编码是否为空函数
		if (code.empty())return true;
		else
		{
			return false;
		}
	}

	void TxtTraverse() {					//文本遍历频率记录函数
		unsigned int chs[257] = { 0 };
		for (unsigned int i = 0; i < txt.length(); i++)
		{
			chs[txt[i]]++;					//字符频率计数
		}
		for (unsigned int i = 0; i < 256; i++)
		{
			if (chs[i]!=0) {				
				HFMnode *node = new  HFMnode(i, chs[i]);
				PushNode(*node);			//将频率不为0的数据存储在链表中
			}
		}
		//NodeList.Print();
		//cout << "文本遍历结束" << endl;
		return;
	}

	void PushNode(HFMnode &node) {				//链表数据添加函数
		NodeList.AddInTrun(node);
	}

	LinkList<HFMnode> NodeList;					//储存数据链表

	void CodeTxt() {							//文本遍历编码
		for (int i = 0; i < txt.length(); i++)
		{
			unsigned char c = txt[i];
			LinkNode<HFMnode> *p = NodeList.head;
			while (NULL != p->next)				//寻找数据链表中匹配项
			{
				p = p->next;
				if (p->data.data == c) {
					code += p->data.code; break;//更新编码
				}
			}
			//cout  << c;//<< "   编码出错 无该字符！！！" << endl;
		}
		code += endFlag;						//在结尾输入结束字符
		if(code.length()<1024*8)cout <<endl<< "压缩编码编码后：" <<code.length()<<"byte"<< endl;
		else { cout << endl << "压缩编码编码后：" << code.length()/(1024*8) << "kb" << endl; }
		cout << "压缩率：" << (double)code.length()/(double)(txt.length() * 8) << "%" << endl;
		if (code.length() < 10000) cout << endl << code << endl;//进行压缩率计算并输出
	}

	void CodeNodeList() {						//哈夫曼树构建函数
		HFMnode *end1, *end2 , *newNode;
		
		while (NodeList.length>1)				//当链表中只有一个节点是结束
		{
		//	cout << endl;
		//	NodeList.Print();
		//	cout << endl;
			end1 = new HFMnode();
			end2 = new HFMnode();
			newNode = new HFMnode('*', 0);
			NodeList.Pop(*end1);					//取出频率最小节点
			NodeList.Pop(*end2);					//取出频率第二小节点
			newNode->zero = end2;
			newNode->one =end1;
			newNode->rate = end1->rate + end2->rate;//更新新中间节点频率
		//	cout << endl << newNode->data << "   0:" << newNode->zero->data << " 1:" << newNode->one->data << endl;
			NodeList.AddInTrun(*newNode);			//将新节点加入链表中
			
		}

		root = newNode;								
	}

	void PreOrderTraverse(ofstream &fout) {		//前序输出并写入文件函数
		NodeList.Clear();

		Stack<HFMnode *> s;						//建立栈对象s
		HFMnode *p = root, *q;					//定义两个指针 期中p赋值为根节点
		q = new HFMnode();
		string tempcode="";
		char c = '~';
		while (p || !s.isEmpty())						//如果p的值不为空或者栈不为空则循环以下操作
		{
			if (p) {									//如果p的值不为空  p入栈  输出p中数据  并让p进入左子树
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
					cout << p->data << " 频率：" << p->rate << " 编码："<<p->code<<endl;
			
				
				}
				else
				{
					p->isCode = false;
				}
				p = p->zero;
				tempcode += '0';
			}
			else										//或者p的值为空 s出栈q 让p进入q的右子树
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
	
	unsigned char output() {						//写入文件函数
		if (!code.length())return 0;				//当无编码时退出函数
		int ASCII = 0;
		unsigned char tempCh;
		for (int i = 7; i >= 0; i--) {				//每8位二进制转化为一个字符
			if (code.length() > 0) {
				ASCII += (code[0] - '0')*pow(2, i);
				code.erase(0, 1);					//清除首位字符
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
	string openfilename=" ";					//打开文件名
	string outputfilename=" ";					//输出文件名
	while (true)
	{
		system("cls");
		cout << "████████      请选择操作      ████████" << endl;
		cout << "████████      1 压缩文件      ████████" << endl;
		cout << "████████      2 解压文件      ████████" << endl;
		n = getch();
		
		if (n == '1') { cout << "████████  请输入需压缩文件名  ████████" << endl; cin >> openfilename; cout << "请输入输出文件名：" << endl; cin >> outputfilename; HFMcode code(outputfilename); code.OpenFile(openfilename); system("pause"); }
		else if (n == '2') { cout << "████████  请输入需解压文件名  ████████" << endl; cin >> openfilename; HFMdecode decode(openfilename); decode.RunDecode(); system("pause");  }
		else { cout << "████████  操作错误！  ████████"; }

	}
	
	return 0;
}
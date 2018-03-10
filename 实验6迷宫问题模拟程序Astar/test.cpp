/********************************************************************************************************************
���ߣ���׿
���ڣ�2016-10-12-13:40
�ļ���test.cpp  LinkList.h (��Ҫ��C++11�Ļ���)
���ܣ��Թ�����ģ�����
������������һ���ַ����͵Ķ�ά�����ʾ�Թ��������е�ÿ��Ԫ�ر�ʾһ��С����ȡֵ��0����ͨ������1��������������һ��ģ��С�������Թ��ĳ���ΪС����Ѱ��һ�����Թ���ڵ��Թ����ڵ�;��С�������ٵ����ͨ·��
Ҫ������㷨��ʵ�����¹���
��1����������������Թ����û�����ѡ���Թ��Ĵ�С���������ж����У���
��2��ѡ����ʵ����ݽṹ��ʾ�Թ���
��3���Թ���ڴ����±��ǣ�x0��y0�������ڴ����±��ǣ�x1��y1�����ɼ������롣
��4���������ڵ����ڵ����ͨ·������ڣ��򲻴���ͨ·����Ϣ��
��Ƴ��Ѻõ�ͼ�λ����棬�������õ��˻�������


Ӧ���㷨A*�㷨
��������
�رռ���
�����ʼ�㵽 ��ʼ���� ��

ѭ�����²��裺
		��ǰ��= �������� ����СF_Cost �ĵ�
		�� ��ǰ�� �Ƴ� �������� ��
		�� ��ǰ�� ��ӵ� �رռ��� ��

		��� ��ǰ�� ��Ŀ��㣬������ѯ

		���� ��ǰ�� ��ÿ�� ���ڵ�
				��� ���ڵ� ���ܷ��ʻ��� ���ڵ� �� �رռ��� �У������� ���ڵ�
				�����·���� ���ڵ� �ľ�����̣����� ���ڵ� ���� �������� ��
						��������F_Cost
						���������丸�ڵ�Ϊ ��ǰ��
				��� ���ڵ� ���� �������� ��
						��� ���ڵ� �� ����������
*********************************************************************************************************************/


																			/*ͷ�ļ��б�*/
#include<iostream>		
#include<stdlib.h>	
#include<ctime>																					//�������������ͷ�ļ�
#include<conio.h>																				//getch����ͷ�ļ�
#include"LinkList.h"																			//������ģ��
#include<thread>																				//���߳�����ͷ�ļ�
using namespace std;

															/*A*Ѱ·���ýڵ���ҪΪGHF��ֵ*/
struct AstarNode
{
	int status;																					//������ʾ�ڵ㵱ǰ״̬ 0=��ͨ�� 1=�ϰ��� 2=·�� 3=��� 4=�յ� -1=�ر��б� -2=�����б�
	int G;																						//������ߵ��˽ڵ����û���G	
	int H;																						//�˽ڵ�����յ�ľ��뻨��H���ж����㷨��
	int F;																						//G+H���ܻ���F
	int X;																						//��¼���ڵ�XY������
	int Y;
	AstarNode *parent;																			//���ڵ�ָ��

	AstarNode() {																				//Ĭ�Ϲ��캯�� ���в������ݳ�ʼ��
		status = 0;
		G = 0;
		H = 0;
		F = 0;
		parent = NULL;
	}
	void Fupdate() {																			//����Fֵ�ĺ���
		F = G + H;
	}
	void Hcost(AstarNode *node) {																//Hֵ���㺯��
		H= fabs(node->X - X) + fabs(node->Y - Y);
	}
	void Clear() {																				//���в������ݵĳ�ʼ��
		
		G = 0;
		H = 0;
		F = 0;
		parent = NULL;
	}
	bool operator >(AstarNode other) {															//����>��������Ѱ��Fֵ��С�Ľڵ�
		if (F > other.F)return true;
		else if (F < other.F)return false;
		else
		{
			if (G < other.G)return true;
			else if (G == other.G) {
				if (other.H >= H)return true;
				else return false;
			}
			else
			{
				return false;
			}
		}
	}
};

void ShowMap(AstarNode **Map, int size, bool showG = false, bool showF = false, bool showH = false);	//��ӡ�Թ��ĺ�������
bool Check(int x, int y, AstarNode **Map, int G,int size, AstarNode *end);								//���ڵ��Ƿ�Ϊ���Ž⺯��
bool FindPath(AstarNode *start, AstarNode *end, AstarNode **Map, int size, bool showPath=false);		//Ѱ��·����������

LinkList<AstarNode*>  openList;																			//ȫ�ֱ��� �����б� ������LinkList<AstarNode*>��ģ�� ����

															/*ɨ�躯��ʵ�� ɨ��ýڵ������������ߵĽڵ�*/
void UpdateEvery(AstarNode *node, AstarNode **Map,int size,AstarNode *end) {

	int tempX, tempY;
	tempX = node->X + 1; tempY = node->Y;																//�Լ��������ܵ�ÿһ���ڵ㶼����Check����
	if (Check(tempX, tempY, Map, node->G,size,end)) {
		Map[tempX][tempY].parent = node;																//���͵�G ֵ��ζ�Ÿ��õ�·����������������Ͱ���һ��ĸ��ڵ�ĳɵ�ǰ�񣬲������¼�����һ���G ��F ֵ��
	}
	tempX = node->X - 1; tempY = node->Y;
	if (Check(tempX, tempY, Map, node->G,size,end)) {
		Map[tempX][tempY].parent = node;
	}
	tempX = node->X ; tempY = node->Y-1;
	if (Check(tempX, tempY, Map, node->G,size,end)) {
		Map[tempX][tempY].parent = node;
	}
	tempX = node->X; tempY = node->Y+1;
	if (Check(tempX, tempY, Map, node->G,size,end)) {
		Map[tempX][tempY].parent = node;
	}
}

															/*������Ž⺯��ʵ��*/
bool Check(int x,int y, AstarNode **Map,int G,int size,AstarNode *end) {
	if (x >= size || x < 0 || y >= size || y < 0||Map[x][y].status==-1|| Map[x][y].status == 1) {
		return false;													//* ���������ͨ�������Ѿ��� �ر��б��У��Թ�������֮���¡�
	}
	else if(Map[x][y].status == -2)			
	{
		if (G + 1 < Map[x][y].G) {										//* ������Ѿ��� �����б��У���G ֵΪ�ο�����µ�·���Ƿ���á�
			Map[x][y].G = G + 1;										//���¼���GFֵ
			Map[x][y].Fupdate();
			return true;												//�͵�G ֵ��ζ�Ÿ��õ�·��������true
		}
		else
		{
			return false;
		}
	}
	else
	{	
		openList.Add(&Map[x][y]);										//��������� �����б��У�������ӽ�ȥ
		Map[x][y].status = -2;
		Map[x][y].Hcost(end);
		Map[x][y].G = G + 1;											//�ѵ�ǰ����Ϊ��һ��ĸ��ڵ㡣��¼��һ���F,G, ��H ֵ��
		Map[x][y].Fupdate();
		return true;
	}

}

															/*Ѱ��·������ʵ��*/
bool FindPath(AstarNode *start, AstarNode *end, AstarNode **Map,int size,bool showPath) {
	
	clock_t Timestart, Timefinish;
	double duration;
	AstarNode *currentNode;
	Timestart= clock();
	for (int i = 0; i < 1000; i++)
	{


		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Map[i][j].Clear();
				if (Map[i][j].status != 1)Map[i][j].status = 0;
			}
		}
		start->status = 3;
		end->status = 4;
		openList.Add(start);											//1���� ��ʼ����ӵ������б�
		start->status = -2;																											//-2����������


		while (openList.Length() > 0)										//2���ظ����µĹ�����
		{
			currentNode = openList.MinNode().data;						//		a) Ѱ�� �����б���F ֵ��͵ĸ��ӡ����ǳ���Ϊ ��ǰ��
			openList.RemoveByData(currentNode);							//		b) �����л��� �ر��б�
			currentNode->status = -1;																								//-1����رռ���
			UpdateEvery(currentNode, Map, size, end);					//		c) �����ڵĸ��е�ÿһ�����м�����Ž�?

			if (showPath)
				ShowMap(Map, size, false, false, false);

			if (currentNode == end) { break; }							//ֹͣ�������Ŀ�����ӽ��˹ر��б���ʱ��·�����ҵ�
		}
		openList.Clear();

		AstarNode *path = end;

		while (path)
		{
			path->status = 2;
			path = path->parent;
		}
		start->status = 3;
		end->status = 4;
	}
	Timefinish = clock();
	duration = (double)(Timefinish - Timestart);// / CLOCKS_PER_SEC;
	cout << "Ѱ·ʱ��Ϊ" << duration << "����" << endl;
	if (currentNode == end)return true;								
	else return false;												//û���ҵ� Ŀ��� �����б��Ѿ����ˡ���ʱ��·�������ڡ�
}

															/*��ӡ�Թ�����ʵ�֣���ѡ���ӡGFH����ֵ--�����ã�*/
void ShowMap(AstarNode **Map,int size,bool showG, bool showF , bool showH) {
	system("cls");												/*��������*/
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {						/*����Ӧ��ֵ��ӡ����*/
			if (Map[i][j].status == 1) { cout << "��"; }
			else if (Map[i][j].status == 0) { cout << "  "; }
			else if (Map[i][j].status == 2) { cout << "��"; }
			else if (Map[i][j].status == 3) { cout << "��"; }
			else if (Map[i][j].status == 4) { cout << "��"; }
			else if (Map[i][j].status == -2) { cout << "��"; }
			else
			{
				cout << "��";
			}
		}
		cout << endl;
	}
	if (showF) {												/*���showFΪ���ӡ��Ӧ��Fֵ*/
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << Map[i][j].F << "\t";
			}
			cout << endl;
		}
	}
	if (showG) {												/*���showGΪ���ӡ��Ӧ��Fֵ*/
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << Map[i][j].G << "\t";
			}
			cout << endl;
		}
	}
	if (showH) {												/*���showHΪ���ӡ��Ӧ��Fֵ*/
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << Map[i][j].H << "\t";
			}
			cout << endl;
		}
	}
	_sleep(10);													/*������ͣ��߻�������ʱ��*/
}

															/*��ӡ·������ ��Ϊѭ����ӡ�����ڶ��̣߳�*/
void ShowPath(AstarNode **Map, int size) {
	while (true)
	{
		system("cls");
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Map[i][j].status == 1) { cout << "��"; }
				else if (Map[i][j].status == 0) { cout << "  "; }
				else if (Map[i][j].status == 2) { cout << "��"; }
				else if (Map[i][j].status == 3) { cout << "��"; }
				else if (Map[i][j].status == 4) { cout << "��"; }
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}
		_sleep(600);									/*��ͣһ��ʱ�併��ˢ��Ƶ��*/
	}
	
}

															/*main����ʵ��*/
int main() {
	
	//while (true)																		//ѭ��ʹ�����ɶ��ʹ��
	{


		int size = 0;																	//��size��С�������Թ���С
		while (size < 5 || size>60)														//�û������Թ���С���Ҽ����Ӧ��
		{
			system("cls");
			cout << " �� �� �� �� �� �� С ( 5 <= size <= 60 ):" << endl;	
			cin >> size;
		}
		int tempX = 0, tempY = 0;														//��tempXY������������Թ��յ�λ�ò����Ϸ���
		while (tempX < 1 || tempX >= size - 1 || tempY < 1 || tempY >= size - 1)
		{
			system("cls");
			cout << " �� �� �� �� �� �� �� �� �� X Y ( 1 <= X/Y <= " << size - 2 << " ):" << endl;
			cin >> tempX >> tempY;

		}

		srand(unsigned(time(0)));														//����������� ������������Թ�
		int randomIndex;																//��randomIndex���������

		AstarNode **Map = new AstarNode*[size];											//�ö���ָ��Map��̬�����Թ�
		AstarNode *start, *end;															//��start endָ�����洢����յ�
		for (int i = 0; i < size; i++) {												//�ö���ָ��Mapģ���ά���� �����财��ռ�
			AstarNode *Y = new AstarNode[size];
			Map[i] = Y;
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {											//�������鲢��ֵ
				if (i == size - 1 || j == size - 1 || i == 0 || j == 0) { Map[i][j].status = 1; }
				else if (i == size - 2 || j == size - 2 || i == 1 || j == 1)
				{

					randomIndex = rand() / (RAND_MAX / 1.2);							//���������ʼ������ ����1��0�Ķ�ά����
					Map[i][j].status = randomIndex;
				}
				else
				{
					randomIndex = rand() / (RAND_MAX / 1.4);							
					Map[i][j].status = randomIndex;
				}
			}

		}
		start = &Map[1][1];																//��ʼ�����λ�ã�Ĭ�����Ͻǣ�
		start->status = 3;																//����㸶״ֵ̬=3
		end = &Map[tempX][tempY];														//��tempXY��ʼ���յ�λ��
		end->status = 4;																//���յ㸶״ֵ̬=3

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Map[i][j].X = i; Map[i][j].Y = j;										//�Խڵ�XYֵ��ʼ��
				if (Map[i][j].status == 1) { cout << "��"; }
				else if (Map[i][j].status == 0) { cout << "  "; }						//ͬʱ��ӡһ���Թ�
				else if (Map[i][j].status == 3) { cout << "��"; }
				else if (Map[i][j].status == 4) { cout << "��"; }
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}

		system("pause");																//��ͣ����

		bool pathExist = false;
		pathExist = FindPath(start, end, Map, size, false);								//����Ѱ·�������Ҵ�ӡѰ·���� �������ӡ�Ƿ��ҵ�·��

		if (pathExist)cout << "=============== �� �� · �� !=================" << endl;		
		else																			
		{
			cout << "=================== û �� �� · �� ! ! ! ================" << endl;
		}

		for (int i = 0; i < size; i++) {												/*��ӡһ��Ѱ�ҵ���·��*/
			for (int j = 0; j < size; j++) {
				if (Map[i][j].status == 1) { cout << "��"; }
				else if (Map[i][j].status == 0) { cout << "  "; }
				else if (Map[i][j].status == 2) { cout << "��"; }
				else if (Map[i][j].status == 3) { cout << "��"; }
				else if (Map[i][j].status == 4) { cout << "��"; }
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}

		system("pause");																//��ͣ���� ֮�����û�ҵ�·���ͽ���
		if (!pathExist)return 0;//continue;

		thread th1(ShowPath, Map, size);												//��ShowPath�����������̶߳���
		th1.detach();																	//���̷߳��������̵߳�������
		char c;
		while (true)																	/*�ƶ�ѭ����*/
		{
			c = ' ';
			c = getch();																//��ȡ��������
			cout << c << endl;
			switch (c)
			{
			case 's':if (Map[start->X + 1][start->Y].status != 1) {						//�ж����������Ӧ������ƶ������ҵ���Ѱ��·������
				start->status = 0; start = &Map[start->X + 1][start->Y]; start->status = 3; FindPath(start, end, Map, size);
			}break;
			case 'w':if (Map[start->X - 1][start->Y].status != 1) {
				start->status = 0; start = &Map[start->X - 1][start->Y]; start->status = 3; FindPath(start, end, Map, size);
			}break;
			case 'a':if (Map[start->X][start->Y - 1].status != 1) {
				start->status = 0; start = &Map[start->X][start->Y - 1]; start->status = 3; FindPath(start, end, Map, size);
			}break;
			case 'd':if (Map[start->X][start->Y + 1].status != 1) {
				start->status = 0; start = &Map[start->X][start->Y + 1]; start->status = 3; FindPath(start, end, Map, size);
			}break;
			default:
				break;
			}
			if (start == end)break;
		}


		for (int i = 0; i < size; i++) {		
			delete Map[i];																	//���Map�Ĵ���ռ�
		}
		
	//	cout << " �� �� 0 �� �� �� �� �� �� " << endl;
	//	c = getch();
		
	//	if (c != '0')break;																	//������Ϊ��ʱ�˳�ѭ��
		

	}
	return 0;
}

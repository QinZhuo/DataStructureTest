/********************************************************************************************************************
作者：琴卓
日期：2016-10-12-13:40
文件：test.cpp  LinkList.h (需要在C++11的环境)
功能：迷宫问题模拟程序
问题描述：用一个字符类型的二维数组表示迷宫，数组中的每个元素表示一个小方格，取值“0”（通道）或“1”（阻塞物）。设计一个模拟小动物走迷宫的程序，为小动物寻找一条从迷宫入口到迷宫出口的途径小方格最少的最短通路。
要求：设计算法并实现如下功能
（1）用随机函数设置迷宫（用户可以选择迷宫的大小，即多少行多少列）。
（2）选择合适的数据结构表示迷宫。
（3）迷宫入口处的下标是（x0，y0），出口处的下标是（x1，y1），由键盘输入。
（4）输出从入口到出口的最短通路（如存在）或不存在通路的信息。
设计出友好的图形化界面，做到量好的人机交互。


应用算法A*算法
开启集合
关闭集合
添加起始点到 开始集合 中

循环如下步骤：
		当前点= 开启集合 中最小F_Cost 的点
		将 当前点 移出 开启集合 中
		将 当前点 添加到 关闭集合 中

		如果 当前点 是目标点，结束查询

		遍历 当前点 的每个 相邻点
				如果 相邻点 不能访问或者 相邻点 在 关闭集合 中，跳过此 相邻点
				如果新路径到 相邻点 的距离更短，或者 相邻点 不在 开启集合 中
						重新设置F_Cost
						重新设置其父节点为 当前点
				如果 相邻点 不在 开启集合 中
						添加 相邻点 到 开启集合中
*********************************************************************************************************************/


																			/*头文件列表*/
#include<iostream>		
#include<stdlib.h>	
#include<ctime>																					//包含随机数所用头文件
#include<conio.h>																				//getch所用头文件
#include"LinkList.h"																			//链表类模版
#include<thread>																				//多线程所用头文件
using namespace std;

															/*A*寻路所用节点主要为GHF数值*/
struct AstarNode
{
	int status;																					//用来表示节点当前状态 0=可通过 1=障碍物 2=路径 3=起点 4=终点 -1=关闭列表 -2=开启列表
	int G;																						//从起点走到此节点所用花费G	
	int H;																						//此节点距离终点的距离花费H（有多种算法）
	int F;																						//G+H的总花费F
	int X;																						//记录本节点XY的坐标
	int Y;
	AstarNode *parent;																			//父节点指针

	AstarNode() {																				//默认构造函数 进行部分数据初始化
		status = 0;
		G = 0;
		H = 0;
		F = 0;
		parent = NULL;
	}
	void Fupdate() {																			//更新F值的函数
		F = G + H;
	}
	void Hcost(AstarNode *node) {																//H值计算函数
		H= fabs(node->X - X) + fabs(node->Y - Y);
	}
	void Clear() {																				//进行部分数据的初始化
		
		G = 0;
		H = 0;
		F = 0;
		parent = NULL;
	}
	bool operator >(AstarNode other) {															//重载>符号用来寻找F值最小的节点
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

void ShowMap(AstarNode **Map, int size, bool showG = false, bool showF = false, bool showH = false);	//打印迷宫的函数声明
bool Check(int x, int y, AstarNode **Map, int G,int size, AstarNode *end);								//检测节点是否为最优解函数
bool FindPath(AstarNode *start, AstarNode *end, AstarNode **Map, int size, bool showPath=false);		//寻找路径函数声明

LinkList<AstarNode*>  openList;																			//全局变量 开启列表 声明（LinkList<AstarNode*>类模版 对象）

															/*扫描函数实现 扫描该节点四周所有能走的节点*/
void UpdateEvery(AstarNode *node, AstarNode **Map,int size,AstarNode *end) {

	int tempX, tempY;
	tempX = node->X + 1; tempY = node->Y;																//对即诶但四周的每一个节点都调用Check函数
	if (Check(tempX, tempY, Map, node->G,size,end)) {
		Map[tempX][tempY].parent = node;																//更低的G 值意味着更好的路径。如果是这样，就把这一格的父节点改成当前格，并且重新计算这一格的G 和F 值。
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

															/*检测最优解函数实现*/
bool Check(int x,int y, AstarNode **Map,int G,int size,AstarNode *end) {
	if (x >= size || x < 0 || y >= size || y < 0||Map[x][y].status==-1|| Map[x][y].status == 1) {
		return false;													//* 如果它不可通过或者已经在 关闭列表中，略过它。反之如下。
	}
	else if(Map[x][y].status == -2)			
	{
		if (G + 1 < Map[x][y].G) {										//* 如果它已经在 开启列表中，用G 值为参考检查新的路径是否更好。
			Map[x][y].G = G + 1;										//重新计算GF值
			Map[x][y].Fupdate();
			return true;												//低的G 值意味着更好的路径，返回true
		}
		else
		{
			return false;
		}
	}
	else
	{	
		openList.Add(&Map[x][y]);										//如果它不在 开启列表中，把它添加进去
		Map[x][y].status = -2;
		Map[x][y].Hcost(end);
		Map[x][y].G = G + 1;											//把当前格作为这一格的父节点。记录这一格的F,G, 和H 值。
		Map[x][y].Fupdate();
		return true;
	}

}

															/*寻找路径函数实现*/
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
		openList.Add(start);											//1，把 起始格添加到开启列表。
		start->status = -2;																											//-2代表开启集合


		while (openList.Length() > 0)										//2，重复如下的工作：
		{
			currentNode = openList.MinNode().data;						//		a) 寻找 开启列表中F 值最低的格子。我们称它为 当前格。
			openList.RemoveByData(currentNode);							//		b) 把它切换到 关闭列表。
			currentNode->status = -1;																								//-1代表关闭集合
			UpdateEvery(currentNode, Map, size, end);					//		c) 对相邻的格中的每一个进行检测最优解?

			if (showPath)
				ShowMap(Map, size, false, false, false);

			if (currentNode == end) { break; }							//停止，当你把目标格添加进了关闭列表，这时候路径被找到
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
	cout << "寻路时间为" << duration << "毫秒" << endl;
	if (currentNode == end)return true;								
	else return false;												//没有找到 目标格， 开启列表已经空了。这时候，路径不存在。
}

															/*打印迷宫函数实现（可选择打印GFH的数值--测试用）*/
void ShowMap(AstarNode **Map,int size,bool showG, bool showF , bool showH) {
	system("cls");												/*清屏函数*/
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {						/*按对应数值打印符号*/
			if (Map[i][j].status == 1) { cout << "█"; }
			else if (Map[i][j].status == 0) { cout << "  "; }
			else if (Map[i][j].status == 2) { cout << "★"; }
			else if (Map[i][j].status == 3) { cout << "★"; }
			else if (Map[i][j].status == 4) { cout << "◎"; }
			else if (Map[i][j].status == -2) { cout << "□"; }
			else
			{
				cout << "☆";
			}
		}
		cout << endl;
	}
	if (showF) {												/*如果showF为真打印对应点F值*/
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << Map[i][j].F << "\t";
			}
			cout << endl;
		}
	}
	if (showG) {												/*如果showG为真打印对应点F值*/
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << Map[i][j].G << "\t";
			}
			cout << endl;
		}
	}
	if (showH) {												/*如果showH为真打印对应点F值*/
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << Map[i][j].H << "\t";
			}
			cout << endl;
		}
	}
	_sleep(10);													/*短暂暂停提高画面暂留时间*/
}

															/*打印路径函数 内为循环打印（用于多线程）*/
void ShowPath(AstarNode **Map, int size) {
	while (true)
	{
		system("cls");
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (Map[i][j].status == 1) { cout << "█"; }
				else if (Map[i][j].status == 0) { cout << "  "; }
				else if (Map[i][j].status == 2) { cout << "☆"; }
				else if (Map[i][j].status == 3) { cout << "★"; }
				else if (Map[i][j].status == 4) { cout << "◎"; }
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}
		_sleep(600);									/*暂停一段时间降低刷新频率*/
	}
	
}

															/*main函数实现*/
int main() {
	
	//while (true)																		//循环使函数可多次使用
	{


		int size = 0;																	//用size大小来控制迷宫大小
		while (size < 5 || size>60)														//用户输入迷宫大小并且检测适应性
		{
			system("cls");
			cout << " 请 输 入 迷 宫 大 小 ( 5 <= size <= 60 ):" << endl;	
			cin >> size;
		}
		int tempX = 0, tempY = 0;														//用tempXY来储存输入的迷宫终点位置并检测合法性
		while (tempX < 1 || tempX >= size - 1 || tempY < 1 || tempY >= size - 1)
		{
			system("cls");
			cout << " 请 输 入 迷 宫 终 点 坐 标 X Y ( 1 <= X/Y <= " << size - 2 << " ):" << endl;
			cin >> tempX >> tempY;

		}

		srand(unsigned(time(0)));														//启动随机种子 用于随机生成迷宫
		int randomIndex;																//用randomIndex储存随机数

		AstarNode **Map = new AstarNode*[size];											//用二级指针Map动态创建迷宫
		AstarNode *start, *end;															//用start end指针来存储起点终点
		for (int i = 0; i < size; i++) {												//用二级指针Map模拟二维数组 并赋予储存空间
			AstarNode *Y = new AstarNode[size];
			Map[i] = Y;
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {											//遍历数组并赋值
				if (i == size - 1 || j == size - 1 || i == 0 || j == 0) { Map[i][j].status = 1; }
				else if (i == size - 2 || j == size - 2 || i == 1 || j == 1)
				{

					randomIndex = rand() / (RAND_MAX / 1.2);							//用随机数初始化数组 生成1或0的二维数组
					Map[i][j].status = randomIndex;
				}
				else
				{
					randomIndex = rand() / (RAND_MAX / 1.4);							
					Map[i][j].status = randomIndex;
				}
			}

		}
		start = &Map[1][1];																//初始化起点位置（默认左上角）
		start->status = 3;																//给起点付状态值=3
		end = &Map[tempX][tempY];														//用tempXY初始化终点位置
		end->status = 4;																//给终点付状态值=3

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Map[i][j].X = i; Map[i][j].Y = j;										//对节点XY值初始化
				if (Map[i][j].status == 1) { cout << "█"; }
				else if (Map[i][j].status == 0) { cout << "  "; }						//同时打印一遍迷宫
				else if (Map[i][j].status == 3) { cout << "★"; }
				else if (Map[i][j].status == 4) { cout << "◎"; }
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}

		system("pause");																//暂停程序

		bool pathExist = false;
		pathExist = FindPath(start, end, Map, size, false);								//调用寻路函数并且打印寻路过程 结束后打印是否找到路径

		if (pathExist)cout << "=============== 找 到 路 径 !=================" << endl;		
		else																			
		{
			cout << "=================== 没 找 到 路 径 ! ! ! ================" << endl;
		}

		for (int i = 0; i < size; i++) {												/*打印一遍寻找到的路径*/
			for (int j = 0; j < size; j++) {
				if (Map[i][j].status == 1) { cout << "█"; }
				else if (Map[i][j].status == 0) { cout << "  "; }
				else if (Map[i][j].status == 2) { cout << "☆"; }
				else if (Map[i][j].status == 3) { cout << "★"; }
				else if (Map[i][j].status == 4) { cout << "◎"; }
				else
				{
					cout << "  ";
				}
			}
			cout << endl;
		}

		system("pause");																//暂停程序 之后如果没找到路径就结束
		if (!pathExist)return 0;//continue;

		thread th1(ShowPath, Map, size);												//用ShowPath函数创建多线程对象
		th1.detach();																	//让线程分离于主线程单独运行
		char c;
		while (true)																	/*移动循环体*/
		{
			c = ' ';
			c = getch();																//获取键盘输入
			cout << c << endl;
			switch (c)
			{
			case 's':if (Map[start->X + 1][start->Y].status != 1) {						//判断输入进行相应的起点移动，并且调用寻找路径函数
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
			delete Map[i];																	//清空Map的储存空间
		}
		
	//	cout << " 输 入 0 继 续 其 他 退 出 " << endl;
	//	c = getch();
		
	//	if (c != '0')break;																	//当如入为零时退出循环
		

	}
	return 0;
}

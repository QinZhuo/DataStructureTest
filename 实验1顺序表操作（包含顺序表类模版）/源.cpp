/********************************************************************************************************************
作者：琴卓
日期：2016-9-8-15:40
文件：源.cpp
功能：顺序表操作（包含顺序表类模版）
1、设线性表的数据元素都为整数，存放在顺序表S中且递增有序。设计算法，将x插入到顺序表S的适当位置上，以保持线性表的有序性。
2、线性表使用顺序表作存储结构，设计算法，仅用一个辅助结点，实现将顺序表中的结点循环右移k位的运算。
3、设计算法，仅用一个辅助结点，实现将顺序存储的线性表中的数据元素逆置。
*********************************************************************************************************************/

#include<iostream>
using namespace std;													

#define LIST_INIT_SIZE 100														//定义顺序表最大存储
#define LIST_TEMP_SIZE 1														//定义顺序表辅助空间大小

template <class ElemType> class SqList											//声明线性顺序表模版类
{
public:
	void ClearList() {															//清空顺序表数据函数
		length = 0;																//长度归零
	}
	bool ListEmpty() {															//检测顺序表是否为空
		if (0 == length) {
			return true;														//为空返回真 反之返回假
		}
		else
		{
			return false;
		}
	}
	int ListLength() {															//获取顺序表长度函数
		return length;
	}
	int LocateElem(ElemType data, bool (*equal)(ElemType, ElemType)=NULL) {		//定位数据函数 可赋值函数指针（自定义比较方式）
		int i = 1;
		ElemType* p = elem;														//定义数据类型的指针
		if (equal) {															//当函数指针不为空时执行以下操作
			while (i <= length&& !(*equal)(*p++, data))++i;						
		}
		else
		{
			while (i <= length&& data!=*p++)++i;								//当函数指针为空时进行默认比较方式
		}
		if (i <= length)return i;												//如果位置合法 返回数据在顺序表中第几个
		else return 0;
	}
	bool Push(ElemType data,int (*compare)(ElemType,ElemType)=NULL) {			//添加操作函数  可赋值函数指针（自定义比较方式）
		if (length > maxSize) { return false; }									//判断是否超过储存上限
		if (length <= 0) {														//当顺序表为空时 直接插入数据
			elem[length] = data;
			length++;
		}
		else
		{
			int i = 0;
			while (i<length)
			{
				if (!compare) {													//函数指针为空是 进行默认比较 插入操作
					if (elem[i]>data) {											//如果插入数据小于顺序表数据进行以下操作
						ElemType *q = &elem[i];
						ElemType *p;
						for (p = &elem[length - 1]; p >= q;) {					//将大于插入数据的数据元全部后移一位
							*(p + 1) = *p;
							--p;
						}
						*q = data;
						length++;
						break;													//插入完成跳出循环
					}
					else
					{
						i++;
					}
					
				}
				
			}
			if (i==length)														//如果插入数据大于所有顺序表数据 则将数据插入末尾
			{
				elem[length] = data;
				length++;
			}
			
			return true;
		}
		
	}
	bool RotateRight(int k) {													//循环右移函数
		if (k <= LIST_TEMP_SIZE&&k >= 0) {
			ElemType *q = elem;
			ElemType *p;
			for (p = &elem[length - 1]; p >= q; --p)									//将数据表整体右移k位
			{
				*(p + k) = *p;
			}
			for (p = &elem[length]; p <= &elem[length + k - 1]; ++p, ++q) {			//将超出的数据移动到顺序表前端
				*q = *p;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	void Invert() {																//数据逆至函数
		ElemType *q=&elem[0];
		ElemType *p=&elem[length-1];
		ElemType dataTemp;
		while (p>q)																//首尾交换 并移动指针
		{
			dataTemp = *q;
			*q = *p;
			*p = dataTemp;
			q++;
			p--;
		}
	}
	
	SqList() {																	//默认构造函数 进行顺序表的初始化
		elem = new ElemType[LIST_INIT_SIZE+LIST_TEMP_SIZE];
		if (!elem)exit(1);
		length = 0;
		maxSize = LIST_INIT_SIZE;
	}
	~SqList() {																	//析构函数 进行顺序表的内存释放
		delete[] elem;
	}
	bool ListDelete(int i) {													//主动删除一个节点
		if (i<1 || i>length)return false;
		ElemType *p = &(elem[i - 1]);
		ElemType *q = elem + length - 1;
		for (++p; p <= q; ++p)*(p - 1) = *p;
		return true;
	}
	bool ListTraverse(bool(*visit)(ElemType)) {									//遍历函数 将顺序表 依次执行指针指向的函数
		int i = 1;
		ElemType* p = elem;
		while (i <= length && (*visit)(*p++))
		{
			++i;
		}
		return true;
	}
private:
	ElemType *elem;																//数据首地址
	int length;																	//当前长度
	int maxSize;																//最大长度
};


bool equal(int a, int b) {														//比较函数
	if (a == b)return true;
	return false;
}												

bool show(int e) {																//展示函数
	cout <<"    "<< e << "    ";
	return true;
}


int main() {
	SqList<int> L;																//创建顺序表数据对象
	int n = 0;
	while (n<5)																	//执行5次数据输入并展示
	{

		cout << " 请 输 入 数 据 ：" << endl<<endl;
		int i = 0;
		cin >> i;
		L.Push(i);
		system("cls");
		cout << " 数 据 展 示 结 果 ：" << endl<<endl << "***************************************************************************" << endl;
		L.ListTraverse(show);													//调用遍历函数展示数据
		cout << endl<<"***************************************************************************" <<endl;
		n++;
	}
	cout << " 逆 至 数 据 展 示 结 果 ：" << endl<<endl << "***************************************************************************" << endl;
	L.Invert();																	//调用逆至函数并展示
	L.ListTraverse(show);
	L.Invert();																	//逆至回元函数
	cout << endl << "***************************************************************************" << endl;
	n = 3;
	cout << " 循 环 右 移 " << n << " 位 展 示 结 果 ：" << endl<<endl<<"***************************************************************************"<<endl;
	for (int i = 0; i < 3;i++)
	L.RotateRight(1);															//循环右移1位3次并展示
	L.ListTraverse(show);
	cout << endl << "***************************************************************************" << endl;
	return 0;
}

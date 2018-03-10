/********************************************************************************************************************
���ߣ���׿
���ڣ�2016-9-8-15:40
�ļ���Դ.cpp
���ܣ�˳������������˳�����ģ�棩
1�������Ա������Ԫ�ض�Ϊ�����������˳���S���ҵ�����������㷨����x���뵽˳���S���ʵ�λ���ϣ��Ա������Ա�������ԡ�
2�����Ա�ʹ��˳������洢�ṹ������㷨������һ��������㣬ʵ�ֽ�˳����еĽ��ѭ������kλ�����㡣
3������㷨������һ��������㣬ʵ�ֽ�˳��洢�����Ա��е�����Ԫ�����á�
*********************************************************************************************************************/

#include<iostream>
using namespace std;													

#define LIST_INIT_SIZE 100														//����˳������洢
#define LIST_TEMP_SIZE 1														//����˳������ռ��С

template <class ElemType> class SqList											//��������˳���ģ����
{
public:
	void ClearList() {															//���˳������ݺ���
		length = 0;																//���ȹ���
	}
	bool ListEmpty() {															//���˳����Ƿ�Ϊ��
		if (0 == length) {
			return true;														//Ϊ�շ����� ��֮���ؼ�
		}
		else
		{
			return false;
		}
	}
	int ListLength() {															//��ȡ˳����Ⱥ���
		return length;
	}
	int LocateElem(ElemType data, bool (*equal)(ElemType, ElemType)=NULL) {		//��λ���ݺ��� �ɸ�ֵ����ָ�루�Զ���ȽϷ�ʽ��
		int i = 1;
		ElemType* p = elem;														//�����������͵�ָ��
		if (equal) {															//������ָ�벻Ϊ��ʱִ�����²���
			while (i <= length&& !(*equal)(*p++, data))++i;						
		}
		else
		{
			while (i <= length&& data!=*p++)++i;								//������ָ��Ϊ��ʱ����Ĭ�ϱȽϷ�ʽ
		}
		if (i <= length)return i;												//���λ�úϷ� ����������˳����еڼ���
		else return 0;
	}
	bool Push(ElemType data,int (*compare)(ElemType,ElemType)=NULL) {			//��Ӳ�������  �ɸ�ֵ����ָ�루�Զ���ȽϷ�ʽ��
		if (length > maxSize) { return false; }									//�ж��Ƿ񳬹���������
		if (length <= 0) {														//��˳���Ϊ��ʱ ֱ�Ӳ�������
			elem[length] = data;
			length++;
		}
		else
		{
			int i = 0;
			while (i<length)
			{
				if (!compare) {													//����ָ��Ϊ���� ����Ĭ�ϱȽ� �������
					if (elem[i]>data) {											//�����������С��˳������ݽ������²���
						ElemType *q = &elem[i];
						ElemType *p;
						for (p = &elem[length - 1]; p >= q;) {					//�����ڲ������ݵ�����Ԫȫ������һλ
							*(p + 1) = *p;
							--p;
						}
						*q = data;
						length++;
						break;													//�����������ѭ��
					}
					else
					{
						i++;
					}
					
				}
				
			}
			if (i==length)														//����������ݴ�������˳������� �����ݲ���ĩβ
			{
				elem[length] = data;
				length++;
			}
			
			return true;
		}
		
	}
	bool RotateRight(int k) {													//ѭ�����ƺ���
		if (k <= LIST_TEMP_SIZE&&k >= 0) {
			ElemType *q = elem;
			ElemType *p;
			for (p = &elem[length - 1]; p >= q; --p)									//�����ݱ���������kλ
			{
				*(p + k) = *p;
			}
			for (p = &elem[length]; p <= &elem[length + k - 1]; ++p, ++q) {			//�������������ƶ���˳���ǰ��
				*q = *p;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	void Invert() {																//������������
		ElemType *q=&elem[0];
		ElemType *p=&elem[length-1];
		ElemType dataTemp;
		while (p>q)																//��β���� ���ƶ�ָ��
		{
			dataTemp = *q;
			*q = *p;
			*p = dataTemp;
			q++;
			p--;
		}
	}
	
	SqList() {																	//Ĭ�Ϲ��캯�� ����˳���ĳ�ʼ��
		elem = new ElemType[LIST_INIT_SIZE+LIST_TEMP_SIZE];
		if (!elem)exit(1);
		length = 0;
		maxSize = LIST_INIT_SIZE;
	}
	~SqList() {																	//�������� ����˳�����ڴ��ͷ�
		delete[] elem;
	}
	bool ListDelete(int i) {													//����ɾ��һ���ڵ�
		if (i<1 || i>length)return false;
		ElemType *p = &(elem[i - 1]);
		ElemType *q = elem + length - 1;
		for (++p; p <= q; ++p)*(p - 1) = *p;
		return true;
	}
	bool ListTraverse(bool(*visit)(ElemType)) {									//�������� ��˳��� ����ִ��ָ��ָ��ĺ���
		int i = 1;
		ElemType* p = elem;
		while (i <= length && (*visit)(*p++))
		{
			++i;
		}
		return true;
	}
private:
	ElemType *elem;																//�����׵�ַ
	int length;																	//��ǰ����
	int maxSize;																//��󳤶�
};


bool equal(int a, int b) {														//�ȽϺ���
	if (a == b)return true;
	return false;
}												

bool show(int e) {																//չʾ����
	cout <<"    "<< e << "    ";
	return true;
}


int main() {
	SqList<int> L;																//����˳������ݶ���
	int n = 0;
	while (n<5)																	//ִ��5���������벢չʾ
	{

		cout << " �� �� �� �� �� ��" << endl<<endl;
		int i = 0;
		cin >> i;
		L.Push(i);
		system("cls");
		cout << " �� �� չ ʾ �� �� ��" << endl<<endl << "***************************************************************************" << endl;
		L.ListTraverse(show);													//���ñ�������չʾ����
		cout << endl<<"***************************************************************************" <<endl;
		n++;
	}
	cout << " �� �� �� �� չ ʾ �� �� ��" << endl<<endl << "***************************************************************************" << endl;
	L.Invert();																	//��������������չʾ
	L.ListTraverse(show);
	L.Invert();																	//������Ԫ����
	cout << endl << "***************************************************************************" << endl;
	n = 3;
	cout << " ѭ �� �� �� " << n << " λ չ ʾ �� �� ��" << endl<<endl<<"***************************************************************************"<<endl;
	for (int i = 0; i < 3;i++)
	L.RotateRight(1);															//ѭ������1λ3�β�չʾ
	L.ListTraverse(show);
	cout << endl << "***************************************************************************" << endl;
	return 0;
}

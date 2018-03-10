
/********************************************************************************************************************
���ߣ���׿
���ڣ�2016-12-8-17:10
�ļ���test.cpp 
���ܣ������㷨�������ʵ��
1���÷��η������ʵ�ֹ鲢�����㷨��
2�� ��������n��Ԫ�صĶ��ؼ���S��ÿ��Ԫ����S�г��ֵĴ�����Ϊ��Ԫ�ص����������ؼ���S����������Ԫ�س�Ϊ���������磬���ؼ���S = { 1,2,2,7,2,7,5 }������������2��������Ϊ3���÷��η���Ʋ�ʵ���ڶ��ؼ����������������������㷨��Ҫ���㷨��ʱ�临�����ڻ�����²�����O(nlogn)��
Ҫ�������÷��η�����㷨�ķ���������ѡ���ʺϵ����ݽṹ��������ʵ������Ƶķ����㷨��ʹ�㷨�����Ծ����ܵ͡�
*********************************************************************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;
#define MAX_MERGESORT_INT 100

int num = 0;
int sum = 0;


/*����Ϊ�鲢�������*/
/***************************************************************************************************************/
void Merge(int *r, int *t, int low, int mid, int high) {				
	int i = low, j = mid + 1, k = low;
	while (i <= mid&&j <= high)
	{
		if (r[i] < r[j])t[k++] = r[i++];
		else t[k++] = r[j++];
	}
	while (i <= mid)
	{
		t[k++] = r[i++];
	}
	while (j <= high)
	{
		t[k++] = r[j++];
	}
}
void MSort(int *r, int *t, int low, int high) {
	if (low == high)t[low] = r[low];
	else
	{
		int s[100];
		int mid = (low + high) / 2;
		MSort(r, s, low, mid);
		MSort(r, s, mid + 1, high);
		Merge(s, t, low, mid, high);
	}
}
void MergeSort(int *L, int size) {
	MSort(L, L, 0, size - 1);
}
/********************************************************************************************************/


int count(int a[], int min, int max) {						//���м�Ԫ�ؽ��м�������
	int mid = (min + max) / 2;								//�����м�Ԫ���±�
	int n = a[mid];											//��¼Ԫ����ֵ
	int counts = 0;					
	for (int i = mid; i < max; i++) {						//���Ԫ���Ҳ���Ԫ����ͬ������һ
		if (a[i] == n) {
			counts++;
		}
		else
		{
			break;
		}
	}
	for (int i = mid-1; i >= min; i--) {					//���Ԫ�������Ԫ����ͬ������һ
		if (a[i] == n) {
			counts++;
		}
		else
		{
			break;
		}
	}
	return counts;
}
int start(int a[], int min, int max) {						//������м�Ԫ����ͬ�ĵ�һ��λ�õ��±�
	int x = 0;
	int mid = a[(min + max) / 2];							
	for (int i = min; i < max; i++) {						//��¼��һ����ͬԪ�ص��±�
		if (a[i] ==mid ){
			x = i;
			break;
		}
	}
	return x;												//�����±�
}
void Mode(int a[], int min, int max) {						//����������������
	int mid = (min + max) / 2;								//�м�λ���±�
	int midSum = count(a, min, max);						//�����м�λ��Ԫ�ظ���
	int left = start(a, min, max);							//��ȡ�м�λ��Ԫ���������ͬԪ��
	if (midSum > sum) {										//��������������������������������������
		sum = midSum;
		num = a[mid];
	}
	if (max - (left + midSum) > sum) {						//���Ҳ�ʣ����Ŀ���ڵ�ǰ����������ʱ�ݹ����Ҳ�����
		Mode(a,left+midSum, max);
	}
	if (left > sum) {										//�����ʣ����Ŀ���ڵ�ǰ����������ʱ�ݹ����������
		Mode(a, 0, left);
	}
}
int main() {
	int a[10];
	cout << "������10�����������ϣ�" << endl;
	for (int i = 0; i <10; i++)
	{
		cin >> a[i];											//��ȡ���ϵ�����
	}
	MergeSort(a, 10);											//���й鲢����
	cout << "�����ݼ��Ϲ鲢�����������Ϊ��" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout<< a[i]<<" ";											//���й鲢��������
	}
	
	Mode(a, 0, 10);												//�����������ĺ���
	cout <<endl<< "���ϵ�����Ϊ��" << num << "��������������Ϊ��" << sum << endl;
	return 0;
}
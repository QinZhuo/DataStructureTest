
/********************************************************************************************************************
作者：琴卓
日期：2016-12-8-17:10
文件：test.cpp 
功能：分治算法的设计与实现
1、用分治法设计与实现归并排序算法。
2、 给定含有n个元素的多重集合S，每个元素在S中出现的次数称为该元素的重数。多重集合S中重数最大的元素称为众数。例如，多重集合S = { 1,2,2,7,2,7,5 }，其中众数是2，其重数为3。用分治法设计并实现在多重集合中找众数及其重数的算法，要求算法的时间复杂性在坏情况下不超过O(nlogn)。
要求：掌握用分治法设计算法的方法，并能选择适合的数据结构，在其上实现所设计的分治算法，使算法复杂性尽可能低。
*********************************************************************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;
#define MAX_MERGESORT_INT 100

int num = 0;
int sum = 0;


/*下列为归并排序代码*/
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


int count(int a[], int min, int max) {						//对中间元素进行计数函数
	int mid = (min + max) / 2;								//所求中间元素下标
	int n = a[mid];											//记录元素数值
	int counts = 0;					
	for (int i = mid; i < max; i++) {						//如果元素右侧有元素相同计数加一
		if (a[i] == n) {
			counts++;
		}
		else
		{
			break;
		}
	}
	for (int i = mid-1; i >= min; i--) {					//如果元素左侧有元素相同计数加一
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
int start(int a[], int min, int max) {						//计算和中间元素相同的第一个位置的下标
	int x = 0;
	int mid = a[(min + max) / 2];							
	for (int i = min; i < max; i++) {						//记录第一个相同元素的下标
		if (a[i] ==mid ){
			x = i;
			break;
		}
	}
	return x;												//返回下标
}
void Mode(int a[], int min, int max) {						//计算数组众数函数
	int mid = (min + max) / 2;								//中间位置下表
	int midSum = count(a, min, max);						//计算中间位置元素个数
	int left = start(a, min, max);							//获取中间位置元素最左侧相同元素
	if (midSum > sum) {										//如果所求众数比已求众数的重数大则更改众数
		sum = midSum;
		num = a[mid];
	}
	if (max - (left + midSum) > sum) {						//当右侧剩余数目大于当前众数的重数时递归求右侧众数
		Mode(a,left+midSum, max);
	}
	if (left > sum) {										//当左侧剩余数目大于当前众数的重数时递归求左侧众数
		Mode(a, 0, left);
	}
}
int main() {
	int a[10];
	cout << "请输入10个无序数集合：" << endl;
	for (int i = 0; i <10; i++)
	{
		cin >> a[i];											//获取集合的输入
	}
	MergeSort(a, 10);											//进行归并排序
	cout << "对数据集合归并排序后输出结果为：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout<< a[i]<<" ";											//进行归并排序后输出
	}
	
	Mode(a, 0, 10);												//调用求众数的函数
	cout <<endl<< "集合的众数为：" << num << "集合众数的重数为：" << sum << endl;
	return 0;
}
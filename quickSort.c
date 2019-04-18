#include <stdio.h>

//퀵정렬 QuickSort
int partition(int A[], int p, int r)
{
	int pivot = A[p]; // pivot, 기준원소는 맨 첫번째 원소, *기준원소보다 작은구역을 왼구역, 큰구역을 오른구역이라 하자.
	int i = p + 1; // i: 왼 구역의 끝 지점 + 1
	for (int j = p + 1; j <= r; j++) // j: 왼구역과 오른구역을 나누기 위해 순서대로 A[p+1...r]까지 조사
	{
		if (A[j] <= pivot) // 첫번째원소보다 j번째 원소가 작으면
		{
			int temp = A[i]; // j번째 원소를 왼구역으로 가져옴.
			A[i] = A[j];
			A[j] = temp;
			i = i + 1;
		}
	}
	int temp2 = A[i - 1]; // 기준원소와 왼구역 가장 끝 지점 교환
	A[i - 1] = A[p];
	A[p] = temp2;
	return i - 1; // i - 1 은 왼구역의 가장 끝 지점이다.
}
void quickSort(int A[], int p, int r) // A[p...r]에서 첫번째 포인터와 인덱스 p, r을 인수로 받음.
{
	if (p < r)
	{
		int q = partition(A, p, r); // 분할하여 왼구역의 가장 끝 지점을 q에 저장.
		quickSort(A, p, q - 1); // pivot기준 뒷쪽 배열 재귀호출
		quickSort(A, q + 1, r); // pivot기준 앞쪽 배열 재귀호출
	}
}

int main(){
	return 0;
}

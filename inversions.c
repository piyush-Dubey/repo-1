#include <stdio.h>
#include <stdlib.h>
#define ROW 100000

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int* a, int* b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

// Returns new index of pivot
int partition(int*  ar, int left, int right) 
{
	int p = ar[left];
	int j = left + 1;
	int i = left + 1;
	for(j; j <= right; j++)
	{
		if(ar[j] < p)
		{
			swap((ar + i), (ar + j));
			i++;
		}
	}
	swap(ar + i - 1, ar + left);
	return i - 1;
}

// Function implementing the quicksort algorithm
void quickSort(int* arr, int left, int right)
{
	if(left < right)
	{
		int mid = partition(arr, left, right);
		quickSort(arr, left, mid - 1);
		quickSort(arr, mid + 1, right);
	}
}

int split_inversions(int* arr, int left, int right)
{
	int size = right - left + 1;
	if(size == 2)
		return (arr[right] > arr[left]) ? 0 : 1;
	int mid = (left + right) / 2;
	quickSort(arr, left, mid);
	quickSort(arr, mid + 1, right);
	int i = left, j = mid + 1;
	int count = 0;
	while(i <= mid && j <= right)
	{
		if(arr[i] < arr[j])
		{
			i++;
		}
		else if(arr[i] >= arr[j])
		{
			j++;
			count += mid - i + 1;
		}
	}
	return count;
}

int tot_inversions(int arr[], int left, int right)
{
	int left_inversions, right_inversions, cross_inversions;
	int size = right - left + 1;
	if(size == 1)
		return 0;
	if(size == 2)
		return split_inversions(arr, left, right);
	int mid = (left + right) / 2;
	left_inversions = tot_inversions(arr, left, mid);
	printf("Left inversions : %d\n",left_inversions);
	getchar();
	right_inversions = tot_inversions(arr, mid + 1, right);
	printf("Right inversions : %d\n", right_inversions);
	getchar();
	cross_inversions = split_inversions(arr, left, right);
	printf("Cross inversions : %d\n", cross_inversions);
	getchar();
	return left_inversions + right_inversions + cross_inversions;
}

int main(void)
{
	int i;
	int arr[ROW];
	for(i = 0; i < ROW; i++)
		scanf("%d\n",arr + i);
	int inversions = tot_inversions(arr, 0, ROW - 1);
	printf("The number of inversions is: %d\n", inversions);
}

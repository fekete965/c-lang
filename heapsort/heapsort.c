#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buildMaxHeap(int *arr, int size);
void printNumbers(int *arr, int size);
void heapSort(int *arr, int size);
void maxHeapify(int *arr, int heapSize, int index);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t     Heapsort\t\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted array\n");
  printNumbers(nums, size);

  heapSort(nums, size);

  printf("\nSorted array\n");
  printNumbers(nums, size);

  return 0;
}

void printNumbers(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf(" %d ", arr[i]);
  }

  printf("\n");
}

void buildMaxHeap(int *arr, int size)
{
  for (int i = floor(size / 2) + 1; i >= 0; i--)
  {
    maxHeapify(arr, size, i);
  }
}

void maxHeapify(int *arr, int heapSize, int index)
{
  int left = 2 * index;
  int right = left + 1;

  int largest = index;

  if (left < heapSize && arr[left] > arr[largest])
  {
    largest = left;
  }

  if (right < heapSize && arr[right] > arr[largest])
  {
    largest = right;
  }

  if (largest != index)
  {
    swap(&arr[largest], &arr[index]);
    maxHeapify(arr, heapSize, largest);
  }
}

void heapSort(int *arr, int size)
{
  buildMaxHeap(arr, size);

  for (int i = size - 1; i > -1; i--)
  {
    swap(&arr[0], &arr[i]);

    maxHeapify(arr, i, 0);
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

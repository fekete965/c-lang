#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buildMaxHeap(int *list, int size);
void printNumbers(int *list, int size);
void heapsort(int *list, int size);
void maxHeapify(int *list, int heapSize, int index);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int listSize = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t     Heapsort\t\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted list\n");
  printNumbers(nums, listSize);

  heapsort(nums, listSize);

  printf("\nSorted list\n");
  printNumbers(nums, listSize);

  return 0;
}

void printNumbers(int *list, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf(" %d ", list[i]);
  }

  printf("\n");
}

void buildMaxHeap(int *list, int size)
{
  for (int i = floor(size / 2) + 1; i >= 0; i--)
  {
    maxHeapify(list, size, i);
  }
}

void maxHeapify(int *list, int heapSize, int index)
{
  int left = 2 * index;
  int right = 2 * index + 1;

  int largest = index;

  if (left < heapSize && list[left] > list[index])
  {
    largest = left;
  }

  if (right < heapSize && list[right] > list[largest])
  {
    largest = right;
  }

  if (largest != index)
  {
    swap(&list[largest], &list[index]);
    maxHeapify(list, heapSize, largest);
  }
}

void heapsort(int *list, int size)
{
  buildMaxHeap(list, size);

  for (int i = size - 1; i > -1; i--)
  {
    swap(&list[0], &list[i]);

    maxHeapify(list, i, 0);
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

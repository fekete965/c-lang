#include <stdio.h>

void printNumbers(int *arr, int size);
void quicksort(int *arr, int start, int end);
int partition(int *arr, int start, int end);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Quicksort\t\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted array\n");
  printNumbers(nums, size);

  quicksort(nums, 0, size - 1);

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

void quicksort(int *arr, int start, int end)
{
  if (end <= start)
  {
    return;
  }

  int pivot = partition(arr, start, end);
  quicksort(arr, start, pivot - 1);
  quicksort(arr, pivot + 1, end);
}

int partition(int *arr, int start, int end)
{
  int pivot = arr[end];
  int i = start - 1;

  for (int j = start; j < end; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  i++;
  swap(&arr[i], &arr[end]);

  return i;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

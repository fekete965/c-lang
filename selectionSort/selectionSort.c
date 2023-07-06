#include <stdio.h>

void printNumbers(int *arr, int size);
void selectionSort(int *arr, int size);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Selection Sort\t\t|\n");
  printf("-----------------------------------------\n");

  printf("\nUnsorted array\n");
  printNumbers(nums, size);

  selectionSort(nums, size);

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

void selectionSort(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    int minIdx = i;

    for (int j = i + 1; j < size; j++)
    {
      if (arr[minIdx] > arr[j])
      {
        minIdx = j;
      }
    }

    if (minIdx != i)
    {
      swap(&arr[i], &arr[minIdx]);
    }
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

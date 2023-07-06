#include <stdio.h>

void printNumbers(int *arr, int size);
void bubbleSort(int *arr, int size);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Bubble Sort\t\t|\n");
  printf("-----------------------------------------\n");

  printf("\nUnsorted array\n");
  printNumbers(nums, size);

  bubbleSort(nums, size);

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

void bubbleSort(int *arr, int size)
{

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if (arr[j + 1] < arr[j])
      {
        swap(&arr[j + 1], &arr[j]);
      }
    }
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

#include <stdio.h>

void printNumbers(int *arr, int size);
void insertionSort(int *arr, int size);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t  Insertion Sort\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted array\n");
  printNumbers(nums, size);

  insertionSort(nums, size);

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

void insertionSort(int *arr, int size)
{
  int temp;

  for (int i = 1; i < size; i++)
  {
    temp = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > temp)
    {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = temp;
  }
}

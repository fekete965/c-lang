#include <stdio.h>

void printNumbers(int *list, int size);
void insertionSort(int *list, int size);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int listSize = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t  Insertion Sort\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted list\n");
  printNumbers(nums, listSize);

  insertionSort(nums, listSize);

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

void insertionSort(int *list, int size)
{
  int temp;

  for (int i = 1; i < size; i++)
  {
    temp = list[i];
    int j = i - 1;

    while (j >= 0 && list[j] > temp)
    {
      list[j + 1] = list[j];
      j--;
    }

    list[j + 1] = temp;
  }
}

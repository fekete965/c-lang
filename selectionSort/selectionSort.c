#include <stdio.h>

void printNumbers(int *list, int size);
void selectionSort(int *list, int size);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int listSize = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Selection Sort\t\t|\n");
  printf("-----------------------------------------\n");

  printf("\nUnsorted list\n");
  printNumbers(nums, listSize);

  selectionSort(nums, listSize);

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

void selectionSort(int *list, int size)
{
  for (int i = 0; i < size; i++)
  {
    int minIdx = i;

    for (int j = i + 1; j < size; j++)
    {
      if (list[minIdx] > list[j])
      {
        minIdx = j;
      }
    }

    if (minIdx != i)
    {
      swap(&list[i], &list[minIdx]);
    }
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

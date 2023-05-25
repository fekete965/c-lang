#include <stdio.h>

void printNumbers(int *list, int size);
void bubbleSort(int *list, int size);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int listSize = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Bubble Sort\t\t|\n");
  printf("-----------------------------------------\n");

  printf("\nUnsorted list\n");
  printNumbers(nums, listSize);

  bubbleSort(nums, listSize);

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

void bubbleSort(int *list, int size)
{

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if (list[j + 1] < list[j])
      {
        swap(&list[j + 1], &list[j]);
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

#include <stdio.h>

void printNumbers(int *list, int size);
void quickSort(int *list, int start, int end);
int partition(int *list, int start, int end);
void swap(int *a, int *b);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int listSize = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Quick Sort\t\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted list\n");
  printNumbers(nums, listSize);

  quickSort(nums, 0, listSize);

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

void quickSort(int *list, int start, int end)
{
  if (end <= start)
  {
    return;
  }

  int pivot = partition(list, start, end);
  quickSort(list, start, pivot - 1);
  quickSort(list, pivot + 1, end);
}

int partition(int *list, int start, int end)
{
  int pivot = list[end];
  int i = start - 1;

  for (int j = start; j < end; j++)
  {
    if (list[j] < pivot)
    {
      i++;
      swap(&list[i], &list[j]);
    }
  }

  i++;
  swap(&list[i], &list[end]);

  return i;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

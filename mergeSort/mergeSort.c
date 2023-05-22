#include <stdio.h>

void printNumbers(int *list, int size);
void mergeSort(int *list, int size);
void merge(int *left, int leftSize, int *right, int rightSize, int *list);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Merge Sort\t\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted list\n");
  printNumbers(nums, size);

  mergeSort(nums, size);

  printf("\nSorted list\n");
  printNumbers(nums, size);

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

void mergeSort(int *list, int size)
{
  if (size <= 1)
  {
    return;
  }

  int leftSize = size / 2;
  int rightSize = size - leftSize;

  int left[leftSize];
  int right[rightSize];

  int i = 0;
  int j = 0;

  for (; i < size; i++)
  {
    if (i < leftSize)
    {
      left[i] = list[i];
    }
    else
    {
      right[j] = list[i];
      j++;
    }
  }

  mergeSort(left, leftSize);
  mergeSort(right, rightSize);
  merge(left, leftSize, right, rightSize, list);
}

void merge(int *left, int leftSize, int *right, int rightSize, int *list)
{
  int i = 0;
  int l = 0;
  int r = 0;

  while (l < leftSize && r < rightSize)
  {
    if (left[l] < right[r])
    {
      list[i] = left[l];
      l++;
    }
    else
    {
      list[i] = right[r];
      r++;
    }

    i++;
  }

  while (l < leftSize)
  {
    list[i] = left[l];
    i++;
    l++;
  }

  while (r < rightSize)
  {
    list[i] = right[r];
    i++;
    r++;
  }
}

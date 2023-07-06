#include <stdio.h>

void printNumbers(int *arr, int size);
void mergeSort(int *arr, int size);
void merge(int *left, int leftSize, int *right, int rightSize, int *arr);

int main()
{
  int nums[] = {8, 10, 6, 4, 5, 7, 3, 1, 9, 2};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t   Merge Sort\t\t|\n");
  printf("---------------------------------\n");

  printf("\nUnsorted array\n");
  printNumbers(nums, size);

  mergeSort(nums, size);

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

void mergeSort(int *arr, int size)
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
      left[i] = arr[i];
    }
    else
    {
      right[j] = arr[i];
      j++;
    }
  }

  mergeSort(left, leftSize);
  mergeSort(right, rightSize);
  merge(left, leftSize, right, rightSize, arr);
}

void merge(int *left, int leftSize, int *right, int rightSize, int *arr)
{
  int i = 0;
  int l = 0;
  int r = 0;

  while (l < leftSize && r < rightSize)
  {
    if (left[l] < right[r])
    {
      arr[i] = left[l];
      l++;
    }
    else
    {
      arr[i] = right[r];
      r++;
    }

    i++;
  }

  while (l < leftSize)
  {
    arr[i] = left[l];
    i++;
    l++;
  }

  while (r < rightSize)
  {
    arr[i] = right[r];
    i++;
    r++;
  }
}

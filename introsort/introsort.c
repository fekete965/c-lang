#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void print_numbers(int *arr, int size);
void intro_sort(int *arr, int start, int end, int maxDepth);
void insertion_sort(int *arr, int start, int end);
void build_max_heap(int *arr, int start, int end);
void heap_sort(int *arr, int start, int end);
void max_heapify(int *arr, int heapSize, int index);
void swap(int *a, int *b);
int partition_rand(int *arr, int start, int end);
int partition(int *arr, int start, int end);

int main()
{
  srand(time(NULL));

  int nums[] = {2, 26, 24, 17, 10, 27, 4, 19, -3, 20,
                77, 99, 120, -62, 9, 13, 12, 22, 50, 0,
                -24, 42, 1, 3, 23, -10, 8, 113, 60, -5};
  int size = sizeof(nums) / sizeof(nums[0]);

  printf("\n|\t  Introspective Sort\t|\n");
  printf("------------------------------------\n");

  printf("\nUnsorted array\n");
  print_numbers(nums, size);

  int maxDepth = log(size) * 2;
  intro_sort(nums, 0, size - 1, maxDepth);

  printf("\nSorted array\n");
  print_numbers(nums, size);

  return 0;
}

void print_numbers(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf(" %d ", arr[i]);
  }
  printf("\n");
}

void intro_sort(int *arr, int start, int end, int maxDepth)
{
  if ((end - start) < 16)
  {
    insertion_sort(arr, start, end);
  }
  else if (maxDepth == 0)
  {
    heap_sort(arr, start, end);
  }
  else
  {
    int p = partition(arr, start, end);
    intro_sort(arr, start, p - 1, maxDepth - 1);
    intro_sort(arr, p + 1, end, maxDepth - 1);
  }
}

void insertion_sort(int *arr, int start, int end)
{
  for (int i = start + 1; i <= end; i++)
  {
    int tmp = arr[i];
    int j = i;

    while (j > start && arr[j - 1] > tmp)
    {
      arr[j] = arr[j - 1];
      j--;
    }

    arr[j] = tmp;
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void build_max_heap(int *arr, int start, int end)
{
  for (int i = floor((end - start) / 2) + 1; i >= 0; i--)
  {
    max_heapify(arr, end - start, i);
  }
}

void max_heapify(int *arr, int heapSize, int index)
{
  int left = 2 * index;
  int right = left + 1;

  int largest = index;

  if (left < heapSize && arr[left] > arr[largest])
  {
    largest = left;
  }

  if (right < heapSize && arr[right] > arr[largest])
  {
    largest = right;
  }

  if (largest != index)
  {
    swap(&arr[largest], &arr[index]);
    max_heapify(arr, heapSize, largest);
  }
}

void heap_sort(int *arr, int start, int end)
{
  build_max_heap(arr, start, end);

  for (int i = end - start - 1; i > -1; i--)
  {
    swap(&arr[0], &arr[1]);

    max_heapify(arr, i, 0);
  }
}

int partition_rand(int *arr, int start, int end)
{
  int pIndex = rand() % (end - start + 1) + start;
  swap(&arr[pIndex], &arr[end]);

  return partition(arr, start, end);
}

int partition(int *arr, int start, int end)
{
  int pivot = arr[end];
  int pIndex = start;

  for (int i = start; i < end; i++)
  {
    if (arr[i] <= pivot)
    {
      swap(&arr[pIndex], &arr[i]);
      pIndex++;
    }
  }

  swap(&arr[pIndex], &arr[end]);

  return pIndex;
}

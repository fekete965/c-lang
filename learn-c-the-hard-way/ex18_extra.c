#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef int (*compare_cb)(int a, int b);
typedef int *(*sorting_alg)(int *numbers, int count, compare_cb cmp);

void die(char *message);
int *bubble_sort(int *numbers, int count, compare_cb cmp);
int *quick_sort(int *numbers, int count, compare_cb cmp);
int sorted_order(int a, int b);
int reverse_order(int a, int b);
int strange_order(int a, int b);
void test_sorting(int *numbers, int count, sorting_alg sort, compare_cb cmp);
void swap(int *a, int *b);
int partition(int *numbers, int start, int end, compare_cb cmp);
void execute_quick_sort(int *target, int start, int end, compare_cb cmp);

int main(int argc, char *argv[])
{
  if (argc < 2)
    die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;
  int *numbers = malloc(count * sizeof(int));

  if (!numbers)
    die("Memory error.");

  for (i = 0; i < count; i++)
  {
    numbers[i] = atoi(inputs[i]);
  }

  printf("Bubble sort\n");
  test_sorting(numbers, count, bubble_sort, sorted_order);
  test_sorting(numbers, count, bubble_sort, reverse_order);
  test_sorting(numbers, count, bubble_sort, strange_order);
  printf("\nQuick sort\n");
  test_sorting(numbers, count, quick_sort, sorted_order);
  test_sorting(numbers, count, quick_sort, reverse_order);
  test_sorting(numbers, count, quick_sort, strange_order);

  free(numbers);

  return 0;
}

void die(char *message)
{
  if (errno)
  {
    perror(message);
  }
  else
  {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int j = 0;
  int i = 0;
  int *target = malloc(count * sizeof(int));

  if (!target)
    die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  for (i = 0; i < count; i++)
  {
    for (j = 0; j < count - 1; j++)
    {
      if (cmp(target[j], target[j + 1]) > 0)
      {
        swap(&target[j + 1], &target[j]);
      }
    }
  }

  return target;
}

int *quick_sort(int *numbers, int count, compare_cb cmp)
{
  int *target = malloc(count * sizeof(int));

  if (!target)
    die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  execute_quick_sort(target, 0, count - 1, cmp);

  return target;
}

int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if (a == 0 || b == 0)
  {
    return 0;
  }
  else
  {
    return a % b;
  }
}

/**
 * Used to test what we are sorting things correctly
 * by doing the sort and printing it out
 */
void test_sorting(int *numbers, int count, sorting_alg sort, compare_cb cmp)
{
  int i = 0;
  int *sorted = sort(numbers, count, cmp);

  if (!sorted)
    die("Failed to sort as requested.");

  for (i = 0; i < count; i++)
  {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);

  unsigned char *data = (unsigned char *)cmp;
  for (i = 0; i < 25; i++)
  {
    printf("%02x:", data[i]);
  }
  printf("\n");
}

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int *numbers, int start, int end, compare_cb cmp)
{
  int pivot = numbers[end];
  int i = start - 1;

  for (int j = start; j < end; j++)
  {
    if (cmp(numbers[j], pivot) > 0)
    {
      i++;
      swap(&numbers[i], &numbers[j]);
    }
  }

  i++;
  swap(&numbers[i], &numbers[end]);

  return i;
}

void execute_quick_sort(int *target, int start, int end, compare_cb cmp)
{
  if (end <= start)
  {
    return;
  }

  int pivot = partition(target, start, end, cmp);
  execute_quick_sort(target, start, pivot - 1, cmp);
  execute_quick_sort(target, pivot + 1, end, cmp);
}

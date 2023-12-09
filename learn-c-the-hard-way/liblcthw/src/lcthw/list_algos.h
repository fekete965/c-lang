#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include "list.h"
/*
List_compare is used to compare the list values during the sort

Input:
  void *first: the value we compare with the second one
  void *second: the value we compare with the first one
Output:
  The return value is an integer we use to decide the sorting order
  Return 0 if the values are equal
  Return 1 if the first value is greater than the second value
  Return -1 if the first value is less than the second value
*/
typedef int (*List_compare)(void *first, void *second);

/*
The function which performs a bubble sort on a list

Inputs:
  List *list: the list required to be sorted
  List_compare *compare: the comparison function used to determine the sorting
*/
int List_bubble_sort(List *list, List_compare compare);

/*
The Function which performs the merge sort on a list

Inputs:
  List *list: the list required to be sorted
  List_compare *compare: the comparison function used to determine the sorting
*/
List *List_merge_sort(List *list, List_compare compare);

#endif

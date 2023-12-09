#include <lcthw/list.h>
#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

int List_bubble_sort(List *list, List_compare compare)
{
  if (list->count < 2)
  {
    return 0;
  }
  int swapped = 0;

  int i = 0;
  int n = list->count;
  ListNode *current = list->first->next;
  ListNode *prev = current->prev;
  ListNode *next = current->next;

  do
  {
    swapped = 0;

    while (i < n)
    {
      if (compare(prev->value, current->value) > 0)
      {
        if (prev == list->first)
        {
          prev->next = current->next;
          prev->next->prev = prev;
          prev->prev = current;
          current->next = prev;
          current->prev = NULL;
          list->first = current;
        }
        else if (current == list->last)
        {
          current->prev = prev->prev;
          current->prev->next = current;
          current->next = prev;
          prev->prev = current;
          prev->next = NULL;
          list->last = prev;
        }
        else
        {
          current->prev = prev->prev;
          current->prev->next = current;
          prev->next = current->next;
          prev->next->prev = prev;
          current->next = prev;
          prev->prev = current;
        }

        swapped = 1;
      }

      current = current->next;
      prev = current->prev;
      next = current->next;

      i++;
    }

    current = list->first->next;
    prev = current->prev;
    next = current->next;
    n--;
    i = 0;
  } while (swapped == 1);

  return 0;
}

List *List_merge_sort(List *list, List_compare compare)
{
  return list;
}

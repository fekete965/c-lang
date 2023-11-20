#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
  List *list = calloc(1, sizeof(List));
  check_mem(list);

  return list;

error:
  return;
}

void List_destroy(List *list)
{
  CHECK_LIST(list);

  LIST_FOREACH(list, first, next, cur)
  {
    if (cur->prev)
    {
      free(cur->prev);
    }
  }

  free(list->last);
  free(list);

error:
  return;
}

void List_clear(List *list)
{
  CHECK_LIST(list);

  LIST_FOREACH(list, first, next, cur)
  {
    free(cur->value);
  }

error:
  return;
}

void List_clear_destroy(List *list)
{
  CHECK_LIST(list);

  LIST_FOREACH(list, first, next, cur)
  {
    free(cur->value);

    if (cur->prev)
    {
      free(cur->prev);
    }
  }

  free(list->last);
  free(list);

error:
  return;
}

void List_push(List *list, void *value)
{
  CHECK_LIST(list);

  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->last == NULL)
  {
    list->first = node;
    list->last = node;
  }
  else
  {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }

  list->count++;

error:
  return;
}

void *List_pop(List *list)
{
  CHECK_LIST(list);

  ListNode *node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;

error:
  return NULL;
}

void List_unshift(List *list, void *value)
{
  CHECK_LIST(list);

  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->first == NULL)
  {
    list->first = node;
    list->last = node;
  }
  else
  {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }

  list->count++;

error:
  return;
}

void *List_shift(List *list)
{
  CHECK_LIST(list);

  ListNode *node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;

error:
  return NULL;
}

void *List_remove(List *list, ListNode *node)
{
  CHECK_LIST(list);

  void *result = NULL;

  check(list->first && list->last, "List is empty.");
  check(node, "Node can't be NULL");

  if (node == list->first && node == list->last)
  {
    list->first = NULL;
    list->last = NULL;
  }
  else if (node == list->first)
  {
    list->first = node->next;
    check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
    list->first->prev = NULL;
  }
  else if (node == list->last)
  {
    list->last = node->prev;
    check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
    list->last->next = NULL;
  }
  else
  {
    ListNode *after = node->next;
    ListNode *before = node->prev;
    after->prev = before;
    before->next = after;
  }

  list->count--;
  result = node->value;
  free(node);

error:
  return result;
}

List *List_split(List *list, int at)
{
  CHECK_LIST(list);

  check(list->count >= at, "List does not have enough elements");

  List *newList = List_create();

  // If the index where we should split is equals to the count
  // we simply return an empty list
  if (list->count == at)
  {
    return newList;
  }

  // If the index where we should split at is 0
  // we swap the original and new array references
  if (at == 0)
  {
    List *tmp = list;
    list = newList;
    newList = tmp;
  }

  // Otherwise we iterate through the list and split where needed
  int i = 0;

  LIST_FOREACH(list, first, next, cur)
  {
    if (i == at)
    {
      newList->first = cur;
      newList->last = list->last;
      list->last = cur->prev;
      list->last->next = NULL;
      cur->prev = NULL;

      newList->count = list->count - at;
      list->count = at;
      break;
    }

    i++;
  }

  return newList;

error:
  return;
}

List *List_join(List *listA, List *listB, size_t size)
{
  CHECK_LIST(listA);
  CHECK_LIST(listB);

  List *newList = List_create();

  LIST_FOREACH(listA, first, next, cur)
  {
    void *value = NULL;
    memcpy(value, cur->value, size);
    List_push(newList, value);
  }

  LIST_FOREACH(listB, first, next, cur)
  {
    void *value = NULL;
    memcpy(value, cur->value, size);
    List_push(newList, value);
  }

  return newList;

error:
  return;
}

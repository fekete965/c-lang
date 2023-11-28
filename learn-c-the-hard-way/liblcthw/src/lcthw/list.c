#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
  List *list = calloc(1, sizeof(List));
  check_mem(list);

  return list;

error:
  return list;
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
    if (cur->value != NULL)
    {
      free(cur->value);
    }
  }

error:
  return;
}

void List_clear_destroy(List *list)
{
  CHECK_LIST(list);

  LIST_FOREACH(list, first, next, cur)
  {
    if (cur->value != NULL)
    {
      free(cur->value);
    }

    if (cur->prev != NULL)
    {
      free(cur->prev);
    }
  }

  if (list->last != NULL)
  {
    free(list->last);
  }
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
  void *result = NULL;

  CHECK_LIST(list);

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
  List *newList = NULL;

  CHECK_LIST(list);

  newList = List_create();

  check(list->count >= at, "List does not have enough elements");

  // If the index where we should split is equals to the count
  // we simply return an empty list
  if (list->count == at)
  {
    return newList;
  }

  // If the index where we should move every node
  // from the original list into the new list
  if (at == 0)
  {
    newList->count = list->count;
    newList->first = list->first;
    newList->last = list->last;

    list->count = 0;
    list->first = NULL;
    list->last = NULL;

    return newList;
  }

  // Otherwise we iterate through the list and split where needed
  int i = 0;

  LIST_FOREACH(list, first, next, cur)
  {
    if (i == at)
    {
      newList->first = cur;
      newList->last = list->last;
      list->last = newList->first->prev;
      list->last->next = NULL;
      newList->first->prev = NULL;

      newList->count = list->count - at;
      list->count = at;
      break;
    }

    i++;
  };

  return newList;

error:
  return newList;
}

List *List_join(List *listA, List *listB)
{
  List *newList = NULL;

  CHECK_LIST(listA);
  CHECK_LIST(listB);

  newList = List_create();

  {
    LIST_FOREACH(listA, first, next, cur)
    {
      List_push(newList, cur->value);
    }
  }

  {
    LIST_FOREACH(listB, first, next, cur)
    {
      List_push(newList, cur->value);
    }
  }

  free(listA);
  free(listB);

  return newList;

error:
  return newList;
}

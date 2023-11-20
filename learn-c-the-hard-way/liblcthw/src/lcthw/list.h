#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>
#include "dbg.h"

struct ListNode;

/*
This is the ListNode typedef used within a List.

Properties:
  - ListNode *next: the connected node after the current one
  - ListNode *prev: the connected node before the current one
  - void *value: the property which can hold any value
*/
typedef struct ListNode
{
  struct ListNode *next;
  struct ListNode *prev;
  void *value;
} ListNode;

/*
This is the List typedef which is the root of the node list

Properties:
  - int count: this value indicates the currently held node count
  - ListNode *first: this value holds the reference of the first ListNode within the List
  - ListNode *last: this value holds the reference of the last ListNode within the List
*/
typedef struct List
{
  int count;
  ListNode *first;
  ListNode *last;
} List;

/*
This function creates a new List on the heap.

Input:
  There are not input values
Output:
  The return value is a List*
*/
List *List_create();

/*
This function frees each node inside the a list,
then the list itself.

Input:
  List* list: the list that needs to be destroyed
Output:
  There is no return value
*/
void List_destroy(List *list);

/*
This function frees each node value inside a list.

Input:
  List* list: the list that needs to be cleared
Output:
  There is no return value
*/
void List_clear(List *list);

/*
This function frees each node value inside a List,
destroys each node then the list itself.

Input:
  List* list: the list that needs to be cleared and destroyed
Output:
  There is no return value
*/
void List_clear_destroy(List *list);

/*
This macro returns the count of a list

Input:
  L: this is the list itself
*/
#define List_count(L) ((L)->count)

/*
This macro returns the value of the first node
of a list if it is defined, otherwise NULL

Input:
  L: this is the list itself
*/
#define List_first(L) ((L)->first != NULL ? (L)->first->value : NULL)

/*
This macro returns the value of the last node
of a list if it is defined, otherwise NULL

Input:
  L: this is the list itself
*/
#define List_last(L) ((L)->last != NULL ? (L)->last->value : NULL)

/*
This function adds a new node at the end of a list.

Input:
  List *list: the target list which needs the operation to be performed on
  void *value: the value of the new node in the list
Output:
  There is no return value
*/
void List_push(List *list, void *value);

/*
This function pops/removes a node from the end of a list.

Input:
  List *list: the target list which needs the operation to be performed on
Output:
  The value of the removed node
*/
void *List_pop(List *list);

/*
This function adds a new node at the beginning of a list.

Input:
  List *list: the target list which needs the operation to be performed on
  void *value: the value of the new node in the list
Output:
  There is no return value
*/
void List_unshift(List *list, void *value);

/*
This function shifts/removes a node from the beginning of a list.

Input:
  List *list: the target list which needs the operation to be performed on
Output:
  The value of the removed node
*/
void *List_shift(List *list);

/*
This function removes a node from a list.

Input:
  List *list: the target list which needs the operation to be performed on
  ListNode *node: the reference of a node
Output:
  The value of the removed node
*/
void *List_remove(List *list, ListNode *node);

/*
This macro helps you to create the base of an iteration correctly

Inputs:
  L: this is the target list
  S: this is the first node in the list
  M: this is the next node in the list
  V: this is the current node in the list

Usage:
LIST_FOREACH(list, first, next, cur) { ... }
*/
#define LIST_FOREACH(L, S, M, V) \
  ListNode *_node = NULL;        \
  ListNode *V = NULL;            \
  for (V = _node = L->S; _node != NULL; V = _node = _node->M)

/*
This macro validates the list using the the following criteria:
  - The list is not NULL
  - The list count value is >= 0
  - If the list counter is > 0
    - The first node is not NULL

Input:
  L: this is the list itself
*/
#define CHECK_LIST(L)                            \
  {                                              \
    check((L) != NULL, "Invalid list");          \
    check((L)->count >= 0, "Invalid list");      \
    if ((L)->count > 0)                          \
    {                                            \
      check((L)->first != NULL, "Invalid list"); \
    }                                            \
  }

/*
This function splits a list at an index

Input:
  - List *list: this is the list that will be splitted
  - int at: this is the index where we split the list
Output:
  The return value is a new list containing the splitted elements
*/
List *List_split(List *list, int at);

/*
This function joins 2 lists together

Input:
  - List *rootList: this is the root list that serves as the base list
  - List *list: this is the last that will be added to the rootList
  - size_t size: this is the size of the data stored within the list nodes
Output:
  The return value is a new List* containing the elements from listA and listB
*/
List *List_join(List *listA, List *listB, size_t size);

#endif

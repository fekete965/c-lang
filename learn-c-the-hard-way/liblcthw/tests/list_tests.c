#include "minuit.h"
#include <lcthw/list.h>
#include <assert.h>

char *get_test_data(char *data, int size)
{
  char *str = calloc(1, sizeof(char) * size);
  mu_assert(str != NULL, "str should not be NULL");
  snprintf(str, size, "%s", data);

  return str;
}

char *test_create()
{
  List *list = List_create();
  mu_assert(list != NULL, "Failed to create list.");

  free(list);

  return NULL;
}

char *test_push_pop()
{
  List *list = List_create();

  char *str1 = get_test_data("test data 1", 12);
  char *str2 = get_test_data("test data 2", 12);
  char *str3 = get_test_data("test data 3", 12);

  List_push(list, str1);
  mu_assert(List_last(list) == str1, "Wrong last value.");
  mu_assert(List_first(list) == str1, "Wrong first value.");

  List_push(list, str2);
  mu_assert(List_last(list) == str2, "Wrong last value.");
  mu_assert(List_first(list) == str1, "Wrong first value.");

  List_push(list, str3);
  mu_assert(List_last(list) == str3, "Wring last value.");
  mu_assert(List_first(list) == str1, "Wrong first value.");
  mu_assert(List_count(list) == 3, "Wrong count on push.");

  char *val = List_pop(list);
  mu_assert(val == str3, "Wrong value on pop. (1)");

  val = List_pop(list);
  mu_assert(val == str2, "Wrong value on pop. (2)");

  val = List_pop(list);
  mu_assert(val == str1, "Wrong value on pop. (3)");
  mu_assert(List_count(list) == 0, "Wrong count on pop. (3)");

  free(list);

  return NULL;
}

char *test_destroy()
{
  List *list = List_create();

  char *str1 = get_test_data("test data 1", 12);
  char *str2 = get_test_data("test data 2", 12);

  List_push(list, str1);
  List_push(list, str2);

  List_clear_destroy(list);

  return NULL;
}

char *test_unshift_shift()
{
  List *list = List_create();

  char *str1 = get_test_data("test data 1", 12);
  char *str2 = get_test_data("test data 2", 12);
  char *str3 = get_test_data("test data 3", 12);

  List_unshift(list, str1);
  mu_assert(List_first(list) == str1, "Wrong first value.");
  mu_assert(List_last(list) == str1, "Wrong last value.");

  List_unshift(list, str2);
  mu_assert(List_first(list) == str2, "Wrong first value.");
  mu_assert(List_last(list) == str1, "Wrong last value.");

  List_unshift(list, str3);
  mu_assert(List_first(list) == str3, "Wrong first value.");
  mu_assert(List_last(list) == str1, "Wrong last value.");

  char *val = List_shift(list);
  mu_assert(val == str3, "Wrong value on shift.");

  val = List_shift(list);
  mu_assert(val == str2, "Wrong value on shift.");
  mu_assert(List_count(list) == 1, "Wrong count after shift.");

  List_clear_destroy(list);

  return NULL;
}

char *test_split()
{
  List *list = List_create();

  char *str1 = get_test_data("test data 1", 12);
  char *str2 = get_test_data("test data 2", 12);
  char *str3 = get_test_data("test data 3", 12);
  char *str4 = get_test_data("test data 4", 12);

  // Setup our list for the split
  List_push(list, str1);
  List_push(list, str2);
  List_push(list, str3);
  List_push(list, str4);

  // We split the list at the last element
  List *secondList = List_split(list, List_count(list));

  // That should produce us a new empty list
  mu_assert(List_count(list) == 4, "The initial list count should not change.");
  mu_assert(list->first != NULL, "The initial list first element should not be empty.");
  mu_assert(list->last != NULL, "The initial list last element should not be empty.");

  mu_assert(List_count(secondList) == 0, "The second list be empty.");
  mu_assert(secondList->first == NULL, "The second list first element should be empty.");
  mu_assert(secondList->last == NULL, "The second list last element should be empty.");

  // Clean up
  List_clear_destroy(secondList);

  // Split the list at the first element
  secondList = List_split(list, 0);
  mu_assert(List_count(list) == 0, "The initial list should be empty.");
  mu_assert(list->first == NULL, "The initial list first element should be empty.");
  mu_assert(list->last == NULL, "The initial list last element should be empty.");

  mu_assert(List_count(secondList) == 4, "The second list should have all the members as the initial list.");
  mu_assert(secondList->first != NULL, "The second list first element should not be empty.");
  mu_assert(secondList->first->value == str1, "The second list first element has an unexpected value.");
  mu_assert(secondList->last != NULL, "The second list last element should not be empty.");
  mu_assert(secondList->last->value == str4, "The second list last element has an unexpected value.");

  // Split the second list at the second element
  list = List_split(secondList, 2);

  mu_assert(List_count(list) == 2, "The initial list should count should be 2.");
  mu_assert(list->first != NULL, "The initial list first element should not be empty.");
  mu_assert(list->first->value == str3, "The initial list first element has an unexpected value.");
  mu_assert(list->last != NULL, "The initial list last element should not be empty.");
  mu_assert(list->last->value == str4, "The initial list first element has an unexpected value.");

  mu_assert(List_count(secondList) == 2, "The second list count should be 2.");
  mu_assert(secondList->first != NULL, "The second list first element should not be empty.");
  mu_assert(secondList->first->value == str1, "The second list first element has an unexpected value.");
  mu_assert(secondList->last != NULL, "The second list last element should not be empty.");
  mu_assert(secondList->last->value == str2, "The second list first element has an unexpected value.");

  List_clear_destroy(list);

  return NULL;
}

char *test_join()
{
  List *list = List_create();

  char *str1 = get_test_data("test data 1", 12);
  char *str2 = get_test_data("test data 2", 12);
  char *str3 = get_test_data("test data 3", 12);
  char *str4 = get_test_data("test data 4", 12);

  List_push(list, str1);
  List_push(list, str2);

  mu_assert(List_count(list) == 2, "We should have a list with 2 nodes.");

  List *list2 = List_create();

  List_push(list2, str3);
  List_push(list2, str4);

  mu_assert(List_count(list2) == 2, "We should have another list with 2 nodes.");

  List *joinedList = List_join(list, list2);

  mu_assert(List_count(joinedList) == 4, "The new list should contain 4 values.");
  mu_assert(joinedList->first->value == str1, "The new list first value has an unexpected value.");
  mu_assert(joinedList->first->next->value == str2, "The new list seconds value has an unexpected value.");
  mu_assert(joinedList->last->prev->value == str3, "The new list third value has an unexpected value.");
  mu_assert(joinedList->last->value == str4, "The new list fourth value has an unexpected value.");

  List_clear_destroy(joinedList);

  return NULL;
}

char *test_remove()
{
  List *list = List_create();

  char *str1 = get_test_data("test data 1", 12);
  char *str2 = get_test_data("test data 2", 12);
  char *str3 = get_test_data("test data 3", 12);

  List_push(list, str1);
  List_push(list, str2);
  List_push(list, str3);

  char *val = List_remove(list, list->first->next);
  mu_assert(val == str2, "Wrong removed element.");
  mu_assert(List_count(list) == 2, "Wrong count after remove.");
  mu_assert(List_first(list) == str1, "Wrong first after remove.");
  mu_assert(List_last(list) == str3, "Wrong last after remove.");

  List_clear_destroy(list);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_push_pop);
  mu_run_test(test_destroy);
  mu_run_test(test_unshift_shift);
  mu_run_test(test_remove);
  mu_run_test(test_split);
  mu_run_test(test_join);

  return NULL;
}

RUN_TESTS(all_tests);

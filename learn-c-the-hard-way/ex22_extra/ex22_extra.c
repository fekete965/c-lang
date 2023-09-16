#include <stdio.h>
#include "ex22_extra.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age()
{
  return THE_AGE;
}

void set_age(int age)
{
  THE_AGE = age;
}

double update_ratio(double new_ratio)
{
  static double ratio = 1.0;

  double old_ratio = ratio;
  ratio = new_ratio;

  return old_ratio;
}

void print_size()
{
  log_info("I think size is %d", THE_SIZE);
}

// Extra credit below
void add_to_counter_mutation(int *counter, int value)
{
  (*counter) += value;
}

int add_to_counter_copy(int counter, int value)
{
  return counter + value;
}

void lets_cause_stack_overflow(int dummy_value)
{
  debug("Calling lets_cause_stack_overflow with: %d", dummy_value);
  lets_cause_stack_overflow(dummy_value + 10);
}

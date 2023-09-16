#ifndef _ex22_extra_h
#define _ex22_extra_h

// make THE_SIZE in ex22.c available to other .c files
extern int THE_SIZE;

// gets and sets an internal static variable in ex22.c
int get_age();

void set_age(int age);

// updates a static variable that's inside update_ratio
double update_ratio(double ratio);

void print_size();

// Extra credit below
void add_to_counter_mutation(int *counter, int value);

int add_to_counter_copy(int counter, int value);

void lets_cause_stack_overflow(int dummy_value);

#endif

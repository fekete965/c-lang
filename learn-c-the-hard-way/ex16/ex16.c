#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
  char *name;
  int age;
  int height;
  int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destroy(struct Person *who)
{
  assert(who != NULL);

  free(who->name);
  free(who);
}

void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %i\n", who->age);
  printf("\tHeight: %i\n", who->height);
  printf("\tWeight: %i\n", who->weight);
}

int main(int argc, char *argv[])
{
  // make two people structures
  struct Person *joe = Person_create("Joe Alex", 32, 64, 140);

  struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

  // print them out and where they are in memory
  printf("Joe is at memory location %p\n", joe);
  Person_print(joe);

  printf("Frank is at memory location %p\n", frank);
  Person_print(frank);

  // make everyone age 20 years and print them again
  joe->age = 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age = 20;
  frank->weight += 20;
  Person_print(frank);

  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}

/*
  Describe the each line of the program

1-4: Include the following libraries: stdio, assert, stdlib, string
  stdio gives us: "printf"
  assert gives us: "assert"
  stdlib gives us: "malloc", "free"
  string gives us: "strdup"

6-12: We declare a struct named Person with the following properties:
    name, age, height, weight

14: We create a function called "Person_create" which returns a pointer that has a struct Person type.
  The function takes in the struct Person properties as arguments.

16: We allocate enough memory for a single struct Person and save its pointer into a variable called "who"

17: We call "assert" (macro) to check if the "who" variable is NULL pointer.
  (assert terminates the program if the assertion is false otherwise does nothing)

19-22: We assign the "who" variable properties using the function's arguments

24: We return the "who" variable (the pointer to the struct Person we've just crated)

27: We create a void function called "Person_destroy" which only argument is a struc Person pointer

29: We use "assert" (macro) to check if the passed in pointer is not NULL

31: We free the memory allocated for the struct Person name
32: we free the memory allocated for the struct Person

35: We declare a void function called "Person_print" which only argument is a struct Person pointer

43-40: We print out each properties of the passed in struct Person pointer

43: We declare the "main" function

46: We create a person called "joe" using "Person_create"
48: We create a person called "frank" using "Person_create"

51: We print a "joe" struct's memory location to the console
52: We print out the properties of "joe" using "Person_print"

54: We print a "frank" struct's memory location to the console
55: We print out the properties of "frank" using "Person_print"

58: We set "joe" struct's age property to 20
59: We decrement "joe" struct's height property by 2
60: We increment "joe" struct's weight property by 40
61: We print out the updated properties of "joe" using "Person_print"

63: We set "frank" struct's age property to 20
64: We increment "frank" struct's weight property by 20
65: We print out the updated properties of "frank" using "Person_print"

68: We free up the allocated memory of "joe" by calling "Person_destroy"
69: We free up the allocated memory of "frank" by calling "Person_destroy"

71: We terminate the program
*/

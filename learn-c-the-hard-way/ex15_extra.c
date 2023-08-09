#include <stdio.h>
#include <stdlib.h>

void firstCustomPrint(char **names, int *ages, int size);
void secondCustomPrint(char **names, int *ages, int size);
void thirdCustomPrint(char **names, int *ages, int size);
void printDataAndMemoryAddress(char **names, int *ages, int size);

int main(int argc, char *argv[])
{
  int count = 5;

  int *ages = malloc(sizeof(int) * count);
  ages[0] = 23;
  ages[1] = 43;
  ages[2] = 12;
  ages[3] = 89;
  ages[4] = 2;

  char **names = malloc(sizeof(char) * count);
  names[0] = "Alan";
  names[1] = "Frank";
  names[2] = "Mary";
  names[3] = "John";
  names[4] = "Lisa";

  // first way using indexing
  firstCustomPrint(names, ages, count);

  printf("---\n");
  // set up the pointers to the start of the arrays
  char *cur_name[] = {names[0], names[1], names[2], names[3], names[4]};
  int cur_age[] = {ages[0], ages[1], ages[2], ages[3], ages[4]};

  // second way using pointers
  secondCustomPrint(cur_name, cur_age, count);

  printf("---\n");

  // third way, pointers are just arrays
  thirdCustomPrint(cur_name, cur_age, count);

  printf("---\n");

  // print data and its memory address
  printDataAndMemoryAddress(cur_name, cur_age, count);

  return 0;
}

void firstCustomPrint(char **names, int *ages, int count)
{
  int i = 0;

  printf("       For loop\n");
  for (i = 0; i < count; i++)
  {
    printf("%s has %d years alive.\n", names[i], ages[i]);
  }

  i = 0;
  printf("       While loop\n");
  while (i < count)
  {
    printf("%s has %d years alive.\n", names[i], ages[i]);
    i++;
  }
}

void secondCustomPrint(char **names, int *ages, int size)
{
  int i = 0;

  printf("     For loop\n");
  for (i = 0; i < size; i++)
  {
    printf("%s is %d years old.\n", *(names + i), *(ages + i));
  }

  i = 0;
  printf("     While loop\n");
  while (i < size)
  {
    printf("%s is %d years old.\n", *(names + i), *(ages + i));
    i++;
  }
}

void thirdCustomPrint(char **names, int *ages, int size)
{
  int i = 0;

  printf("        For loop\n");
  for (i = 0; i < size; i++)
  {
    printf("%s is %d years old again.\n", names[i], ages[i]);
  }

  i = 0;
  printf("     While loop\n");
  while (i < size)
  {
    printf("%s is %d years old again.\n", names[i], ages[i]);
    i++;
  }
}

void printDataAndMemoryAddress(char **names, int *ages, int size)
{
  int i = 0;

  printf("     For loop\n");
  for (i = 0; i < size; i++)
  {
    printf("The value and address of name[%i]: %s - %p\n", i, names[i], &names[i]);
    printf("The value and address of ages[%i]: %i - %p\n", i, ages[i], &ages[i]);
  }

  i = 0;
  printf("     While loop\n");
  while (i < size)
  {
    printf("The value and address of name[%i]: %s - %p\n", i, names[i], &names[i]);
    printf("The value and address of ages[%i]: %i - %p\n", i, ages[i], &ages[i]);
    i++;
  }
}

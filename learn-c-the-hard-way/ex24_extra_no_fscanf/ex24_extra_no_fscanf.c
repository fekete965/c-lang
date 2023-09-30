#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor
{
  BLUE_EYES,
  GREEN_EYES,
  BROWN_EYES,
  BLACK_EYES,
  OTHER_EYES,
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"};

typedef struct Person
{
  int age;
  char first_name[MAX_DATA];
  char last_name[MAX_DATA];
  EyeColor eyes;
  float income;
} Person;

int main(int argc, char *argv[])
{
  Person you = {.age = 0};
  int i = 0;
  char *in = NULL;
  char *tmp_input = malloc(sizeof(char) * MAX_DATA);

  printf("What's your First Name? ");
  in = fgets(you.first_name, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read first name.");

  printf("What's your Last Name? ");
  in = fgets(you.last_name, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read last name.");

  printf("How old are you? ");
  in = fgets(tmp_input, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read age.");

  you.age = atoi(tmp_input);
  check(you.age > 0, "Age has to be greater than 0.");

  printf("What color are your eyes:\n");
  for (i = 0; i <= OTHER_EYES; i++)
  {
    printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
  }
  printf("> ");

  in = fgets(tmp_input, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read eye color.");
  for (i = 0; i < MAX_DATA - 1; i++)
  {
    int is_new_line = tmp_input[i] == '\n';
    int is_zero_char = tmp_input[i] == '\0';
    check(isnumber(tmp_input[i]) || is_new_line || is_zero_char, "You have to enter a number.");
  }

  you.eyes = atoi(tmp_input) - 1;
  check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

  printf("How much do you make an hour? ");
  in = fgets(tmp_input, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read income.");

  you.income = atof(tmp_input);
  check(you.income > 0, "Enter a floating point number.");

  printf("----- RESULTS -----\n");

  printf("First Name: %s", you.first_name);
  printf("Last Name: %s", you.last_name);
  printf("Age: %d\n", you.age);
  printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
  printf("Income: %f\n", you.income);

  return 0;

error:
  return -1;
}

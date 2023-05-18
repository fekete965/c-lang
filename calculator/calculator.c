#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValidOperator(char *operator);
char getOperator(char *operator);
void getNumber(char *text, double *num);
void calculate(double a, char operator, double b, double *result);
void showResult(double result);

const char VALID_OPERATORS[4] = {'+', '-', '*', '/'};
const int SIZE_OF_VO = sizeof(VALID_OPERATORS) / sizeof(VALID_OPERATORS[0]);

int main()
{

  char operator;
  double a;
  double b;
  double result;

  getOperator(&operator);
  getNumber("\nEnter number 1: ", &a);
  do
  {
    if (b == 0)
    {
      printf("\n0 division is invalid!\n");
    }
    getNumber("\nEnter number 2: ", &b);

  } while (operator== '/' && b == 0);

  calculate(a, operator, b, &result);
  showResult(result);

  return 0;
}

int isValidOperator(char *operator)
{
  for (int i = 0; i < SIZE_OF_VO; i++)
  {
    char vo = VALID_OPERATORS[i];
    if (vo == operator[0])
    {
      return 1;
    }
  }

  return 0;
}

char getOperator(char *operator)
{
  printf("\nEnter an operator: (+ - * /): ");
  scanf("%c", operator);
  operator[strlen(operator)] = '\0';

  if (!isValidOperator(operator))
  {
    printf("\n%c operator is not valid!\n", operator[0]);
    fflush(stdin);
    return getOperator(operator);
  }

  return operator[0];
}

void getNumber(char *text, double *num)
{
  printf("%s", text);
  scanf("%lf", num);
}

void calculate(double a, char operator, double b, double *result)
{
  switch (operator)
  {
  case '+':
    (*result) = a + b;
    break;
  case '-':
    (*result) = a - b;
    break;
  case '*':
    (*result) = a * b;
    break;
  case '/':
    (*result) = a / b;
    break;
  default:
    printf("\n%c operator hadn't been implemented yet", operator);
    exit(1);
  }
}

void showResult(double result)
{
  printf("\nResult: %.2lf\n", result);
}

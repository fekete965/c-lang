#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MAX_STACK 10
#define MIN_NUM 0
#define MAX_NUM 100
#define HELP_MESSAGE "Pick a command: 1 = push, 2 = pop, 3 = display, 4 = display top, 5 = quit\n"

typedef struct MyStack
{
  int values[MAX_STACK];
  int top;
} MyStack;

int die(const char *message);
int push(MyStack *stack, int newValue);
int pop(MyStack *stack);
int is_empty(MyStack *stack);
int is_full(MyStack *stack);
int top(MyStack *stack);
int generate_random_number(int min, int max);
void Stack_display(MyStack *stack);
void Stack_display_top(MyStack *stack);

int main(int argc, char *argv[])
{
  srand(time(NULL));

  MyStack stack = {.top = -1};
  int cmd = 0;

  printf("Exercise 17 - Extra Credit Stack\n");
  printf(HELP_MESSAGE);
  while (1)
  {
    scanf("%d", &cmd);

    switch (cmd)
    {
    case 1:
    {
      int rnd_number = generate_random_number(MIN_NUM, MAX_NUM);
      printf("Pushing %d to the stack\n", rnd_number);
      push(&stack, rnd_number);
      break;
    }

    case 2:
    {
      int poppedValue = pop(&stack);
      printf("Popped %d from the stack\n", poppedValue);
      break;
    }

    case 3:
    {
      Stack_display(&stack);
      break;
    }

    case 4:
    {
      Stack_display_top(&stack);
      break;
    }

    case 5:
    {
      printf("Closing the application\n");
      exit(0);
    }

    default:
    {
      printf("Invalid command\n");
      printf(HELP_MESSAGE);
    }
    }
  }

  return 0;
}

int push(MyStack *stack, int newValue)
{
  if (is_full(stack))
    die("Stack is full");

  stack->values[++stack->top] = newValue;

  return stack->top;
}

int pop(MyStack *stack)
{
  if (is_empty(stack))
    die("Stack is empty");

  int poppedVal = stack->values[stack->top--];

  return poppedVal;
}

int is_empty(MyStack *stack)
{
  return stack->top == -1;
}

int is_full(MyStack *stack)
{
  return stack->top >= MAX_STACK - 1;
}

void Stack_display_top(MyStack *stack)
{
  if (is_empty(stack))
    die("Stack is empty");

  printf("Top value: %d\n", stack->values[stack->top]);
}

void Stack_display(MyStack *stack)
{
  printf("Top: %d\n", stack->top);

  printf("Values:\n");
  int i = 0;
  for (i = 0; i < stack->top + 1; i++)
  {
    printf(" %d", stack->values[i]);
  }
  printf("\n");
}

int generate_random_number(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

int die(const char *message)
{
  if (errno)
  {
    perror(message);
  }
  else
  {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  if (argc == 2)
  {
    printf("You only have on argument. You suck.\n");
  }
  else if (argc > 2 && argc < 5)
  {
    printf("Here's your arguments:\n");

    for (i = 0; i < argc; i++)
    {
      printf("%s ", argv[i]);
    }
    printf("\n");
  }
  else
  {
    printf("You have too many arguments. You suck.\n");
  }

  return 0;
}

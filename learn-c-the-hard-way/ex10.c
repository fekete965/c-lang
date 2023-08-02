#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("ERROR: You need one argument\n");
    // this is how you abort a program
    return 1;
  }

  int i = 0;
  for (i = 0; argv[1][i] != '\0'; i++)
  {
    char letter = argv[1][i];

    switch (letter)
    {
    case 'a':
    case 'A':
      printf("%d: 'A'\n", letter);
      break;

    case 'e':
    case 'E':
      printf("%d: 'E'\n", letter);
      break;

    case 'i':
    case 'I':
      printf("%d: 'I'\n", letter);
      break;

    case 'o':
    case 'O':
      printf("%d: 'O'\n", letter);
      break;

    case 'u':
    case 'U':
      printf("%d: 'U'\n", letter);
      break;

    case 'y':
    case 'Y':
      if (i > 2)
      {
        // it's only sometimes Y
        printf("%d: 'Y'\n", letter);
      }
      break;

    default:
      printf("%d: %c is not a vowel\n", i, letter);
    }
  }

  return 0;
}

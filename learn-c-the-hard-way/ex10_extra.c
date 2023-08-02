#include <stdio.h>

int toLowerCase(int letter);

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("ERROR: You need one argument\n");
    // this is how you abort a program
    return 1;
  }

  char letter = '\0';

  for (int i = 1; i < argc; i++)
  {
    for (int j = 0, letter = argv[i][j]; letter != '\0'; j++, letter = argv[i][j])
    {
      letter = (char)toLowerCase(letter);

      switch (letter)
      {
      case 'a':
        printf("%d: 'A'\n", letter);
        break;

      case 'e':
        printf("%d: 'E'\n", letter);
        break;

      case 'i':
        printf("%d: 'I'\n", letter);
        break;

      case 'o':
        printf("%d: 'O'\n", letter);
        break;

      case 'u':
        printf("%d: 'U'\n", letter);
        break;

      case 'y':
        if (j > 2)
        {
          // it's only sometimes Y
          printf("%d: 'Y'\n", letter);
        }
        break;

      default:
        printf("%d: %c is not a vowel\n", j, letter);
      }
    }

    printf("\n");
  }

  return 0;
}

int toLowerCase(int letter)
{
  if (letter >= 65 && letter <= 90)
  {
    return letter + 32;
  }

  return letter;
}

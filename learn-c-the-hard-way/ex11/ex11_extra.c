#include <stdio.h>

int power(int n, int p);

int main(int argc, char *argv[])
{
  int numbers[4] = {0};
  int name[4] = {'a'};

  // first, print them out raw
  printf("numbers: %d %d %d %d\n",
         numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
         name[0], name[1], name[2], name[3]);

  printf("name: %s\n", name);

  // set up the numbers
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  // set up the name
  name[0] = 5;
  name[1] = 6;
  name[2] = 4;
  name[3] = 1;

  // extra credit part - start
  int nameAsInt = 0;
  int length = sizeof(name) / sizeof(name[0]);

  for (int i = 1; i <= length; i++)
  {
    nameAsInt += name[i - 1] * power(10, length - i);
  }

  printf("Name as Int: %d\n", nameAsInt);
  // extra credit part - end

  // then print them out initialized
  printf("numbers: %d %d %d %d\n",
         numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
         name[0], name[1], name[2], name[3]);

  // print the name like a string
  printf("name: %s\n", name);

  // another way to use name
  char *another = "Zed";

  printf("another: %s\n", another);

  printf("another each: %c %c %c %c\n",
         another[0], another[1], another[2], another[3]);

  return 0;
}

int power(int n, int p)
{
  if (p == 0)
  {
    return 1;
  }

  int v = n;

  while (p > 1)
  {
    v *= n;
    p--;
  }

  return v;
}

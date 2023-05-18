#include <stdio.h>
#include <math.h>

int main()
{
  double a;
  double b;
  double c;

  printf("\nEnter side A: ");
  scanf("%lf", &a);
  printf("\nEnter side B: ");
  scanf("%lf", &b);

  c = sqrt(a * a + b * b);
  printf("Side C: %lf\n", c);

  return 0;
}

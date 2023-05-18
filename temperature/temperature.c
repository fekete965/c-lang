#include <stdio.h>
#include <ctype.h>

float toCelsius(float temp);
float toFahrenheit(float temp);

int main()
{

  char unit;
  float temp;

  printf("\nIs the temperature in (F) or (C): ");
  scanf("%c", &unit);

  unit = toupper(unit);

  if (unit == 'C')
  {
    printf("\nEnter the temp in Celsius: ");
    scanf("%f", &temp);
    temp = toFahrenheit(temp);
    printf("\nThe temp in Fahrenheit is: %.1f\n", temp);
  }
  else if (unit == 'F')
  {
    printf("\nEnter the temp in Fahrenheit: ");
    scanf("%f", &temp);
    temp = toCelsius(temp);
    printf("\nThe temp in Celsius is: %.1f\n", temp);
  }
  else
  {
    printf("\n%c is not a valid unit of measurement\n", unit);
  }

  return 0;
}

float toFahrenheit(float temp)
{
  return (temp * 9 / 5) + 32;
}

float toCelsius(float temp)
{
  return (temp - 32) * 5 / 9;
}

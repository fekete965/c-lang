#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
  int i = 0;
  int char_int = -1;
  *out_string = calloc(1, max_buffer + 1);
  check_mem(*out_string);

  for (i = 0; i < max_buffer - 1; i++)
  {
    char_int = fgetc(stdin);
    if (char_int == '\n')
      break;

    (*out_string)[i] = char_int;
  }
  (*out_string)[i + 1] = '\0';

  // Initial approach
  // char *result = fgets(*out_string, max_buffer, stdin);
  // check(result != NULL, "Input error.");

  return 0;

error:
  if (*out_string)
    free(*out_string);
  *out_string = NULL;
  return -1;
}

int read_int(long *out_int)
{
  char *input = NULL;
  char *end = NULL;
  int rc = read_string(&input, MAX_DATA);
  check(rc == 0, "Failed to read number.");

  *out_int = strtol(input, &end, 10);
  check((*end == '\0' || *end == '\n') && *input != '\0', "Invalid number: %s", input);

  free(input);
  return 0;

error:
  if (input)
    free(input);
  return -1;
}

int read_scan(const char *fmt, ...)
{
  int i = 0;
  int rc = 0;
  long *out_int = NULL;
  char *out_char = NULL;
  char **out_string = NULL;
  int max_buffer = 0;

  va_list argp;
  va_start(argp, fmt);

  for (i = 0; fmt[i] != '\0'; i++)
  {
    if (fmt[i] == '%')
    {
      i++;
      switch (fmt[i])
      {
      case '\0':
        sentinel("Invalid format, you ended with %%.");
        break;

      case 'd':
        out_int = va_arg(argp, long *);
        rc = read_int(out_int);
        check(rc == 0, "Failed to read int.");
        break;

      case 'c':
        out_char = va_arg(argp, char *);
        *out_char = fgetc(stdin);
        break;

      case 's':
        max_buffer = va_arg(argp, int);
        out_string = va_arg(argp, char **);
        rc = read_string(out_string, max_buffer);
        check(rc == 0, "Failed to read string.");
        break;

      default:
        sentinel("Invalid, format.");
      }
    }
    else
    {
      fgetc(stdin);
    }

    check(!feof(stdin) && !ferror(stdin), "Input error.")
  }

  va_end(argp);
  return 0;

error:
  va_end(argp);
  return -1;
}

int print_out(const char *fmt, ...)
{
  int i = 0;
  int rc = 0;

  char tmp_char = '\0';
  char *tmp_str = calloc(1, MAX_DATA + 1);
  int tmp_int = 0;
  long tmp_long = 0;
  int fmt_length = strlen(fmt);
  int placeholder_count = 0;

  // Count placeholders in the template
  for (i = 0; fmt[i] != '\0'; i++)
  {
    if (fmt[i] == '%')
    {
      placeholder_count++;
    }
  }

  // Allocate enough memory
  char *output_str = calloc(1, fmt_length + placeholder_count * MAX_DATA);

  va_list argp;
  va_start(argp, fmt);

  for (i = 0; fmt[i] != '\0'; i++)
  {
    if (fmt[i] == '%')
    {
      i++;
      switch (fmt[i])
      {
      case '\0':
        sentinel("Invalid format, you ended with %%.");
        break;
      case 'c':
        tmp_char = va_arg(argp, int);
        strncat(output_str, &tmp_char, 1);
        break;
      case 'd':
        tmp_int = va_arg(argp, int);
        sprintf(tmp_str, "%d", tmp_int);
        strcat(output_str, tmp_str);
        break;
      case 'l':
        if (fmt[i + 1] != 'd')
        {
          sentinel("Invalid format, only 'd' and 'ld' supported");
          break;
        }
        tmp_long = va_arg(argp, long);
        sprintf(tmp_str, "%ld", tmp_long);
        strcat(output_str, tmp_str);
        i++;
        break;
      case 's':
        strcat(output_str, va_arg(argp, char *));
        break;

      default:
        break;
      }
    }
    else
    {
      strncat(output_str, &fmt[i], 1);
    }
  }

  fputs(output_str, stdout);

  va_end(argp);
  return 0;

error:
  va_end(argp);
  return -1;
}

int main(int argc, char *argv[])
{
  char *first_name = NULL;
  char initial = ' ';
  char *last_name = NULL;
  long age = 0;

  print_out("What's your first name? ");
  int rc = read_scan("%s", MAX_DATA, &first_name);
  check(rc == 0, "Failed first name.");

  print_out("What's your initial? ");
  rc = read_scan("%c\n", &initial);
  check(rc == 0, "Failed initial");

  print_out("What's your last name? ");
  rc = read_scan("%s", MAX_DATA, &last_name);
  check(rc == 0, "Failed last name");

  print_out("How old are you? ");
  rc = read_scan("%d", &age);
  check(rc == 0, "Failed to read age.");

  print_out("---- RESULTS 1 ----\n");
  print_out("First Name: %s\n", first_name);
  print_out("Initial: %c\n", initial);
  print_out("Last Name: %s\n", last_name);
  print_out("Age: %ld\n", age);

  print_out("---- RESULTS 2 ----\n");
  print_out("First Name: %s\nInitial: %c\nLast Name: %s\nAge: %ld\n", first_name, initial, last_name, age);

  free(first_name);
  free(last_name);
  return 0;

error:
  return -1;
}

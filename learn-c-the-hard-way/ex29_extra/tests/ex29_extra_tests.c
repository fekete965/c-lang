#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dbg.h"

#define LIB_FILE_NAME "libex29_extra.so"
#define MAX_DIR_LENGTH 100
#define MAX_LIB_FILE_LENGTH 150

typedef int (*lib_function)(const char *data, int length);

int run_test(void *lib, const char *function_name, const char *data, int data_length);

char *lib_file;

int main()
{
  char cwd[MAX_DIR_LENGTH];
  getcwd(cwd, MAX_DIR_LENGTH);

  check(strlen(cwd) > 0, "Could not obtain the current working directory");

  lib_file = malloc(MAX_LIB_FILE_LENGTH);
  check_mem(lib_file);

  snprintf(lib_file, MAX_LIB_FILE_LENGTH, "%s/build/%s", cwd, LIB_FILE_NAME);

  void *lib = dlopen(lib_file, RTLD_NOW);
  check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

  printf("\nSuccessful function calls\n");
  printf("-------------------------\n");
  run_test(lib, "print_a_message", "hello there", 11);
  run_test(lib, "uppercase", "hello there", 11);
  run_test(lib, "lowercase", "HELLO THERE", 11);
  run_test(lib, "fail_on_purpose", "I fail", 11);

  printf("\nUnsuccessful function calls\n");
  printf("---------------------------\n");
  int rc = run_test(lib, "fail_on_purpose", "It will fail", 11);
  check(rc == -1, "'fail_on_purpose' should have failed");
  rc = run_test(lib, "asasdasd", "asdasd", 11);
  check(rc == -1, "calling not existing function should have failed");
  printf("\n");

  rc = dlclose(lib);
  check(rc == 0, "Failed to close %s", lib_file);

  return 0;

error:
  return 1;
}

int run_test(void *lib, const char *function_name, const char *data, int data_length)
{
  printf("Testing (%s) with data '%s' and length: %d\n", function_name, data, data_length);
  lib_function func = dlsym(lib, function_name);
  check(func != NULL, "Did not find %s function in the library %s: %s", function_name, lib_file, dlerror());

  int rc = func(data, data_length);
  check(rc == 0, "Function %s return %d for data: %s | data length: %d", function_name, rc, data, data_length);

  return 0;

error:
  return -1;
}

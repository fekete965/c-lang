#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "dbg.h"

#define MINIMUM_ARG_COUNT 2
#define OR_ARGUMENT "-o"
#define FOUR_MEGABYTE 4096

typedef enum SearchLogic
{
  AND,
  OR,
} SearchLogic;

const char *LOG_FILE_EXTENSIONS[] = {".cef", ".csv", ".json", ".kvp", ".txt", ".xml"};

SearchLogic setup_search_logic(char **argv)
{
  int i = 0;

  for (i = 0; argv[i]; i++)
  {
    if (strcasestr(argv[i], OR_ARGUMENT))
    {
      log_info("Found -o flag, the search logic is set to OR\n");
      return OR;
    }
  }

  log_info("No -o flag was specified, the search logic is set to AND\n");
  return AND;
}

int is_log_file(char *file_name)
{
  int i = 0;
  int length = sizeof(LOG_FILE_EXTENSIONS) / sizeof(LOG_FILE_EXTENSIONS[0]);

  for (i = 0; i < length; i++)
  {
    char *partial_str = strrchr(file_name, '.');

    if (!partial_str)
    {
      return 0;
    }

    if (strcasecmp(partial_str, LOG_FILE_EXTENSIONS[i]) == 0)
    {
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  if (argc < MINIMUM_ARG_COUNT)
  {
    log_err("Missing argument(s), try: ./logfind test");

    return 1;
  }

  const char *HOME = getenv("HOME");
  const int HOME_PATH_LEN = strlen(HOME);

  int i = 0;
  DIR *home_dir_ptr = NULL;
  struct dirent *dp = NULL;
  FILE *log_file_ptr = NULL;
  SearchLogic logic = setup_search_logic(argv);
  char *file_path = NULL;
  int file_name_len = -1;
  int line_count = 1;
  char *line = malloc(sizeof(char) * FOUR_MEGABYTE);

  home_dir_ptr = opendir(HOME);
  check(home_dir_ptr != NULL, "Cannot open home directory");

  dp = readdir(home_dir_ptr);

  do
  {
    if (is_log_file(dp->d_name))
    {
      file_name_len = strlen(dp->d_name);
      check(file_name_len > 0, "Couldn't read the filename correctly");

      file_path = malloc(sizeof(char) * (HOME_PATH_LEN + file_name_len));
      check_mem(file_path);
      sprintf(file_path, "%s/%s", HOME, dp->d_name);

      log_file_ptr = fopen(file_path, "r");
      check(log_file_ptr != NULL, "Could not open file: %s", file_path);

      while (fgets(line, FOUR_MEGABYTE, log_file_ptr) != NULL)
      {
        for (i = 0; argv[i]; i++)
        {
          if (strstr(line, argv[i]))
          {
            printf("File [%s:%d] <> [%s]\n", file_path, line_count, argv[i]);
          }
        }

        line_count++;
      }

      line_count = 1;
      fclose(log_file_ptr);
      log_file_ptr = NULL;
    }

    dp = readdir(home_dir_ptr);
  } while (dp != NULL);

  if (home_dir_ptr != NULL)
    closedir(home_dir_ptr);
  if (dp != NULL)
    free(dp);
  if (file_path != NULL)
    free(file_path);
  if (log_file_ptr != NULL)
    fclose(log_file_ptr);
  return 0;

error:
  if (home_dir_ptr != NULL)
    closedir(home_dir_ptr);
  if (dp != NULL)
    free(dp);
  if (file_path != NULL)
    free(file_path);
  if (log_file_ptr != NULL)
    fclose(log_file_ptr);

  return -1;
}

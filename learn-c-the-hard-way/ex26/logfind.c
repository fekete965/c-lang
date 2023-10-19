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

typedef struct MatchData
{
  int line_number;
  char *word;
} MatchData;

const char *LOG_FILE_EXTENSIONS[] = {".cef", ".csv", ".json", ".kvp", ".txt", ".xml"};

SearchLogic setup_search_logic(char **argv)
{
  int i = 0;

  for (i = 0; argv[i]; i++)
  {
    if (strcasestr(argv[i], OR_ARGUMENT))
    {
      log_info("Found -o flag, the search logic is set to OR");
      return OR;
    }
  }

  log_info("No -o flag was specified, the search logic is set to AND");
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

void free_matches(MatchData **matches, int size)
{
  int i = 0;

  for (i = 0; i < size; i++)
  {
    if (matches[i] != NULL && matches[i]->word != NULL)
    {
      free(matches[i]->word);
    }
  }
}

int search_and(FILE *log_file_ptr, char *file_path, int argc, char **argv, int *line_count)
{
  MatchData **matches = NULL;
  char *line = NULL;
  int match_count = 0;
  int word_length = 0;
  int i = 1;

  matches = malloc(sizeof(MatchData) * argc);
  check_mem(matches);

  line = malloc(sizeof(char) * FOUR_MEGABYTE);
  check_mem(line);

  while (fgets(line, FOUR_MEGABYTE, log_file_ptr) != NULL)
  {
    for (i = 1; argv[i]; i++)
    {
      if (strcasestr(line, argv[i]))
      {
        word_length = strlen(argv[i]);

        matches[match_count] = malloc(sizeof(MatchData));
        matches[match_count]->line_number = *line_count;
        matches[match_count]->word = malloc(sizeof(char) * word_length);
        check_mem(matches[match_count]->word);

        strncpy(matches[match_count]->word, argv[i], word_length);

        match_count++;
      }
    }

    (*line_count)++;
  }

  // Check if we have found every word in the file
  // If we have, print the line + word to the user
  if (i == match_count + 1)
  {
    for (i = 0; i < match_count; i++)
    {
      printf("File: %s:%d --> %s\n", file_path, matches[i]->line_number, matches[i]->word);
    }
  }
  else
  {
    // Otherwise, reset the matches to 0
    match_count = 0;
  }

  free(line);
  free_matches(matches, argc);

  return match_count;

error:
  if (line != NULL)
    free(line);
  if (matches != NULL)
    free_matches(matches, argc);
  return -1;
}

int search_or(FILE *log_file_ptr, char *file_path, char **argv, int *line_count)
{
  char *line = malloc(sizeof(char) * FOUR_MEGABYTE);
  int match_count = 0;
  int i = 1;

  while (fgets(line, FOUR_MEGABYTE, log_file_ptr) != NULL)
  {
    for (i = 1; argv[i]; i++)
    {

      // We want to ignore argv if it is our option flag (-0), otherwise try to match the word
      if (strcasecmp(argv[i], OR_ARGUMENT) != 0 && strcasestr(line, argv[i]))
      {
        printf("File: %s:%d --> %s\n", file_path, (*line_count), argv[i]);
        match_count++;
      }
    }

    (*line_count)++;
  }

  return match_count;
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

  DIR *home_dir_ptr = NULL;
  struct dirent *dp = NULL;
  FILE *log_file_ptr = NULL;
  SearchLogic logic = setup_search_logic(argv);
  char *file_path = NULL;
  int file_name_len = -1;
  int line_count = 1;
  int matches = 0;

  home_dir_ptr = opendir(HOME);
  check(home_dir_ptr != NULL, "Cannot open home directory");

  dp = readdir(home_dir_ptr);

  do
  {
    if (is_log_file(dp->d_name))
    {
      line_count = 1;

      file_name_len = strlen(dp->d_name);
      check(file_name_len > 0, "Couldn't read the filename correctly");

      file_path = malloc(sizeof(char) * (HOME_PATH_LEN + file_name_len));
      check_mem(file_path);
      sprintf(file_path, "%s/%s", HOME, dp->d_name);

      log_file_ptr = fopen(file_path, "r");
      check(log_file_ptr != NULL, "Could not open file: %s", file_path);

      switch (logic)
      {
      case AND:
        matches += search_and(log_file_ptr, file_path, argc, argv, &line_count);
        break;
      case OR:
        matches += search_or(log_file_ptr, file_path, argv, &line_count);
        break;
      default:
        sentinel("Unsupported search logic");
      }

      fclose(log_file_ptr);
      log_file_ptr = NULL;
    }

    dp = readdir(home_dir_ptr);
  } while (dp != NULL);

  printf("Total matches: %d\n", matches);

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

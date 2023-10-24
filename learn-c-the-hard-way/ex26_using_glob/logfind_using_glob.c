#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <glob.h>
#include <errno.h>
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

  SearchLogic logic = setup_search_logic(argv);
  glob_t glob_buf;
  FILE *log_file_ptr = NULL;
  char *file_path = NULL;
  int file_path_len = -1;
  int line_count = 1;
  int matches = 0;
  int i = 0;
  int j = 0;
  int r = -1;
  int log_extensions_len = sizeof(LOG_FILE_EXTENSIONS) / sizeof(LOG_FILE_EXTENSIONS[0]);
  int ext_len = 0;

  for (i = 0; i < log_extensions_len; i++)
  {
    ext_len = strlen(LOG_FILE_EXTENSIONS[i]);
    file_path_len = HOME_PATH_LEN + ext_len + 3;

    if (file_path == NULL)
    {
      file_path = malloc(sizeof(char) * file_path_len);

      check_mem(file_path);
    }
    else
    {
      file_path = realloc(file_path, file_path_len);
      check_mem(file_path);
    }

    snprintf(file_path, file_path_len, "%s/*%s", HOME, LOG_FILE_EXTENSIONS[i]);

    r = glob(file_path, GLOB_ERR, NULL, &glob_buf);

    if (r != 0)
    {
      if (r == GLOB_NOMATCH)
      {
        printf("No match found for: *%s\n", LOG_FILE_EXTENSIONS[i]);
      }
      else
      {
        log_err("Glob error: %s", strerror(errno));
        goto error;
      }
    }

    for (j = 0; j < glob_buf.gl_pathc; j++)
    {
      log_file_ptr = fopen(glob_buf.gl_pathv[j], "r");

      check(log_file_ptr != NULL, "Could not open file: %s", glob_buf.gl_pathv[j]);

      switch (logic)
      {
      case AND:
        matches += search_and(log_file_ptr, glob_buf.gl_pathv[j], argc, argv, &line_count);
        break;
      case OR:
        matches += search_or(log_file_ptr, glob_buf.gl_pathv[j], argv, &line_count);
      default:
        sentinel("Unsupported search logic")
      }
    }

    fclose(log_file_ptr);
  }

  printf("Total matches: %d\n", matches);

  globfree(&glob_buf);
  if (file_path != NULL)
    free(file_path);
  if (log_file_ptr != NULL)
    fclose(log_file_ptr);
  return 0;

error:
  globfree(&glob_buf);
  if (file_path != NULL)
    free(file_path);
  if (log_file_ptr != NULL)
    fclose(log_file_ptr);

  return -1;
}

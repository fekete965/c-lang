#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "dbg.h"
#include "duff_macros.h"

#define BILLION 1000000000L;

int normal_copy(char *from, char *to, int count)
{
  int i = 0;

  for (i = 0; i < count; i++)
  {
    to[i] = from[i];
  }

  return i;
}

int duffs_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch (count % 8)
    {
    case 0:
      do
      {
        *to++ = *from++;
      case 7:
        *to++ = *from++;
      case 6:
        *to++ = *from++;
      case 5:
        *to++ = *from++;
      case 4:
        *to++ = *from++;
      case 3:
        *to++ = *from++;
      case 2:
        *to++ = *from++;
      case 1:
        *to++ = *from++;
      } while (--n > 0);
    }
  }

  return count;
}

int duffs_device_macro(char *from, char *to, int count)
{
  {
    dd_start_device(32, count);
    dd_create_sixteen_cases(32);
    dd_create_eight_cases(16);
    dd_create_four_cases(8);
    dd_create_two_cases(4);
    dd_create_case(1);
    dd_end_device;

    return count;
  }
}

int zeds_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch (count % 8)
    {
    case 0:
    again:
      *to++ = *from++;

    case 7:
      *to++ = *from++;
    case 6:
      *to++ = *from++;
    case 5:
      *to++ = *from++;
    case 4:
      *to++ = *from++;
    case 3:
      *to++ = *from++;
    case 2:
      *to++ = *from++;
    case 1:
      *to++ = *from++;
      if (--n > 0)
        goto again;
    }
  }

  return count;
}

int valid_copy(char *data, int count, char expects)
{
  int i = 0;
  for (i = 0; i < count; i++)
  {
    if (data[i] != expects)
    {
      log_err("[%d] %c != %c", i, data[i], expects);
      return 0;
    }
  }

  return 1;
}

long long get_timestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);

  long long delta = (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
  return delta;
}

void get_cpu_clock_time(struct timespec *t)
{
  if (clock_gettime(CLOCK_REALTIME, t) == -1)
  {
    log_err("Getting clock time failed");
    exit(1);
  }
}

void log_cpu_clock_time_diff(struct timespec *a, struct timespec *b)
{
  double delta = (b->tv_sec - a->tv_sec) + (double)(b->tv_nsec - a->tv_nsec) / (double)BILLION;

  log_info("Ending Duff's device finished in %f seconds", delta);
}

int main(int argc, char *argv[])
{
  char from[1000] = {'a'};
  char to[1000] = {'c'};
  int rc = 0;

  long long timestamp = 0;
  long long delta = 0;
  struct timespec t1, t2;

  // set up the from to have some stuff
  memset(from, 'x', 1000);

  // set it to a failure mode
  memset(to, 'y', 1000);
  check(valid_copy(to, 1000, 'y'), "Not initalized right.");

  // use normal copy to
  rc = normal_copy(from, to, 1000);
  check(rc == 1000, "Normal copy failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Normal copy failed.");

  // reset
  memset(to, 'y', 1000);

  // duff version
  log_info("Starting Duff's device");
  timestamp = get_timestamp();
  get_cpu_clock_time(&t1);

  rc = duffs_device(from, to, 1000);

  get_cpu_clock_time(&t2);
  delta = timestamp - get_timestamp();

  log_cpu_clock_time_diff(&t1, &t2);
  log_info("Ending Duff's device finished in: %lli\n", delta);

  check(rc == 1000, "Duff's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duff's device failed copy.");

  // reset
  memset(to, 'y', 1000);

  // my version
  log_info("Starting Zed's device");
  timestamp = get_timestamp();
  get_cpu_clock_time(&t1);

  rc = zeds_device(from, to, 1000);

  get_cpu_clock_time(&t2);
  delta = timestamp - get_timestamp();

  log_cpu_clock_time_diff(&t1, &t2);
  log_info("Ending Zed's device finished in: %lli\n", delta);

  check(rc == 1000, "Zed's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Zed's device failed copy.");

  // reset
  memset(to, 'y', 1000);

  // macro version
  log_info("Starting Duff's device macro");
  timestamp = get_timestamp();
  get_cpu_clock_time(&t1);

  rc = duffs_device_macro(from, to, 1000);

  get_cpu_clock_time(&t2);
  delta = timestamp - get_timestamp();

  log_cpu_clock_time_diff(&t1, &t2);
  log_info("Ending Duff's device macro finished in: %lli\n", delta);

  check(rc == 1000, "Duff's device macro failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duff's device macro failed copy.");

  log_info("Starting memset");
  get_cpu_clock_time(&t1);

  memset(to, 'y', 1000);

  get_cpu_clock_time(&t2);
  log_cpu_clock_time_diff(&t1, &t2);
  log_info("Ending memset\n");

  log_info("Starting memmove");
  get_cpu_clock_time(&t1);

  memmove(to, from, 1000);

  get_cpu_clock_time(&t2);
  log_cpu_clock_time_diff(&t1, &t2);
  log_info("Ending memmove\n");

  log_info("Starting memcpy");
  get_cpu_clock_time(&t1);

  memcpy(from, to, 1000);

  get_cpu_clock_time(&t2);
  log_cpu_clock_time_diff(&t1, &t2);
  log_info("Ending memcpy");

  return 0;
error:
  return 1;
}

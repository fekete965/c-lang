#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_ROWS 255
#define MAX_DATA 255

struct Address
{
  int id;
  int set;
  int height;
  int weight;
  char first_name[MAX_DATA];
  char last_name[MAX_DATA];
  char email[MAX_DATA];
  char phone[MAX_DATA];
};

struct Database
{
  int max_data;
  int max_rows;
  struct Address rows[MAX_ROWS];
};

struct Connection
{
  FILE *file;
  struct Database *db;
};

void Address_print(struct Address *addr);
void die(struct Connection *conn, const char *message);
void Database_close(struct Connection *conn);
void Database_create(struct Connection *conn, int max_rows, int max_data);
void Database_delete(struct Connection *conn, int id);
void Database_find(struct Connection *conn, char field, char *query);
void Database_get(struct Connection *conn, int id);
void Database_list(struct Connection *conn);
void Database_load(struct Connection *conn);
struct Connection *Database_open(const char *filename, char mode);
int Database_run_query(struct Connection *conn, struct Address *addr, char field, char *query);
void Database_set(
    struct Connection *conn,
    int id,
    const char *first_name,
    const char *last_name,
    const char *email,
    const char *phone,
    const int height,
    const int weight);
void Database_write(struct Connection *conn);
void validate_new_ptr(struct Connection *conn, void *ptr, const char *message);

void die(struct Connection *conn, const char *message)
{
  if (errno)
  {
    perror(message);
  }
  else
  {
    printf("ERROR: %s\n", message);
  }

  Database_close(conn);

  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s %s %dcm %dkg\n", addr->id, addr->first_name, addr->last_name, addr->email, addr->height, addr->weight);
}

void Database_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die(conn, "Failed to load database");
}

struct Connection *Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn)
    die(conn, "Memory error");

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db)
    die(conn, "Memory error");

  if (mode == 'c')
  {
    conn->file = fopen(filename, "w");
  }
  else
  {
    conn->file = fopen(filename, "r+");

    if (conn->file)
    {
      Database_load(conn);
    }
  }

  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn)
  {
    if (conn->file)
      fclose(conn->file);
    if (conn->db)
      free(conn->db);
    free(conn);
  }
}

void Database_write(struct Connection *conn)
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die(conn, "Failed to write database");

  rc = fflush(conn->file);
  if (rc == -1)
    die(conn, "cannot flush database");
}

void Database_create(struct Connection *conn, int max_rows, int max_data)
{
  int i = 0;

  for (i = 0; i < max_rows; i++)
  {
    // make a prototype to initialize it
    struct Address addr = {
        .id = i,
        .set = 0,
        .height = 0,
        .weight = 0};

    conn->db->rows[i] = addr;
  }

  conn->db->max_data = max_data;
  conn->db->max_rows = max_rows;
}

void Database_set(
    struct Connection *conn,
    int id,
    const char *first_name,
    const char *last_name,
    const char *email,
    const char *phone,
    const int height,
    const int weight)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set)
    die(conn, "Already set, delete it first");

  addr->set = 1;

  int DB_MAX_DATA = conn->db->max_data;

  char *res = strncpy(addr->first_name, first_name, DB_MAX_DATA - 1);
  if (!res)
    die(conn, "First name copy failed");
  addr->first_name[DB_MAX_DATA - 1] = '\0';

  res = strncpy(addr->last_name, last_name, DB_MAX_DATA);
  if (!res)
    die(conn, "Last name copy failed");
  addr->last_name[DB_MAX_DATA - 1] = '\0';

  res = strncpy(addr->email, email, DB_MAX_DATA);
  if (!res)
    die(conn, "Email copy failed");
  addr->email[DB_MAX_DATA - 1] = '\0';

  res = strncpy(addr->phone, phone, DB_MAX_DATA);
  if (!res)
    die(conn, "Phone copy failed");
  addr->phone[DB_MAX_DATA - 1] = '\0';

  addr->height = height;
  addr->weight = weight;
}

void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if (addr->set)
  {
    Address_print(addr);
  }
  else
  {
    die(conn, "ID is not set");
  }
}

void Database_delete(struct Connection *conn, int id)
{
  struct Address addr = {
      .id = id,
      .set = 0,
      .height = 0,
      .weight = 0,
  };
  memset(addr.first_name, 0, strlen(addr.first_name));
  memset(addr.last_name, 0, strlen(addr.last_name));
  memset(addr.email, 0, strlen(addr.email));
  memset(addr.phone, 0, strlen(addr.phone));
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i < db->max_rows; i++)
  {
    struct Address *cur = &db->rows[i];
    if (cur->set)
    {
      Address_print(cur);
    }
  }
}

int Database_run_query(struct Connection *conn, struct Address *addr, char field, char *query)
{
  switch (field)
  {
  case 'f':
    return strstr(addr->first_name, query) != NULL;
  case 'l':
    return strstr(addr->last_name, query) != NULL;
  case 'e':
    return strstr(addr->email, query) != NULL;
  case 'p':
    return strstr(addr->phone, query) != NULL;
  case 'h':
    return addr->height == atoi(query);
  case 'w':
    return addr->weight == atoi(query);
  default:
    die(conn, "Invalid action: f=first_name, l=last_name, e=email, p=phone, h=height, w=weight");
    return 1;
  }
}

void Database_find(struct Connection *conn, char field, char *query)
{
  struct Database *db = conn->db;
  struct Address *cur = NULL;
  int i = 0;

  for (i = 0; i < db->max_rows; i++)
  {
    cur = &db->rows[i];

    if (Database_run_query(conn, cur, field, query))
    {
      break;
    }
  }

  if (cur)
  {
    Address_print(cur);
  }
  else
  {
    int error_msg_size = db->max_data + 50;
    char error_msg[error_msg_size];

    strcpy(error_msg, "Record cannot be found: ");
    strncat(error_msg, query, sizeof(error_msg) - strlen(error_msg) - 1);

    die(conn, error_msg);
  }
}

void validate_new_ptr(struct Connection *conn, void *ptr, const char *message)
{
  if (ptr == NULL)
    die(conn, message);
}

int main(int argc, char *argv[])
{
  if (argc < 3)
    die(NULL, "USAGE: ex17 <dbfile> <action> [action params]");

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);
  int id = 0;

  switch (action)
  {
  case 'c':
    if (argc != 5)
      die(conn, "Need a max_rows and max_data");

    int max_rows = atoi(argv[3]);
    if (max_rows == 0)
      die(conn, "max_rows number has to be more than 0");

    if (max_rows > MAX_ROWS)
    {
      char msg[50] = "max_rows cannot be more than ";
      char converted_max_rows[5];
      sprintf(converted_max_rows, "%d", MAX_ROWS);
      strcpy(msg, converted_max_rows);
      die(conn, msg);
    }

    int max_data = atoi(argv[4]);
    if (max_data == 0)
      die(conn, "max_data has to be more than 0");

    if (max_data > MAX_DATA)
    {
      char msg[50] = "max_data cannot be more than";
      char converted_max_data[5];
      sprintf(converted_max_data, "%d", MAX_DATA);
      strcpy(msg, converted_max_data);
      die(conn, msg);
    }

    Database_create(conn, max_rows, max_data);
    Database_write(conn);
    break;

  case 'g':
    if (argc != 4)
      die(conn, "Need an id to get");

    id = atoi(argv[3]);
    if (id >= conn->db->max_rows)
      die(conn, "There's not that many records");

    Database_get(conn, id);
    break;

  case 's':
    if (argc != 10)
      die(conn, "Need id, first name, last name, email, phone, height, weight to set");

    id = atoi(argv[3]);
    if (id >= conn->db->max_rows)
      die(conn, "There's not that many records");

    Database_set(conn, id, argv[4], argv[5], argv[6], argv[7], atoi(argv[8]), atoi(argv[9]));
    Database_write(conn);
    break;

  case 'd':
    if (argc != 4)
      die(conn, "Need id to delete");

    id = atoi(argv[3]);
    if (id >= conn->db->max_rows)
      die(conn, "There's not that many records");

    Database_delete(conn, id);
    Database_write(conn);
    break;

  case 'l':
    Database_list(conn);
    break;

  case 'f':
    if (argc < 4)
      die(conn, "Need to target a field: f=first_name, l=last_name, e=email, p=phone, h=height, w=weight");

    if (argc != 5)
      die(conn, "Need something to look for");

    Database_find(conn, argv[3][0], argv[4]);
    break;

  default:
    die(conn, "Invalid action: c=create, g=get, s=set, d=del, l=list, f=find");
  }

  Database_close(conn);

  return 0;
}

#include <sqlite3.h>

int connectDb(sqlite3 *db);
int loginAccount(char *number, char *personnal);
void selectAccount(char *number, char *personnal);
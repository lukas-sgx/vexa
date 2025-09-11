#include <sqlite3.h>

int connectDb(sqlite3 *db);
int loginAccount(char *number, char *personnal);
void selectAccount(char *number, char *personnal);
float balance(char *number, char *personnal);
int IBAN(char *iban);
void transfert(char *sum, char *iban, char *myIban);
char* myIBAN(char *number, char *personnal, char *out_iban, size_t size);
void lastTransaction(char *myIban, int count);
#include <stdio.h>
#include <sqlite3.h>

void connectDb(){
    sqlite3 *db;
    int rc = sqlite3_open("account.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Opened database successfully!\n");
    }
}


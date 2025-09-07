#include <stdio.h>
#include <sqlite3.h>

#include "include/screen.h"

int connectDb(sqlite3 **db){
    int rc = sqlite3_open("account.db", db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    }

    return SQLITE_OK;
}

int loginAccount(char *number, char *personnal){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = connectDb(&db);

    const char *sql = "SELECT * FROM account WHERE number = ? AND personnal = ? LIMIT 1;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    sqlite3_bind_text(stmt, 1, number, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, personnal, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        return 1;
    }else{
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void selectAccount(char *number){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = connectDb(&db);

    const char *sql = "SELECT name, ftName FROM account WHERE number = ?  LIMIT 1;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    sqlite3_bind_text(stmt, 1, number, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        const unsigned char *name   = sqlite3_column_text(stmt, 0);
        const unsigned char *ftName = sqlite3_column_text(stmt, 1);

        printf(" Welcome %s %s !\n\n", name, ftName);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
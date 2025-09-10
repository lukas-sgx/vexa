#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "include/screen.h"
#include "include/colors.h"

int connectDb(MYSQL **conn){
    if (!mysql_real_connect(*conn, "127.0.0.1", "root", "root", "account", 3306, NULL, 0)) {
        fprintf(stderr, "Erreur connexion : %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return 0;
    }
    return 1;
}

int loginAccount(char *number, char *personnal){
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2], result[1];

    conn = mysql_init(NULL);
    if (!connectDb(&conn)) return 0;

    const char *query = "SELECT COUNT(*) FROM user WHERE number=? AND personnal=?";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur mysql_stmt_init : %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Erreur mysql_stmt_prepare : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }
    
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)number;
    bind[0].buffer_length = strlen(number);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)personnal;
    bind[1].buffer_length = strlen(personnal);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Erreur bind_param : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur execute : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    memset(result, 0, sizeof(result));
    int count = 0;
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = (char *)&count;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "Erreur bind_result : %s\n", mysql_stmt_error(stmt));
    }

    int found = 0;
    if (mysql_stmt_fetch(stmt) == 0) {
        if (count > 0) found = 1;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return found;
}

void selectAccount(char *number, char *personnal){
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2], result[2];

    char out_name[100], out_prenom[100];
    unsigned long name_len, prenom_len;

    conn = mysql_init(NULL);
    connectDb(&conn);

    const char *query = "SELECT name, prenom FROM user WHERE number=? AND personnal=? LIMIT 1";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur mysql_stmt_init : %s\n", mysql_error(conn));
        mysql_close(conn);
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Erreur mysql_stmt_prepare : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)number;
    bind[0].buffer_length = strlen(number);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)personnal;
    bind[1].buffer_length = strlen(personnal);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Erreur bind_param : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur execute : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }

    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = out_name;
    result[0].buffer_length = sizeof(out_name);
    result[0].length = &name_len;

    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = out_prenom;
    result[1].buffer_length = sizeof(out_prenom);
    result[1].length = &prenom_len;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "Erreur bind_result : %s\n", mysql_stmt_error(stmt));
    }

    if (mysql_stmt_fetch(stmt) == 0) {
        if (name_len >= sizeof(out_name)) name_len = sizeof(out_name) - 1;
        if (prenom_len >= sizeof(out_prenom)) prenom_len = sizeof(out_prenom) - 1;
        out_name[name_len] = '\0';
        out_prenom[prenom_len] = '\0';
        
        printf("Welcome %s %s !\n", out_name, out_prenom);
        printf("type 'help' to show informations\n\n");
    }


    mysql_stmt_close(stmt);
    mysql_close(conn);
}

float balance(char *number, char *personnal){
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2], result[1];

    char out_sold[100];
    unsigned long sold_len;

    conn = mysql_init(NULL);
    connectDb(&conn);

    const char *query = "SELECT solde FROM user WHERE number=? AND personnal=? LIMIT 1";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur mysql_stmt_init : %s\n", mysql_error(conn));
        mysql_close(conn);
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Erreur mysql_stmt_prepare : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)number;
    bind[0].buffer_length = strlen(number);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)personnal;
    bind[1].buffer_length = strlen(personnal);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Erreur bind_param : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur execute : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }

    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = out_sold;
    result[0].buffer_length = sizeof(out_sold);
    result[0].length = &sold_len;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "Erreur bind_result : %s\n", mysql_stmt_error(stmt));
    }

    if (mysql_stmt_fetch(stmt) == 0) {
        if (sold_len >= sizeof(out_sold)) sold_len = sizeof(out_sold) - 1;
        out_sold[sold_len] = '\0';
        
        return atof(out_sold);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return 0;
}

int IBAN(char *iban){
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1], result[1];

    conn = mysql_init(NULL);
    if (!connectDb(&conn)) return 0;

    const char *query = "SELECT COUNT(*) FROM user WHERE iban=?";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur mysql_stmt_init : %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Erreur mysql_stmt_prepare : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }
    
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)iban;
    bind[0].buffer_length = strlen(iban);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Erreur bind_param : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur execute : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    memset(result, 0, sizeof(result));
    int count = 0;
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = (char *)&count;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "Erreur bind_result : %s\n", mysql_stmt_error(stmt));
    }

    int found = 0;
    if (mysql_stmt_fetch(stmt) == 0) {
        if (count > 0) found = 1;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return found;
}

char* myIBAN(char *number, char *personnal, char *out_iban, size_t size){
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2], result[1];
    unsigned long iban_len;

    conn = mysql_init(NULL);
    connectDb(&conn);

    const char *query = "SELECT iban FROM user WHERE number=? AND personnal=? LIMIT 1";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur mysql_stmt_init : %s\n", mysql_error(conn));
        mysql_close(conn);
        return out_iban;
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Erreur mysql_stmt_prepare : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return out_iban;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = number;
    bind[0].buffer_length = strlen(number);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = personnal;
    bind[1].buffer_length = strlen(personnal);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Erreur bind_param : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return out_iban;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur execute : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return out_iban;
    }

    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = out_iban;
    result[0].buffer_length = size;
    result[0].length = &iban_len;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "Erreur bind_result : %s\n", mysql_stmt_error(stmt));
    }

    if (mysql_stmt_fetch(stmt) == 0) {
        if (iban_len >= size) iban_len = size - 1;
        out_iban[iban_len] = '\0';
    } else {
        out_iban[0] = '\0';
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return out_iban;
}

void transfert(char *sum, char *iban, char *myIban) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[3];

    conn = mysql_init(NULL);
    connectDb(&conn);

    // ⚡ Démarrer une transaction
    if (mysql_query(conn, "START TRANSACTION")) {
        fprintf(stderr, "Erreur START TRANSACTION: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // 1️⃣ Insérer dans la table transactions
    const char *sql_insert = "INSERT INTO transactions (fromAcc, toAcc, price, type) VALUES (?, ?, ?, 'transfert')";
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql_insert, strlen(sql_insert))) {
        fprintf(stderr, "Erreur prepare insert: %s\n", mysql_stmt_error(stmt));
        goto rollback;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = myIban;
    bind[0].buffer_length = strlen(myIban);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = iban;
    bind[1].buffer_length = strlen(iban);

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = sum;
    bind[2].buffer_length = strlen(sum);

    if (mysql_stmt_bind_param(stmt, bind) || mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur insert transaction: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        goto rollback;
    }
    mysql_stmt_close(stmt);

    // 2️⃣ Débiter l’expéditeur
    const char *sql_debit = "UPDATE user SET solde = solde - ? WHERE iban = ?";
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql_debit, strlen(sql_debit))) {
        fprintf(stderr, "Erreur prepare debit: %s\n", mysql_stmt_error(stmt));
        goto rollback;
    }

    MYSQL_BIND bind_debit[2];
    memset(bind_debit, 0, sizeof(bind_debit));

    bind_debit[0].buffer_type = MYSQL_TYPE_STRING;
    bind_debit[0].buffer = sum;
    bind_debit[0].buffer_length = strlen(sum);

    bind_debit[1].buffer_type = MYSQL_TYPE_STRING;
    bind_debit[1].buffer = myIban;
    bind_debit[1].buffer_length = strlen(myIban);

    if (mysql_stmt_bind_param(stmt, bind_debit) || mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur debit: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        goto rollback;
    }
    mysql_stmt_close(stmt);

    // 3️⃣ Créditer le destinataire
    const char *sql_credit = "UPDATE user SET solde = solde + ? WHERE iban = ?";
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql_credit, strlen(sql_credit))) {
        fprintf(stderr, "Erreur prepare credit: %s\n", mysql_stmt_error(stmt));
        goto rollback;
    }

    MYSQL_BIND bind_credit[2];
    memset(bind_credit, 0, sizeof(bind_credit));

    bind_credit[0].buffer_type = MYSQL_TYPE_STRING;
    bind_credit[0].buffer = sum;
    bind_credit[0].buffer_length = strlen(sum);

    bind_credit[1].buffer_type = MYSQL_TYPE_STRING;
    bind_credit[1].buffer = iban;
    bind_credit[1].buffer_length = strlen(iban);

    if (mysql_stmt_bind_param(stmt, bind_credit) || mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur credit: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        goto rollback;
    }
    mysql_stmt_close(stmt);

    if (mysql_query(conn, "COMMIT")) {
        fprintf(stderr, "Erreur COMMIT: %s\n", mysql_error(conn));
        goto rollback;
    }

    printf("%sTransfert approuvé: %s€%s\n", GREEN, sum, WHITE);
    mysql_close(conn);
    return;

    rollback:
        mysql_query(conn, "ROLLBACK");
        fprintf(stderr, "❌ Transfert annulé\n");
        mysql_close(conn);
}



/*char* searchUserByIban(char *out_name, char *out_prenom, char* byiban){
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2], result[2];
    unsigned long iban_len;

    conn = mysql_init(NULL);
    connectDb(&conn);

    const char *query = "SELECT iban FROM user WHERE number=? AND personnal=? LIMIT 1";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "Erreur mysql_stmt_init : %s\n", mysql_error(conn));
        mysql_close(conn);
        return out_iban;
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Erreur mysql_stmt_prepare : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return out_iban;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = number;
    bind[0].buffer_length = strlen(number);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = personnal;
    bind[1].buffer_length = strlen(personnal);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Erreur bind_param : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return out_iban;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Erreur execute : %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return out_iban;
    }

    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = out_iban;
    result[0].buffer_length = size;
    result[0].length = &iban_len;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "Erreur bind_result : %s\n", mysql_stmt_error(stmt));
    }

    if (mysql_stmt_fetch(stmt) == 0) {
        if (iban_len >= size) iban_len = size - 1;
        out_iban[iban_len] = '\0';
    } else {
        out_iban[0] = '\0';
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return out_iban;
}*/
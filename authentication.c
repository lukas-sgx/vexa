#include <stdio.h>
#include <string.h>

#include "include/db.h"

#define MAX_LENGTH 25

void scan(char *buffer){
    char newBuffer[MAX_LENGTH];

    printf("> ");
    if(fgets(newBuffer, sizeof(newBuffer), stdin) != NULL){
        newBuffer[strcspn(newBuffer, "\n")] = 0;
        snprintf(buffer, MAX_LENGTH, "%s", newBuffer);
    }
}

int auth_bank(){
    char accountNumber[100];
    
    printf("Account number\n");
    scan(accountNumber);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "include/db.h"
#include "include/screen.h"

#define MAX_LENGTH 25
#define INPUT 0
#define PASS 1

void scan(char *buffer, int type){
    struct termios oldt, newt;
    char newBuffer[MAX_LENGTH];

    if(type){
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        newt.c_lflag &= ~(ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }

    printf("> ");
    fflush(stdout);
    if(fgets(newBuffer, sizeof(newBuffer), stdin) != NULL){
        newBuffer[strcspn(newBuffer, "\n")] = 0;
        snprintf(buffer, MAX_LENGTH, "%s", newBuffer);
    }

    if(type){
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        printf("\n");
    }
}

void auth_bank(){
    char accountNumber[100];
    char personnalCode[100];
    
    printf("Account Number");
    scan(accountNumber, INPUT);
    printf("Personnal Code");
    scan(personnalCode, PASS);
    printf("\n\n");

    if(loginAccount(accountNumber, personnalCode)){
        char target[100];
        int run = 1;

        init();
        selectAccount(accountNumber, personnalCode);

        while (run)
        {
            scan(target, INPUT);

            if(strcmp(target, "quit") == 0){
                run = 0;
            }else if(strcmp(target, "help") == 0){
                printf("HELP:\n");
            }
        }
    } else {
        printf("❌ Worst Identifier\n");
        auth_bank();
    }
    
}

void auth_blockchain(){

}
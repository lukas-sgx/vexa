#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#include "include/colors.h"
#include "include/db.h"
#include "include/screen.h"

#define MAX_LENGTH 100
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
    fflush(stdout);
}


bool isNumber(const char *s) {
    int dot_count = 0;
    if (*s == '\0') return false;

    for (int i = 0; s[i]; i++) {
        if (s[i] == '.') {
            dot_count++;
            if (dot_count > 1) return false;
        } else if (!isdigit((unsigned char)s[i])) {
            return false;
        }
    }
    return true;
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

            if((strcmp(target, "quit") == 0)|| (strcmp(target, "\\q") == 0)){
                run = 0;
            }else if((strcmp(target, "help") == 0) || (strcmp(target, "\\h") == 0)){
                help();
            }else if((strcmp(target, "balance") == 0) || (strcmp(target, "\\b") == 0)){
                float stock = balance(accountNumber, personnalCode);
                printf("Remaining Banlance: ");
                if(stock >= 0){
                    printf("%s%.2f€\n%s""", GREEN, stock, WHITE);
                }else{
                    printf("%s%.2f€\n%s""", RED, stock, WHITE);
                }
            }else if((strcmp(target, "switch") == 0) || (strcmp(target, "\\x") == 0)){
                init();
                auth_bank();
            }else if((strcmp(target, "clear") == 0) || (strcmp(target, "\\c") == 0)){
                init();
                printf("type 'help' to show informations\n\n");
            }else if((strncmp(target, "transfert", 9) == 0) || (strncmp(target, "\\t", 2) == 0)){
                float stock = balance(accountNumber, personnalCode);
                char *token = strtok(target, " ");
                int i = 0;
                char *iban = NULL, *sum = NULL;
                char myiban[100];

                while (token != NULL) {
                    if (*token != '\0') { 
                        if (i == 1) {
                            sum = token;
                        } else if (i == 2) {
                            iban = token;
                        }
                        i++;
                    }
                    token = strtok(NULL, " ");
                }

                if ((sum == NULL || iban == NULL) || (!isNumber(sum))) {
                    printf("Invalid command. Usage: transfert <amount> <iban>\n");
                    continue;
                }else{
                    if((stock >= atof(sum)) && (IBAN(iban)) && (strcmp(myIBAN(accountNumber, personnalCode, myiban, sizeof(myiban)), iban))){
                        transfert(sum, iban, myiban);
                    }else{
                        printf("%sTranfert denied%s\n", RED, WHITE);
                    }
                }
            }else if((strcmp(target, "statement") == 0) || (strcmp(target, "\\s") == 0)){
                char myiban[100];

                myIBAN(accountNumber, personnalCode, myiban, sizeof(myiban));                
                lastTransaction(myiban, 10);
            }
        }
    } else {
        printf("❌ Worst Identifier\n");
        auth_bank();
    }
    
}

void auth_blockchain(){

}
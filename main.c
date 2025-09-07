#include <stdlib.h>
#include <stdio.h>
#include "colors.h"


int scan(){
    char buffer[250];
    int c = 1;
    
    fgets(buffer, c, stdin);

    return 0;
}

int main(int argc, char const *argv[])
{
    CLEAR_SCREEN();

    int run = 1;
    printf("\n"); 


    while(run){
        scan();
    }

    return 0;
}

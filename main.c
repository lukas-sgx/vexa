#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/colors.h"

#define MAX_LENGTH 250

void scan(char *buffer){
    char newBuffer[MAX_LENGTH];

    printf("> ");
    if(fgets(newBuffer, sizeof(newBuffer), stdin) != NULL){
        snprintf(buffer, sizeof(buffer+1), newBuffer);
    }
}

void init(){
    CLEAR_SCREEN();

    printf("""\n"""
    GREEN
    """ ██╗   ██╗███████╗██╗  ██╗ █████╗ \n"""
    """ ██║   ██║██╔════╝╚██╗██╔╝██╔══██╗\n"""
    """ ██║   ██║█████╗   ╚███╔╝ ███████║\n"""
    """ ╚██╗ ██╔╝██╔══╝   ██╔██╗ ██╔══██║\n"""
    """  ╚████╔╝ ███████╗██╔╝ ██╗██║  ██║\n"""
    """   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝\n"""
    """\n"""
    BLACK
    """    *** Digital Bank Vexa ***\n\n""");
}

int main(int argc, char const *argv[])
{
    int run = 1;

    init();

    printf("%sChoose protocol: Bank (1) Blockchain (2)\n", WHITE);

    char protocol[MAX_LENGTH];
    scan(protocol);

    if(strcmp(protocol, "1")){
        init();
    }    

    return 0;
}

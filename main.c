#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/colors.h"
#include "include/authentication.h"

#define MAX_LENGTH 25

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
    """     *** Digital Bank Vexa ***\n\n"""
    WHITE);
}

void protocol_method(){
    printf("Choose protocol: Bank (1) Blockchain (2)\n");

    char protocol[MAX_LENGTH];
    scan(protocol);

    if(strcmp(protocol, "1") == 0){
        init();
        auth_bank();
    } else if(strcmp(protocol, "2") == 0){
        init();
        auth_bank();
    }else{
        printf("Invalid method !\n");
        protocol_method();
    }
}

int main(int argc, char const *argv[])
{
    init();
    protocol_method();

    return 0;
}

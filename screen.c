#include <stdio.h>

#include "include/colors.h"

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

void help(){
    printf("""List of all VEXA commands:\n"""
           """clear                      (\\c) Clear the current input statement\n"""
           """quit                       (\\q) Quit VEXA app\n"""
           """switch                     (\\s) Switch account\n"""
           """transfert 'sum (€)' 'IBAN' (\\t) Tranfert money to another account\n"""
           """balance                    (\\b) Show account balance\n\n"""
    );
}